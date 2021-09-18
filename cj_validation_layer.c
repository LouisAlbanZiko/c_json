#include "internal.h"
#include "cj_validation_layer.h"

CJ_Variable *_vl_cj_variable_copy(CJ_Variable *variable)
{
	if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'.", "cj_variable_copy");
		return NULL;
	}
	else
	{
		return cj_variable_copy(variable);
	}
}

uint64_t _vl_cj_variable_type(CJ_Variable *variable)
{
	if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'.", "cj_variable_type");
		return CJ_TYPE_NULL;
	}
	else
	{
		return cj_variable_type(variable);
	}
}

uint64_t _vl_cj_variable_value(CJ_Variable *variable)
{
	if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'.", "cj_variable_value");
		return 0;
	}
	else
	{
		return cj_variable_type(variable);
	}
}

void _vl_cj_variable_destroy(CJ_Variable *variable)
{
	if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'.", "cj_variable_destroy");
	}
	else
	{
		cj_variable_type(variable);
	}
}

CJ_Null *_vl_cj_null_create()
{
	return cj_null_create();
}

void _vl_cj_null_destroy(CJ_Null *var)
{
	if(var == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'.", "cj_null_destroy");
	}
	else
	{
		cj_null_destroy(var);
	}
}
