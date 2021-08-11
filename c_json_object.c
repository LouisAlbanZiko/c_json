#include "internal.h"

C_JSON_Variable *c_json_object_create(uint64_t initial_length)
{
	initial_length = (initial_length == C_JSON_DEFAULT) * g_c_json_data->default_object_length + initial_length;
	C_JSON_Object *object = malloc(sizeof(C_JSON_Object) + sizeof(C_JSON_Object_Element) * initial_length);
	object->type = C_JSON_TYPE_OBJECT;
	object->hash_function = _c_json_hash_default;
	c_json_string_buffer_create(&object->buffer, C_JSON_DEFAULT);
	object->count_c = 0;
	object->count_m = initial_length;

	for (uint32_t i = 0; i < initial_length; i++)
	{
		object->elements[i].name = NULL;
		object->elements[i].variable = NULL;
	}

	return (C_JSON_Variable *)object;
}

C_JSON_Variable *c_json_object_copy(C_JSON_Variable *variable)
{
	if (variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable;
		C_JSON_Variable *new_variable = c_json_object_create(object->count_m);
		C_JSON_Object *new_object = (C_JSON_Object *)new_variable;

		for (uint32_t i = 0; i < object->count_m; i++)
		{
			if (object->elements[i].name != NULL)
				c_json_object_push(new_variable, object->elements[i].name, object->elements[i].variable);
		}

		return new_variable;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
		return NULL;
	}
}

void c_json_object_destroy(C_JSON_Variable *variable)
{
	if (variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable;
		for (uint32_t i = 0; i < object->count_m; i++)
		{
			if (object->elements[i].name != NULL)
				c_json_variable_destroy(object->elements[i].variable);
		}
		free(object);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
	}
}

C_JSON_Variable *c_json_object_get(C_JSON_Variable *variable, const char *name)
{
	if (variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable;

		uint64_t index = _c_json_object_find(object, name);
		if(index < object->count_m)
		{
			return object->elements[index].variable;
		}
		else
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_VARIABLE_NOT_FOUND, "The searched for variable could not be found. name: '%s'", name);
			return NULL;
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
		return NULL;
	}
}

void c_json_object_set(C_JSON_Variable *variable, const char *name, C_JSON_Variable *variable_set)
{
	if (variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable;

		uint64_t index = _c_json_object_find(object, name);
		if(index < object->count_m)
		{
			c_json_variable_destroy(object->elements[index].variable);
			object->elements[index].variable = variable_set;
		}
		else
		{
			c_json_object_push(variable, name, variable_set);
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
	}
}

uint64_t _c_json_object_find(C_JSON_Object *object, const char *name)
{
	uint64_t hash = object->hash_function(name) % object->count_m;
	uint64_t hash_start = hash;
	do
	{
		if (object->elements[hash].name != NULL)
		{
			if (strcmp(name, object->elements[hash].name) == 0)
			{
				return hash;
			}
		}
	} while (hash != hash_start);
	return object->count_m;
}