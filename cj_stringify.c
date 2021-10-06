#include "internal.h"

typedef struct _CJ_Stringify_Data
{
	CM_StringBuffer *buffer;
	CJ_Stringify_Options *options;
} CJ_Stringify_Data;

void cj_stringify_variable(CJ_Variable *variable, CJ_Stringify_Data *s_data);

const char *cj_stringify(CJ_Variable *variable, CJ_Stringify_Options *options)
{
	CJ_Stringify_Data s_data;
	s_data.options = options;
	cm_string_buffer_create(s_data.buffer);

	cj_stringify_variable(variable, &s_data);

	return cm_string_buffer_destroy_and_return(s_data.buffer);
}

void cj_stringify_variable(CJ_Variable *variable, CJ_Stringify_Data *s_data)
{
	static const char *_null = "null";
	switch(variable->type)
	{
		case CJ_TYPE_NULL:
		{
			cm_string_buffer_insert_string(s_data->buffer, _null);
			break;
		}
		case CJ_TYPE_INT:
		{
			int64_t nr = cj_integer_get((CJ_Integer *)variable);
			while (nr != 0)
			{
				cm_string_buffer_insert_char(s_data->buffer, (nr % 10));
				nr /= 10;
			}
			break;
		}
			
	}
}
