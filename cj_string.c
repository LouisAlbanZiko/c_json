#include "internal.h"

CJ_String *cj_string_create(CC_String value)
{
	_CJ_String *var = malloc(sizeof(*var));

	var->type = CJ_TYPE_STRING;
	var->value = cc_string_copy(value);

	return (CJ_String *)var;
}

CJ_String *cj_string_copy(CJ_String *var)
{
	return cj_string_create(((_CJ_String *)var)->value);
}

void cj_string_destroy(CJ_String *var)
{
	cc_string_destroy(((_CJ_String *)var)->value);
	free(var);
}

void cj_string_set(CJ_String *string, CC_String value)
{
	_CJ_String *_var = (_CJ_String *)string;
	cc_string_destroy(_var->value);
	_var->value = cc_string_copy(value);
}

CC_String cj_string_get(CJ_String *string)
{
	return ((_CJ_String *)string)->value;
}