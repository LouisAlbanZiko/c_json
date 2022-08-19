#include "internal.h"

CJ_Integer *CJ_Integer_Create(int64_t value)
{
	_CJ_Integer *var = CC_Malloc(sizeof(*var));

	var->type = CJ_TYPE_INTEGER;
	var->value = value;

	return (CJ_Integer *)var;
}

CJ_Integer *CJ_Integer_Copy(CJ_Integer *var)
{
	return CJ_Integer_Create(var->value);
}

void CJ_Integer_Destroy(CJ_Integer *var)
{
	CC_Free(var);
}

void CJ_Integer_Set(CJ_Integer *var, int64_t value)
{
	_CJ_Integer *_var = (_CJ_Integer *)var;
	_var->value = value;
}

int64_t CJ_Integer_Get(CJ_Integer *var)
{
	return var->value;
}