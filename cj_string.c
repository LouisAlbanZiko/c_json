#include "internal.h"

CJ_String *cj_string_create(const char *value)
{
	CJ_String *string = malloc(sizeof(*string));
	string->type = CJ_TYPE_STRING;
	string->value = malloc(sizeof(*string->value) * (strlen(value) + 1));
	strcpy(string->value, value);
	return string;
}

CJ_String *cj_string_copy(CJ_String *string)
{
	CJ_String *copy = cj_string_create(string->value);
	return copy;
}

void cj_string_destroy(CJ_String *string)
{
	free(string->value);
	free(string);
}

void cj_string_set(CJ_String *string, const char *value)
{
	free(string->value);
	string->value = malloc(sizeof(*string->value) * (strlen(value) + 1));
	strcpy(string->value, value);
}

const char *cj_string_get(CJ_String *string)
{
	return string->value;
}
