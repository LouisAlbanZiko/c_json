#include "internal.h"

CJ_Integer *cj_integer_create(int64_t value)
{
	_CJ_Integer *var = malloc(sizeof(*var));

	var->type = CJ_TYPE_INTEGER;
	var->value = value;

	return (CJ_Integer *)var;
}

CJ_Integer *cj_integer_copy(CJ_Integer *var)
{
	return cj_integer_create(var->value);
}

void cj_integer_destroy(CJ_Integer *var)
{
	free(var);
}

void cj_integer_set(CJ_Integer *var, int64_t value)
{
	_CJ_Integer *_var = (_CJ_Integer *)var;
	_var->value = value;
}

int64_t cj_integer_get(CJ_Integer *var)
{
	return var->value;
}