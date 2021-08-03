#include "internal.h"

void c_json_variable_copy(C_JSON_Variable *dst, C_JSON_Variable *src)
{
	switch(src->type)
	{
		case C_JSON_TYPE_STRING:
			c_json_string_copy(dst, src);
			break;
		case C_JSON_TYPE_OBJECT:
			c_json_object_copy(dst, src);
			break;
		case C_JSON_TYPE_ARRAY:
			c_json_array_copy(dst, src);
			break;
		default:
			*dst = *src;
			break;
	}
}

void c_json_variable_destroy(C_JSON_Variable *value)
{
	switch(value->type)
	{
		case C_JSON_TYPE_STRING:
			c_json_string_destroy(value);
			break;
		case C_JSON_TYPE_OBJECT:
			c_json_object_destroy(value);
			break;
		case C_JSON_TYPE_ARRAY:
			c_json_array_destroy(value);
			break;
	}
}