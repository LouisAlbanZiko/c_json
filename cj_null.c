#include "internal.h"

CJ_Null *cj_null_create()
{
	_CJ_Null *var = malloc(sizeof(*var));

	var->type = CJ_TYPE_NULL;
	var->value = 0;

	return (CJ_Null *)var;
}

void cj_null_destroy(CJ_Null *var)
{
	free(var);
}