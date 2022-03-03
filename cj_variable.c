#include "internal.h"

CJ_Variable *cj_variable_copy(CJ_Variable *variable)
{
	switch (variable->type)
	{
	case CJ_TYPE_NULL:
		return (CJ_Variable *)cj_null_create();
	case CJ_TYPE_INTEGER:
		return (CJ_Variable *)cj_integer_copy((CJ_Integer *)variable);
	case CJ_TYPE_FLOAT:
		return (CJ_Variable *)cj_float_copy((CJ_Float *)variable);
	case CJ_TYPE_BOOL:
		return (CJ_Variable *)cj_bool_copy((CJ_Bool *)variable);
	case CJ_TYPE_STRING:
		return (CJ_Variable *)cj_string_copy((CJ_String *)variable);
	case CJ_TYPE_OBJECT:
		return (CJ_Variable *)cj_object_copy((CJ_Object *)variable);
	case CJ_TYPE_ARRAY:
		return (CJ_Variable *)cj_array_copy((CJ_Array *)variable);
	default:
		return NULL;
	}
}

uint64_t cj_variable_type(CJ_Variable *variable)
{
	return variable->type;
}

void cj_variable_destroy(CJ_Variable *variable)
{
	switch (variable->type)
	{
	case CJ_TYPE_NULL:
		cj_null_destroy((CJ_Null *)variable);
		return;
	case CJ_TYPE_INTEGER:
		cj_integer_destroy((CJ_Integer *)variable);
		return;
	case CJ_TYPE_FLOAT:
		cj_float_destroy((CJ_Float *)variable);
		return;
	case CJ_TYPE_BOOL:
		cj_bool_destroy((CJ_Bool *)variable);
		return;
	case CJ_TYPE_STRING:
		cj_string_destroy((CJ_String *)variable);
		return;
	case CJ_TYPE_OBJECT:
		cj_object_destroy((CJ_Object *)variable);
		return;
	case CJ_TYPE_ARRAY:
		cj_array_destroy((CJ_Array *)variable);
		return;
	}
}