#include "internal.h"

CJ_Bool *cj_bool_create(uint64_t value)
{
	CJ_Bool *bool = malloc(sizeof(*bool));
	bool->type = CJ_TYPE_BOOL;
	bool->value = value;
	return bool;
}

CJ_Bool *cj_bool_copy(CJ_Bool *bool)
{
	return cj_bool_create(bool->value);
}

void cj_bool_destroy(CJ_Bool *bool)
{
	free(bool);
}

void cj_bool_set(CJ_Bool *bool, uint64_t value)
{
	bool->value = value;
}

uint64_t cj_bool_get(CJ_Bool *bool)
{
	return bool->value;
}
