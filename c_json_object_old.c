#include "internal.h"

C_JSON_Variable *c_json_object_create(uint64_t initial_length)
{
	initial_length = (initial_length == C_JSON_DEFAULT) * C_JSON_DEFAULT_OBJECT_LENGTH + initial_length;
	C_JSON_Variable *object = malloc(sizeof(*object));
	object->type = C_JSON_TYPE_OBJECT;
	C_JSON_Object *object_ptr = malloc(sizeof(*object_ptr) + initial_length * sizeof(C_JSON_Object_Element));
	object->value = (uint64_t)object_ptr;
	object_ptr->count_c = 0;
	object_ptr->count_m = initial_length;
	c_json_string_buffer_create((JSON_StringBuffer *)(&object_ptr->buffer), C_JSON_DEFAULT);
	object_ptr->hash_function = (uint64_t)_c_json_hash_default;

	C_JSON_Object_Element *object_list = object_ptr->elements;
	for (uint64_t i = 0; i < initial_length; i++)
	{
		object_list[i].name = NULL;
		object_list[i].variable = NULL;
	}
}

const C_JSON_Variable *c_json_object_get(C_JSON_Variable *object, const char *name)
{
	if (object->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object_ptr = (C_JSON_Object *)(object->value);
		C_JSON_Object_Element *object_list = (C_JSON_Object_Element *)object_ptr->elements;
		c_json_hash_function hash_function = (c_json_hash_function)object_ptr->hash_function;
		uint64_t hash = hash_function(name) % object_ptr->count_m;
		uint64_t hash_start = hash;
		do
		{
			if (object_list[hash].name != NULL)
			{
				if (strcmp(object_list[hash].name, name) == 0)
				{
					return object_list[hash].variable;
				}
			}
			hash = (hash + 1) % object_ptr->count_m;
		} while (hash != hash_start);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[object->type]);
	}
	return NULL;
}

void c_json_object_resize(C_JSON_Variable *object, uint64_t new_length)
{
	if (object->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object_ptr = (C_JSON_Object *)(object->value);
		if (new_length < object_ptr->count_c)
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_NEW_SIZE_TOO_SMALL, "The new size of the object is too small. Current used size: %d. New size: %d.", object_ptr->count_c, new_length);
		}
		uint64_t length = object_ptr->count_m;

		C_JSON_Object *new_object_ptr = malloc(sizeof(*object_ptr) + new_length * sizeof(C_JSON_Object_Element));
		object->value = (uint64_t)new_object_ptr;
		new_object_ptr->count_c = 0;
		new_object_ptr->count_m = new_length;
		c_json_string_buffer_create((JSON_StringBuffer *)(&new_object_ptr->buffer), C_JSON_DEFAULT);
		new_object_ptr->hash_function = (object_ptr->hash_function);

		for (uint64_t i = 0; i < length; i++)
		{
			if (object_ptr->elements[i].name != NULL)
			{
				c_json_object_attach(object, object_ptr->elements[i].name, object_ptr->elements[i].variable);
			}
		}

		c_json_string_buffer_destroy(&object_ptr->buffer);
		free(object_ptr);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[object->type]);
	}
}

C_JSON_Variable *c_json_object_copy(C_JSON_Variable *object)
{
	if (object->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object_ptr = (C_JSON_Object *)(object->value);
		C_JSON_Variable *new_object = c_json_object_create(object_ptr->count_m);
		C_JSON_Object_Element *object_list = (C_JSON_Object_Element *)object_ptr->elements;
		for (uint64_t i = 0; i < object_ptr->count_m; i++)
		{
			if (object_list[i].name != NULL)
				c_json_object_insert(new_object, object_list[i].name, object_list[i].variable);
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[object->type]);
	}
}

void c_json_object_insert(C_JSON_Variable *object, const char *name, C_JSON_Variable *variable)
{
	C_JSON_Variable *variable_copy = c_json_variable_copy(variable);
	c_json_object_attach(object, name, variable_copy);
}

void c_json_object_attach(C_JSON_Variable *object, const char *name, C_JSON_Variable *variable)
{
	if (object->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object_ptr = (C_JSON_Object *)(object->value);
		if (object_ptr->count_c == object_ptr->count_m)
		{
			c_json_object_resize(object, object_ptr->count_m + C_JSON_DEFAULT_OBJECT_LENGTH);
		}
		uint64_t hash = object_ptr->hash_function(name) % object_ptr->count_m;

		C_JSON_Object_Element *object_list = (C_JSON_Object_Element *)object_ptr->elements;

		while (object_list[hash].name != NULL)
		{
			if (strcmp(object_list[hash].name, name) == 0)
				break;
			hash = (hash + 1) % object_ptr->count_m;
		}
		JSON_StringBuffer *string_buffer = (JSON_StringBuffer *)&object_ptr->buffer;
		// copy name
		char *name_copy;
		{
			name_copy = string_buffer->data + string_buffer->size_c;
			uint32_t i = 0;
			while (name[i] != '\0')
			{
				c_json_string_buffer_insert(string_buffer, name[i]);
				i++;
			}
			c_json_string_buffer_end_string(string_buffer);
		}

		object_list[hash].name = name_copy;
		object_list[hash].variable = variable;

		object_ptr->count_c++;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[object->type]);
	}
}

void c_json_object_remove(C_JSON_Variable *obj, const char *name)
{
	C_JSON_Variable variable = c_json_object_detach(obj, name);
	c_json_variable_destroy(&variable);
}

C_JSON_Variable c_json_object_detach(C_JSON_Variable *obj, const char *name)
{
	if (obj->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object_ptr = (C_JSON_Object *)(obj->value);
		c_json_hash_function hash_function = (c_json_hash_function)(object_ptr->hash_function);
		uint64_t hash = hash_function(name);

		C_JSON_Object_Element *object_list = (C_JSON_Object_Element *)object_ptr->elements;

		while (object_list[hash].name != NULL)
		{
			if (strcmp(object_list[hash].name, name) == 0)
				break;
			hash = (hash + 1) % object_ptr->count_m;
		}

		C_JSON_Variable return_value = *(object_list[hash].variable);

		object_list[hash].name = NULL;
		object_list[hash].variable = NULL;

		return return_value;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[obj->type]);
	}
}

void c_json_object_destroy(C_JSON_Variable *value)
{
	if (value->type == C_JSON_TYPE_OBJECT)
	{
		C_JSON_Object *object_ptr = (C_JSON_Object *)(value->value);
		C_JSON_Object_Element *object_list = (C_JSON_Object_Element *)object_ptr->elements;
		for (uint64_t i = 0; i < object_ptr->count_m; i++)
		{
			if (object_list[i].name != NULL)
			{
				c_json_variable_destroy(object_list[i].variable);
			}
		}
		JSON_StringBuffer *string_buffer = (JSON_StringBuffer *)&object_ptr->buffer;
		c_json_string_buffer_destroy(string_buffer);
		free(object_ptr);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[value->type]);
	}
}

void _c_json_object_resize(C_JSON_Variable *object, uint64_t new_length)
{
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