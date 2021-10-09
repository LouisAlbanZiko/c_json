#include "internal.h"

CJ_Integer *cj_integer_create(int64_t value)
{
	_CJ_Integer *integer = (_CJ_Integer *)_cj_variable_alloc();
	integer->type = CJ_TYPE_INT;
	integer->value = value;
	return (CJ_Integer *)integer;
}

CJ_Integer *cj_integer_copy(CJ_Integer *integer)
{
	return cj_integer_create(integer->value);
}

void cj_integer_destroy(CJ_Integer *integer)
{
	_cj_variable_free((CJ_Variable *)integer);
}

void cj_integer_set(CJ_Integer *integer_external, int64_t value)
{
	_CJ_Integer *integer = (_CJ_Integer *)integer_external;
	integer->value = value;
}

int64_t cj_integer_get(CJ_Integer *integer)
{
	return integer->value;
}
