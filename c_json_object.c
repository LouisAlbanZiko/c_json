#include "internal.h"

C_JSON_Variable *c_json_object_create(uint64_t initial_length)
{
	initial_length = (initial_length == C_JSON_DEFAULT) * g_c_json_data->default_object_length + initial_length;
	C_JSON_Variable *variable = malloc(sizeof(*variable));
	variable->type = C_JSON_TYPE_OBJECT;
	C_JSON_Object *object = malloc(sizeof(*object) + initial_length * sizeof(C_JSON_Object_Element));
	variable->value = (uint64_t)object;
	object->count_c = 0;
	object->count_m = initial_length;
	c_json_string_buffer_create((JSON_StringBuffer *)(&object->buffer), C_JSON_DEFAULT);
	object->hash_function = _c_json_hash_default;

	C_JSON_Object_Element *object_list = object->elements;
	for(uint64_t i = 0; i < initial_length; i++)
	{
		object_list[i].name = NULL;
		object_list[i].variable = NULL;
	}

	return variable;
}

C_JSON_Variable *c_json_object_copy(C_JSON_Variable *variable)
{
	if(variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable->value;

		C_JSON_Variable *copy_variable = c_json_object_create(object->count_m);
		C_JSON_Object *copy_object = (C_JSON_Object *)copy_variable->value;

		for(uint64_t i = 0; i < object->count_m; i++)
		{
			if(object->elements[i].name != NULL)
			{
				c_json_object_push(copy_variable, object->elements[i].name, object->elements[i].variable);
			}
		}
		return copy_variable;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
		return NULL;
	}
}

void c_json_object_destroy(C_JSON_Variable *variable)
{
	if(variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable->value;
		for(uint64_t i = 0; i < object->count_m; i++)
		{
			if(object->elements[i].name != NULL)
			{
				c_json_variable_destroy(object->elements[i].variable);
			}
		}
		c_json_string_buffer_destroy(&object->buffer);
		free(object);
		free(variable);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
	}
}

C_JSON_Variable *c_json_object_get(C_JSON_Variable *variable, const char *name)
{
	if(variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable->value;

		uint64_t index = _c_json_object_find(variable, name);
		if(index < object->count_m)
		{
			return object->elements[index].variable;
		}
		else
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_VARIABLE_NOT_FOUND, "Variable with name '%s' not found.", name);
			return NULL;
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
		return NULL;
	}
}

void c_json_object_set(C_JSON_Variable *object, const char *name, C_JSON_Variable *variable)
{
	
}


// internal

void _c_json_object_resize(C_JSON_Variable *variable, uint64_t new_length)
{
	if(variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable->value;
		if (new_length < object->count_c)
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_NEW_SIZE_TOO_SMALL, "The new size of the object is too small. Current used size: %d. New size: %d.", object->count_c, new_length);
		}
		
		C_JSON_Object *new_object = malloc(sizeof(*new_object) + new_length * sizeof(C_JSON_Object_Element));
		variable->value = (uint64_t) new_object;
		new_object->count_c = 0;
		new_object->count_m = new_length;
		c_json_string_buffer_create((JSON_StringBuffer *)(&new_object->buffer), C_JSON_DEFAULT);
		new_object->hash_function = (object->hash_function);

		for(uint64_t i = 0; i < object->count_m; i++)
		{
			if(object->elements[i].name != NULL)
			{
				c_json_object_attach(variable, object->elements[i].name, object->elements[i].variable);
			}
		}

		c_json_string_buffer_destroy(&object->buffer);
		free(object);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
	}
}

uint64_t _c_json_object_find(C_JSON_Variable *variable, const char *name)
{
	if (variable->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object = (C_JSON_Object *)variable->value;

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
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[variable->type]);
		return UINT64_MAX;
	}
}

uint64_t _c_json_hash_default(const char *string)
{
	uint64_t size = strlen(string);
	uint64_t hash = 0;
	for (uint32_t i = 0; i < size; i++)
	{
		hash += string[i];
	}
	return hash;
}