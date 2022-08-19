#include "internal.h"

CJ_Bool *CJ_Bool_Create(uint64_t value)
{
	_CJ_Bool *var = CC_Malloc(sizeof(*var));

	var->type = CJ_TYPE_BOOL;
	var->value = value;

	return (CJ_Bool *)var;
}

CJ_Bool *CJ_Bool_Copy(CJ_Bool *var)
{
	return CJ_Bool_Create(var->value);
}

void CJ_Bool_Destroy(CJ_Bool *var)
{
	CC_Free(var);
}

void CJ_Bool_Set(CJ_Bool *var, uint64_t value)
{
	_CJ_Bool *_var = (_CJ_Bool *)var;
	_var->value = value;
}

uint64_t CJ_Bool_Get(CJ_Bool *var)
{
	return var->value;
}
