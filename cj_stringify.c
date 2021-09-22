#include "internal.h"

typedef struct _CJ_StringStream
{
	uint32_t count_c;
	uint32_t count_m;
	char *data;
} CJ_StringStream;

CJ_StringStream *_cj_string_stream_create()
{
	CJ_StringStream *ss = malloc(sizeof(*ss));
	ss->count_m = 128;
	ss->count_c = 0;
	ss->data = malloc(sizeof(*ss->data) * ss->count_m);
	return ss;
}

void _cj_string_stream_insert(CJ_StringStream *ss, const char *string, uint32_t length)
{
	if(ss->count_c + length + 1 > ss->count_m)
	{
		ss->count_m <<= 1;
		ss->data = realloc(ss->data, sizeof(*ss->data) * ss->count_m);
	}
	for(uint32_t i = 0; i < length; i++)
	{
		ss->data[ss->count_c++] = string[i];
	}
}

void _cj_string_stream_destroy(CJ_StringStream *ss)
{
	free(ss->data);
	free(ss);
}


typedef struct _CJ_Stringify_Data
{
	CJ_String_Buffer buffer;
	CJ_Stringify_Options *options;
} CJ_Stringify_Data;

void cj_stringify_variable(CJ_Variable *variable, CJ_Stringify_Data *s_data);

const char *cj_stringify(CJ_Variable *variable, CJ_Stringify_Options *options)
{
	CJ_Stringify_Data s_data;
	s_data.options = options;
	cj_string_buffer_create(&s_data.buffer);

	cj_stringify_variable(variable, &s_data);

	return s_data.buffer.data;
}

void cj_stringify_variable(CJ_Variable *variable, CJ_Stringify_Data *s_data)
{
	switch(variable->type)
	{
		case CJ_TYPE_NULL:
			static const char *_null = "null";
			for(uint32_t i = 0 ; i < 4; i++)
				cj_string_buffer_insert_char(&s_data->buffer, _null[i]);
			break;
	}
}
