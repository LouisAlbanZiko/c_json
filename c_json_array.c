#include "internal.h"

void c_json_array_create(C_JSON_Variable *array_dst, uint64_t initial_length)
{
	initial_length = (initial_length == C_JSON_DEFAULT) * C_JSON_DEFAULT_ARRAY_LENGTH + initial_length;
	array_dst->type = C_JSON_TYPE_ARRAY;
	uint64_t *array_start = malloc(4 * sizeof(uint64_t) + initial_length * sizeof(C_JSON_Variable));
	uint64_t *array_ptr = array_start + 4;
	array_dst->value = (uint64_t)array_ptr;
	array_ptr[C_JSON_INDEX_COUNT_C] = 0;
	array_ptr[C_JSON_INDEX_COUNT_M] = initial_length;
	c_json_string_buffer_create((JSON_StringBuffer *)(&array_ptr[C_JSON_INDEX_STRING_BUFFER]), C_JSON_DEFAULT);
	
	C_JSON_Variable *array_list = (C_JSON_Variable *)array_ptr;
	for(uint64_t i = 0; i < initial_length; i++)
	{
		array_list[i].type = C_JSON_TYPE_NONE;
		array_list[i].value = 0;
	}
}

C_JSON_Variable c_json_array_get(C_JSON_Variable *array, uint64_t index)
{
	if(array->type == C_JSON_TYPE_ARRAY)
	{
		uint64_t *array_ptr = (uint64_t *)(array->value);
		if(index < array_ptr[C_JSON_INDEX_COUNT_C])
		{
			C_JSON_Variable *array_list = (C_JSON_Variable *)array_ptr;
			return array_list[index];
		}
		else
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_OUT_OF_BOUNDS, "The passed index is out of bounds. Size of array: %d. Index: %d.", array_ptr[C_JSON_INDEX_COUNT_C], index);
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[array->type]);
	}
	C_JSON_Variable val = { .type = C_JSON_TYPE_NONE, .value = 0 };
	return val;
}

void c_json_array_resize(C_JSON_Variable *array, uint64_t new_length)
{
	if(array->type == C_JSON_TYPE_ARRAY)
	{
		uint64_t *array_ptr = (uint64_t *)(array->value);
		if(new_length < array_ptr[C_JSON_INDEX_COUNT_C])
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_NEW_SIZE_TOO_SMALL, "The new size of the array is too small. Current used size: %d. New size: %d.", array_ptr[C_JSON_INDEX_COUNT_C], new_length);
		}
		uint64_t *array_start = array_ptr - 4;
		array_start = realloc(array_start, 4 * sizeof(uint64_t) + new_length * sizeof(C_JSON_Variable));
		array_ptr = array_start + 4;
		array->value = (uint64_t)array_ptr;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[array->type]);
	}
}

void c_json_array_copy(C_JSON_Variable *dst, C_JSON_Variable *src)
{
	if(src->type == C_JSON_TYPE_ARRAY)
	{
		uint64_t *src_ptr = (uint64_t *)(src->value);
		c_json_array_create(dst, src_ptr[C_JSON_INDEX_COUNT_M]);
		C_JSON_Variable *src_list = (C_JSON_Variable *)src_ptr;
		for(uint64_t i = 0; i < src_ptr[C_JSON_INDEX_COUNT_C]; i++)
		{
			c_json_array_push(dst, src_list[i]);
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[src->type]);
	}
}

void c_json_array_push(C_JSON_Variable *array, C_JSON_Variable value)
{
	C_JSON_Variable variable_copy;
	c_json_variable_copy(&variable_copy, &value);
	c_json_array_attach(array, variable_copy);
}

void c_json_array_attach(C_JSON_Variable *array, C_JSON_Variable value)
{
	if(array->type == C_JSON_TYPE_ARRAY)
	{
		uint64_t *array_ptr = (uint64_t *)(array->value);
		if(array_ptr[C_JSON_INDEX_COUNT_C] == array_ptr[C_JSON_INDEX_COUNT_M])
		{
			c_json_array_resize(array, array_ptr[C_JSON_INDEX_COUNT_M] + C_JSON_DEFAULT_ARRAY_LENGTH);
		}
		C_JSON_Variable *array_list = (C_JSON_Variable *)array_ptr;
		array_list[array_ptr[C_JSON_INDEX_COUNT_C]] = value;
		array_ptr[C_JSON_INDEX_COUNT_C]++;
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[array->type]);
	}
}

void c_json_array_remove(C_JSON_Variable *array, uint64_t index)
{
	if(array->type == C_JSON_TYPE_ARRAY)
	{
		C_JSON_Variable variable = c_json_array_detach(array, index);
		c_json_variable_destroy(&variable);
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[array->type]);
	}
}

C_JSON_Variable c_json_array_detach(C_JSON_Variable *array, uint64_t index)
{
	if(array->type == C_JSON_TYPE_ARRAY)
	{
		uint64_t *array_ptr = (uint64_t *)(array->value);
		if(index < array_ptr[C_JSON_INDEX_COUNT_C])
		{
			C_JSON_Variable *array_list = (C_JSON_Variable *)array_ptr;
			C_JSON_Variable return_variable = array_list[index];

			array_list[index].type = 0;
			array_list[index].value = 0;

			return return_variable;
		}
		else
		{
			_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_OUT_OF_BOUNDS, "The passed index is out of bounds. Size of array: %d. Index: %d.", array_ptr[C_JSON_INDEX_COUNT_C], index);
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[array->type]);
	}
}

void c_json_array_destroy(C_JSON_Variable *array)
{
	if(array->type == C_JSON_TYPE_ARRAY)
	{
		uint64_t *array_ptr = (uint64_t *)(array->value);
		C_JSON_Variable *array_list = (C_JSON_Variable *)array_ptr;
		for(uint64_t i = 0; i < array_ptr[C_JSON_INDEX_COUNT_M]; i++)
		{
			if(array_list[i].type == C_JSON_TYPE_OBJECT)
			{
				c_json_object_destroy(array_list + i);
			}
			else if(array_list[i].type == C_JSON_TYPE_ARRAY)
			{
				c_json_array_destroy(array_list + i);
			}
		}
	}
	else
	{
		_c_json_make_error(C_JSON_ERROR_SEVERITY_ERROR, C_JSON_ERROR_TYPE_INCORRECT_TYPE, "Incorrect type. Expected %s but received %s.", g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY], g_c_json_data->json_type_strings[array->type]);
	}
}