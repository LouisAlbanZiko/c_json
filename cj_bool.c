#include "internal.h"

CJ_Bool *cj_bool_create(uint64_t value)
{
	_CJ_Bool *bool = (_CJ_Bool *)_cj_variable_alloc();
	bool->type = CJ_TYPE_BOOL;
	bool->value = value;
	return (CJ_Bool *)bool;
}

CJ_Bool *cj_bool_copy(CJ_Bool *bool)
{
	return cj_bool_create(bool->value);
}

void cj_bool_destroy(CJ_Bool *bool)
{
	_cj_variable_free((CJ_Variable *)bool);
}

void cj_bool_set(CJ_Bool *bool_external, uint64_t value)
{
	_CJ_Bool *bool = (_CJ_Bool *)bool_external;
	bool->value = value;
}

uint64_t cj_bool_get(CJ_Bool *bool)
{
	return bool->value;
}
