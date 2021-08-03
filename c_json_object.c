#include "internal.h"

void c_json_object_create(C_JSON_Variable *value_dst, uint64_t initial_length)
{
	initial_length = (initial_length == C_JSON_DEFAULT) * C_JSON_DEFAULT_OBJECT_LENGTH + initial_length;
	value_dst->type = C_JSON_TYPE_OBJECT;
	uint64_t *object_ptr = ((uint64_t *)malloc(5 * sizeof(uint64_t) + initial_length * sizeof(JSON_Object_Element))) + 5;
	value_dst->value = (uint64_t)object_ptr;
	object_ptr[C_JSON_INDEX_COUNT_C] = 0;
	object_ptr[C_JSON_INDEX_COUNT_M] = initial_length;
	c_json_string_buffer_create((JSON_StringBuffer *)(&object_ptr[C_JSON_INDEX_STRING_BUFFER]), C_JSON_DEFAULT);
	object_ptr[C_JSON_INDEX_HASH_FUNCTION] = (uint64_t)_c_json_hash_default;

	JSON_Object_Element *object_list = (JSON_Object_Element *)object_ptr;
	for (uint64_t i = 0; i < initial_length; i++)
	{
		object_list[i].name = NULL;
		object_list[i].type = C_JSON_TYPE_NONE;
		object_list[i].value = 0;
	}
}

C_JSON_Variable c_json_object_get(C_JSON_Variable *value_dst, const char *name)
{
	C_JSON_Variable val = {.type = C_JSON_TYPE_NONE, .value = 0};
	if (value_dst->type == C_JSON_TYPE_OBJECT)
	{
		uint64_t *object_ptr = (uint64_t *)(value_dst->value);
		JSON_Object_Element *object_list = (JSON_Object_Element *)object_ptr;
		c_json_hash_function hash_function = (c_json_hash_function)object_ptr[C_JSON_INDEX_HASH_FUNCTION];
		uint64_t hash = hash_function(name) % object_ptr[C_JSON_INDEX_COUNT_M];
		uint64_t hash_start = hash;
		do
		{
			if (object_list[hash].name != NULL)
			{
				if (strcmp(object_list[hash].name, name) == 0)
				{
					val.type = object_list[hash].type;
					val.value = object_list[hash].value;
					return val;
				}
			}
			hash = (hash + 1) % object_ptr[C_JSON_INDEX_COUNT_M];
		} while (hash != hash_start);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[value_dst->type]);
	}
	return val;
}

void c_json_object_resize(C_JSON_Variable *value_dst, uint64_t new_length)
{
	if (value_dst->type == C_JSON_TYPE_OBJECT)
	{
		uint64_t *object_ptr = (uint64_t *)(value_dst->value);
		if (new_length < object_ptr[C_JSON_INDEX_COUNT_C])
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_NEW_SIZE_TOO_SMALL, "The new size of the object is too small. Current used size: %d. New size: %d.", object_ptr[C_JSON_INDEX_COUNT_C], new_length);
		}
		uint64_t length = object_ptr[C_JSON_INDEX_COUNT_M];
		uint64_t *object_start = object_ptr - 5;

		C_JSON_Variable value_new;
		c_json_object_create(&value_new, new_length);
		uint64_t *object_start_new = (uint64_t *)(value_new.value);
		uint64_t *object_ptr_new = object_start_new + 5;

		JSON_Object_Element *object_list = (JSON_Object_Element *)object_ptr;
		JSON_Object_Element *object_list_new = (JSON_Object_Element *)object_ptr_new;
		for (uint64_t i = 0; i < length; i++)
		{
			if (object_list[i].name != NULL)
			{
				C_JSON_Variable value_c;
				value_c.type = object_list[i].type;
				value_c.value = object_list[i].value;
				c_json_object_insert(value_dst, object_list[i].name, value_c);
			}
		}

		c_json_object_destroy(value_dst);

		value_dst->value = (uint64_t)object_ptr_new;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[value_dst->type]);
	}
}

