#include "internal.h"

void c_json_string_create(C_JSON_Variable *value_dst, const char *string)
{
	value_dst->type = C_JSON_TYPE_STRING;
	char *new_string = malloc(sizeof(*string) * (strlen(string) + 1));
	strcpy(new_string, string);
	value_dst->value = (uint64_t) new_string;
}

void c_json_string_copy(C_JSON_Variable *dst, C_JSON_Variable *src)
{
	if(src->type == C_JSON_TYPE_STRING)
	{
		dst->type = src->type;
		const char *string = (const char *)(src->value);
		char *new_string = malloc(sizeof(*string) * (strlen(string) + 1));
		strcpy(new_string, string);
		dst->value = (uint64_t)(src->value);
	}
	else
	{
		// error type
	}
}

uint64_t c_json_string_is_equal(C_JSON_Variable *val1, C_JSON_Variable *val2)
{
	if(val1->type == C_JSON_TYPE_STRING && val2->type == C_JSON_TYPE_STRING)
	{
		const char *string1 = (const char *)(val1->value);
		const char *string2 = (const char *)(val2->value);
		return strcmp(string1, string2) == 0;
	}
	else
	{
		// error type
	}
	return 0;
}

void c_json_string_destroy(C_JSON_Variable *value)
{
	if(value->type == C_JSON_TYPE_STRING)
	{
		char *string = (char *)(value->value);
		free(string);
	}
	else
	{
		// error type
	}
}