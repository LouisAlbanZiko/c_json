#include "internal.h"

CJ_Integer *cj_integer_create(int64_t value)
{
	CJ_Integer *integer = malloc(sizeof(*integer));
	integer->type = CJ_TYPE_INT;
	integer->value = value;
	return integer;
}

CJ_Integer *cj_integer_copy(CJ_Integer *integer)
{
	return cj_integer_create(integer->value);
}

void cj_integer_destroy(CJ_Integer *integer)
{
	free(integer);
}

void cj_integer_set(CJ_Integer *integer, int64_t value)
{
	integer->value = value;
}

int64_t cj_integer_get(CJ_Integer *integer)
{
	return integer->value;
}
