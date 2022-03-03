#include "internal.h"

CJ_String *cj_string_create(CM_String value)
{
	_CJ_String *var = malloc(sizeof(*var));

	var->type = CJ_TYPE_STRING;
	var->value = cm_string_copy(NULL, value);

	return (CJ_String *)var;
}

CJ_String *cj_string_copy(CJ_String *var)
{
	return cj_string_create(((_CJ_String *)var)->value);
}

void cj_string_destroy(CJ_String *var)
{
	cm_string_destroy(((_CJ_String *)var)->value);
	free(var);
}

void cj_string_set(CJ_String *string, CM_String value)
{
	_CJ_String *_var = (_CJ_String *)string;
	cm_string_destroy(_var->value);
	_var->value = cm_string_copy(NULL, value);
}

CM_String cj_string_get(CJ_String *string)
{
	return ((_CJ_String *)string)->value;
}