void c_json_object_copy(C_JSON_Variable *dst, C_JSON_Variable *src)
{
	if (src->type == C_JSON_TYPE_OBJECT)
	{
		uint64_t *src_ptr = (uint64_t *)(src->value);
		c_json_object_create(dst, src_ptr[C_JSON_INDEX_COUNT_M]);
		JSON_Object_Element *src_list = (JSON_Object_Element *)src_ptr;
		for (uint64_t i = 0; i < src_ptr[C_JSON_INDEX_COUNT_M]; i++)
		{
			if (src_list[i].name != NULL)
				c_json_object_insert(dst, src_list[i].name, *((C_JSON_Variable *)&(src_list[i].type)));
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[src->type]);
	}
}

void c_json_object_insert(C_JSON_Variable *obj, const char *name, C_JSON_Variable value)
{
	C_JSON_Variable variable_copy;
	c_json_variable_copy(&variable_copy, &value);
	c_json_object_attach(obj, name, variable_copy);
}

void c_json_object_attach(C_JSON_Variable *obj, const char *name, C_JSON_Variable value)
{
	if (obj->type == C_JSON_TYPE_OBJECT)
	{
		uint64_t *object_ptr = (uint64_t *)(obj->value);
		if (object_ptr[C_JSON_INDEX_COUNT_C] == object_ptr[C_JSON_INDEX_COUNT_M])
		{
			c_json_object_resize(obj, object_ptr[C_JSON_INDEX_COUNT_M] + C_JSON_DEFAULT_OBJECT_LENGTH);
		}
		uint64_t hash = ((c_json_hash_function)object_ptr[C_JSON_INDEX_HASH_FUNCTION])(name) % object_ptr[C_JSON_INDEX_COUNT_M];
		JSON_Object_Element *object_list = (JSON_Object_Element *)object_ptr;

		while (object_list[hash].name != NULL)
		{
			if (strcmp(object_list[hash].name, name) == 0)
				break;
			hash = (hash + 1) % object_ptr[C_JSON_INDEX_COUNT_M];
		}
		JSON_StringBuffer *string_buffer = (JSON_StringBuffer *)&object_ptr[C_JSON_INDEX_STRING_BUFFER];
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
		object_list[hash].type = value.type;
		object_list[hash].value = value.value;

		object_ptr[C_JSON_INDEX_COUNT_C]++;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[obj->type]);
	}
}

void c_json_object_remove(C_JSON_Variable *obj, const char *name)
{
	C_JSON_Variable variable = c_json_object_detach(obj, name);
	c_json_variable_destroy(&variable);
}

C_JSON_Variable c_json_object_detach(C_JSON_Variable *obj, const char *name)
{
	if(obj->type == C_JSON_TYPE_OBJECT)
	{
		uint64_t *object_ptr = (uint64_t *)(obj->value);
		c_json_hash_function hash_function = (c_json_hash_function)(object_ptr[C_JSON_INDEX_HASH_FUNCTION]);
		uint64_t hash = hash_function(name);
		
		JSON_Object_Element *object_list = (JSON_Object_Element *)object_ptr;

		while (object_list[hash].name != NULL)
		{
			if (strcmp(object_list[hash].name, name) == 0)
				break;
			hash = (hash + 1) % object_ptr[C_JSON_INDEX_COUNT_M];
		}

		C_JSON_Variable return_value;
		return_value.type = object_list->type;
		return_value.value = object_list->value;

		object_list[hash].name = NULL;
		object_list[hash].type = 0;
		object_list[hash].value = 0;

		return return_value;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[obj->type]);
	}
}

void c_json_object_destroy(C_JSON_Variable *value)
{
	if (value->type == C_JSON_TYPE_OBJECT)
	{
		uint64_t *object_ptr = (uint64_t *)(value->value);
		JSON_Object_Element *object_list = (JSON_Object_Element *)object_ptr;
		for (uint64_t i = 0; i < object_ptr[C_JSON_INDEX_COUNT_M]; i++)
		{
			if (object_list[i].name != NULL)
			{
				if (object_list[i].type == C_JSON_TYPE_OBJECT)
				{
					c_json_object_destroy((C_JSON_Variable *)&(object_list[i].type));
				}
				else if (object_list[i].type == C_JSON_TYPE_ARRAY)
				{
					c_json_array_destroy((C_JSON_Variable *)&(object_list[i].type));
				}
			}
		}
		JSON_StringBuffer *string_buffer = (JSON_StringBuffer *)&object_ptr[C_JSON_INDEX_STRING_BUFFER];
		c_json_string_buffer_destroy(string_buffer);
		free(object_ptr - 5);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT], g_c_json_data->json_type_strings[value->type]);
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