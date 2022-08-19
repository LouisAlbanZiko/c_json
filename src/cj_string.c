#include "internal.h"

CJ_String *CJ_String_Create(const char * value)
{
	_CJ_String *var = CC_Malloc(sizeof(*var));

	var->type = CJ_TYPE_STRING;
	var->value = CC_String_Copy(value);

	return (CJ_String *)var;
}

CJ_String *CJ_String_Copy(CJ_String *var)
{
	return CJ_String_Create(((_CJ_String *)var)->value);
}

void CJ_String_Destroy(CJ_String *var)
{
	CC_String_Destroy(((_CJ_String *)var)->value);
	CC_Free(var);
}

void CJ_String_Set(CJ_String *string, const char * value)
{
	_CJ_String *_var = (_CJ_String *)string;
	CC_String_Destroy(_var->value);
	_var->value = CC_String_Copy(value);
}

const char * CJ_String_Get(CJ_String *string)
{
	return ((_CJ_String *)string)->value;
}