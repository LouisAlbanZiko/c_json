#include "internal.h"

CJ_Float *CJ_Float_Create(double value)
{
	_CJ_Float *var = CC_Malloc(sizeof(*var));

	var->type = CJ_TYPE_FLOAT;
	var->value = value;

	return (CJ_Float *)var;
}

CJ_Float *CJ_Float_Copy(CJ_Float *var)
{
	return CJ_Float_Create(var->value);
}

void CJ_Float_Destroy(CJ_Float *var)
{
	CC_Free(var);
}

void CJ_Float_Set(CJ_Float *var, double value)
{
	_CJ_Float *_var = (_CJ_Float *)var;
	_var->value = value;
}

double CJ_Float_Get(CJ_Float *var)
{
	return var->value;
}
