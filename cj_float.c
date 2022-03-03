#include "internal.h"

CJ_Float *cj_float_create(double value)
{
	_CJ_Float *var = malloc(sizeof(*var));

	var->type = CJ_TYPE_FLOAT;
	var->value = value;

	return (CJ_Float *)var;
}

CJ_Float *cj_float_copy(CJ_Float *var)
{
	return cj_float_create(var->value);
}

void cj_float_destroy(CJ_Float *var)
{
	free(var);
}

void cj_float_set(CJ_Float *var, double value)
{
	_CJ_Float *_var = (_CJ_Float *)var;
	_var->value = value;
}

double cj_float_get(CJ_Float *var)
{
	return var->value;
}
