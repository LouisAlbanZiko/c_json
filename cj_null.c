#include "internal.h"

CJ_Null *cj_null_create()
{
	_CJ_Variable *var = (_CJ_Variable *)_cj_variable_alloc();
	var->type = CJ_TYPE_NULL;
	var->value = 0;
	return (CJ_Null *)var;
}

void cj_null_destroy(CJ_Null *var)
{
	_cj_variable_free((CJ_Variable *)var);
}