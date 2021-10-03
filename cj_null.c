#include "internal.h"

CJ_Null *cj_null_create()
{
	CJ_Variable *var = _cj_variable_alloc();
	var->type = CJ_TYPE_NULL;
	var->value = 0;
	return (CJ_Null *)var;
}

void cj_null_destroy(CJ_Null *var)
{
	_cj_variable_free(var);
}