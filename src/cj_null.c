#include "internal.h"

CJ_Null *CJ_Null_Create()
{
	_CJ_Null *var = CC_Malloc(sizeof(*var));

	var->type = CJ_TYPE_NULL;
	var->value = 0;

	return (CJ_Null *)var;
}

void CJ_Null_Destroy(CJ_Null *var)
{
	CC_Free(var);
}