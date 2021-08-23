#include "internal.h"

void cj_string_buffer_create(CJ_String_Buffer *buffer)
{
	buffer->count_c = 0;
	buffer->count_m = C_JSON_DEFAULT_STRING_BUFFER_LENGTH;
	buffer->data = malloc(sizeof(*buffer->data) * buffer->count_m);
}

void cj_string_buffer_insert_string(CJ_String_Buffer *buffer, const char *string)
{
	uint32_t length = strlen(string);
	if(buffer->count_c + length + 1 > buffer->count_m)
	{
		buffer->count_m *= 2;
		buffer->data = realloc(buffer->data, sizeof(*buffer->data) * buffer->count_m);
	}
	strcpy(buffer->data + buffer->count_c, string);
	buffer->count_c += length + 1;
}

void cj_string_buffer_insert_char(CJ_String_Buffer *buffer, char c)
{
	if(buffer->count_c + 1 > buffer->count_m)
	{
		buffer->count_m *= 2;
		buffer->data = realloc(buffer->data, sizeof(*buffer->data) * buffer->count_m);
	}
	buffer->data[buffer->count_c++] = c;
}

char *cj_string_buffer_current(CJ_String_Buffer *buffer)
{
	return buffer->data + buffer->count_c;
}

void cj_string_buffer_destroy(CJ_String_Buffer *buffer)
{
	free(buffer->data);
}