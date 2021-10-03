#include "internal.h"

CJ_String *cj_string_create(const char *value)
{
	CJ_String *string = _cj_variable_alloc();
	string->type = CJ_TYPE_STRING;
	string->value = cm_heap_string_alloc_and_copy(g_cj_heap_string, value);
	return string;
}

CJ_String *cj_string_copy(CJ_String *string)
{
	CJ_String *copy = cj_string_create(string->value);
	return copy;
}

void cj_string_destroy(CJ_String *string)
{
	cm_heap_string_free(g_cj_heap_string, string->value);
	_cj_variable_free(string);
}

void cj_string_set(CJ_String *string, const char *value)
{
	cm_heap_string_free(g_cj_heap_string, string->value);
	string->value = cm_heap_string_alloc_and_copy(g_cj_heap_string, value);
	strcpy(string->value, value);
}

const char *cj_string_get(CJ_String *string)
{
	return string->value;
}
