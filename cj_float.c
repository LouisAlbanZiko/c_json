#include "internal.h"

CJ_Float *cj_float_create(double value)
{
	_CJ_Float *_float = (_CJ_Float *)_cj_variable_alloc();
	_float->type = CJ_TYPE_FLOAT;
	_float->value = value;
	return (CJ_Float *)_float;
}

CJ_Float *cj_float_copy(CJ_Float *_float_external)
{
	_CJ_Float *_float = (_CJ_Float *)_float_external;
	return cj_float_create(_float->value);
}

void cj_float_destroy(CJ_Float *_float)
{
	_cj_variable_free((CJ_Variable *)_float);
}

void cj_float_set(CJ_Float *_float_external, double value)
{
	_CJ_Float *_float = (_CJ_Float *)_float_external;
	_float->value = value;
}

double cj_float_get(CJ_Float *_float)
{
	return _float->value;
}