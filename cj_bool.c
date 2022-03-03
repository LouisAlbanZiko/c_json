#include "internal.h"

CJ_Bool *cj_bool_create(uint64_t value)
{
	_CJ_Bool *var = malloc(sizeof(*var));

	var->type = CJ_TYPE_BOOL;
	var->value = value;

	return (CJ_Bool *)var;
}

CJ_Bool *cj_bool_copy(CJ_Bool *var)
{
	return cj_bool_create(var->value);
}

void cj_bool_destroy(CJ_Bool *var)
{
	free(var);
}

void cj_bool_set(CJ_Bool *var, uint64_t value)
{
	_CJ_Bool *_var = (_CJ_Bool *)var;
	_var->value = value;
}

uint64_t cj_bool_get(CJ_Bool *var)
{
	return var->value;
}
