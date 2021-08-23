#include "internal.h"

typedef struct _CJ_ParseData
{
	const char *start;
	const char *current;
	const char *end;
	uint32_t line;
	uint32_t character_in_line;
} CJ_ParseData;

#define C (parse_data->current[0])

void cj_parse_character(CJ_ParseData *parse_data);
void cj_parse_whitespace(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_value(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_string(CJ_ParseData *parse_data);

CJ_Variable *cj_parse(const char *string)
{
	CJ_ParseData parse_data = 
	{
		.start = string,
		.current = string,
		.end = string + strlen(string),
		.line = 0,
		.character_in_line = 0
	};

	CJ_Variable *variable;



	return variable;
}

void cj_parse_character(CJ_ParseData *parse_data)
{
	uint32_t is_new_line = C == '\n';
	parse_data->line += is_new_line;
	parse_data->character_in_line = !is_new_line * (parse_data->character_in_line + 1);
	parse_data->current++;
}

void cj_parse_whitespace(CJ_ParseData *parse_data)
{
	while(C == ' ' || C == '\t' || C == '\n' || C == '\r')
		cj_parse_character(parse_data);
}

CJ_Variable *cj_parse_value(CJ_ParseData *parse_data)
{
	cj_parse_whitespace(parse_data);

	if(C == '"')
	{
		
	}
	else if(C == '{')
	{

	}
	else if(C == '[')
	{

	}
	else if(C == 't' || C == 'f')
	{

	}
	else if(C == 'n')
	{

	}
	else if(C >= '0' && C <= '9')
	{

	}
	else
	{
		// error
	}
}

CJ_Variable *cj_parse_string(CJ_ParseData *parse_data)
{
	cj_parse_character(parse_data);

	CJ_String_Buffer string_buffer;
	const char *start = string_buffer.data;
	cj_string_buffer_create(&string_buffer);
	while(C != '"')
	{
		if(C == '\\')
		{
			cj_parse_character(parse_data);
			switch(C)
			{
				case '"':

			}
		}
		cj_parse_character(parse_data);
	}

}
