#include "internal.h"

#include <setjmp.h>

typedef struct _CJ_ParseData
{
	const char *start;
	const char *current;
	const char *end;
	uint32_t line;
	uint32_t character_in_line;
	jmp_buf ex_buf;
} CJ_ParseData;

#define CJ_MAKE_PARSE_ERROR(type, ...)     \
	{                                      \
		_cj_make_error(type, __VA_ARGS__); \
		longjmp(parse_data->ex_buf, 1);    \
	}

#define C (parse_data->current[0])

void cj_parse_character(CJ_ParseData *parse_data);
void cj_parse_whitespace(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_value(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_string(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_number(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_object(CJ_ParseData *parse_data);
CJ_Variable *cj_parse_array(CJ_ParseData *parse_data);
uint32_t cj_parse_strcmp(const char *s1, const char *s2);

CJ_Variable *cj_parse(const char *string)
{
	CJ_ParseData parse_data =
	{
		.start = string,
		.current = string,
		.end = string + strlen(string),
		.line = 1,
		.character_in_line = 0 };

	CJ_Variable *variable = NULL;
	if (!setjmp(parse_data.ex_buf))
	{
		variable = cj_parse_value(&parse_data);
		return variable;
	}
	else
	{
		if (variable != NULL)
			cj_variable_destroy(variable);
		return NULL;
	}
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
	while (C == ' ' || C == '\t' || C == '\n' || C == '\r')
		cj_parse_character(parse_data);
}

CJ_Variable *cj_parse_value(CJ_ParseData *parse_data)
{
	CJ_Variable *variable = NULL;

	cj_parse_whitespace(parse_data);

	if (C == '"')
	{
		variable = cj_parse_string(parse_data);
	}
	else if (C == '{')
	{
		variable = cj_parse_object(parse_data);
	}
	else if (C == '[')
	{
		variable = cj_parse_array(parse_data);
	}
	else if (C == 't' || C == 'f')
	{
		uint32_t _true = cj_parse_strcmp("true", &C);
		uint32_t _false = cj_parse_strcmp("false", &C);
		if (_true)
		{
			for (uint32_t i = 0; i < 4; i++)
				cj_parse_character(parse_data);
			variable = (CJ_Variable *)cj_bool_create((uint64_t)1);
		}
		else if (_false)
		{
			for (uint32_t i = 0; i < 5; i++)
				cj_parse_character(parse_data);
			variable = (CJ_Variable *)cj_bool_create((uint64_t)0);
		}
		else
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected token '%s' on line %d, character %d.", &C, parse_data->line, parse_data->character_in_line);
		}
	}
	else if (C == 'n')
	{
		if (cj_parse_strcmp("null", &C))
		{
			for (uint32_t i = 0; i < 4; i++)
				cj_parse_character(parse_data);
			variable = (CJ_Variable *)cj_null_create();
		}
		else
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected token '%s' on line %d, character %d.", &C, parse_data->line, parse_data->character_in_line);
		}
	}
	else if ((C >= '0' && C <= '9') || C == '-')
	{
		variable = cj_parse_number(parse_data);
	}
	else
	{
		CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected character '%c' on line %d, character %d.", C, parse_data->line, parse_data->character_in_line);
	}

	return variable;
}

CJ_Variable *cj_parse_string(CJ_ParseData *parse_data)
{
	cj_parse_character(parse_data);

	CM_StringBuffer *string_buffer = cm_string_buffer_create(128);
	while (C != '"')
	{
		char insert_char = C;
		if (C == '\\')
		{
			cj_parse_character(parse_data);
			insert_char = C;
			switch (C)
			{
			case '"':
			case '\\':
			case '/':
				insert_char = C;
				break;
			case 'b':
				insert_char = '\b';
				break;
			case 'f':
				insert_char = '\f';
				break;
			case 'n':
				insert_char = '\n';
				break;
			case 'r':
				insert_char = '\r';
				break;
			case 't':
				insert_char = '\t';
				break;
			case 'u':
				insert_char = ' ';
				for (uint32_t i = 0; i < 4; i++)
					cj_parse_character(parse_data);
				CJ_MAKE_PARSE_ERROR(CJ_ERROR_NONE, "Unicode isn't supported yet.");
				break;
			default:
				CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNKNOWN_CONTROL_CHARACTER, "Unknown control character '\\%c'.", C);
				break;
			}
		}
		cm_string_buffer_insert_char(string_buffer, insert_char);
		cj_parse_character(parse_data);
	}
	cj_parse_character(parse_data);

	CM_String string = cm_string_buffer_to_string_and_destroy(string_buffer);

	CJ_String *cj_str = cj_string_create(string);

	return (CJ_Variable *)cj_str;
}

CJ_Variable *cj_parse_number(CJ_ParseData *parse_data)
{

	int64_t sign = 1;
	int64_t nr = 0;
	int64_t mantis = 0;
	int64_t mantis_divisor = 1;
	int64_t exponent = 1;
	int64_t exponent_sign = 1;

	if (C == '-' || C == '+')
	{
		sign = (C == '-') * (-1) + (C == '+') * 1;
		cj_parse_character(parse_data);
	}
	while (C >= '0' && C <= '9')
	{
		nr *= 10;
		nr += C - '0';
		cj_parse_character(parse_data);
	}
	if (C == '.')
	{
		cj_parse_character(parse_data);
		while (C >= '0' && C <= '9')
		{
			mantis *= 10;
			mantis_divisor *= 10;
			mantis += C - '0';
			cj_parse_character(parse_data);
		}
	}
	if (C == 'e' || C == 'E')
	{
		exponent = 0;
		cj_parse_character(parse_data);
		if (C == '-' || C == '+')
		{
			exponent_sign = (C == '-') * (-1) + (C == '+') * 1;
			cj_parse_character(parse_data);
		}
		while (C >= '0' && C <= '9')
		{
			exponent *= 10;
			exponent += C - '0';
			cj_parse_character(parse_data);
		}
	}
	if (mantis_divisor == 1)
	{
		return (CJ_Variable *)cj_integer_create(sign * (int64_t)pow((double)nr, (double)exponent_sign * (double)exponent));
	}
	else
	{
		return (CJ_Variable *)cj_float_create((double)sign * pow((double)nr + (double)mantis / (double)mantis_divisor, (double)exponent * (double)exponent_sign));
	}
}

CJ_Variable *cj_parse_object(CJ_ParseData *parse_data)
{
	CJ_Object *object = cj_object_create();

	cj_parse_character(parse_data);
	cj_parse_whitespace(parse_data);
	uint32_t i = 0;
	while (C == '"')
	{
		i++;
		// parse name
		CJ_String *name = (CJ_String *)cj_parse_string(parse_data);
		if (name == NULL)
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected character while parsing cj_object '%c' on line %d, character %d.", C, parse_data->line, parse_data->character_in_line);
		}

		cj_parse_character(parse_data);
		cj_parse_whitespace(parse_data);
		if (C == ':')
		{
			cj_parse_character(parse_data);
		}
		cj_parse_whitespace(parse_data);

		CJ_Variable *var = cj_parse_value(parse_data);
		cj_object_attach(object, cj_string_get(name), var);

		cj_parse_whitespace(parse_data);
		if (C == ',')
		{
			cj_parse_character(parse_data);
			cj_parse_whitespace(parse_data);
		}
		else if (C == '}')
		{
			break;
		}
		else
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected character while parsing cj_object '%c' on line %d, character %d.", C, parse_data->line, parse_data->character_in_line);
		}
	}

	cj_parse_character(parse_data);

	return (CJ_Variable *)object;
}

CJ_Variable *cj_parse_array(CJ_ParseData *parse_data)
{
	CJ_Array *array = cj_array_create();

	cj_parse_character(parse_data);
	cj_parse_whitespace(parse_data);
	while (1)
	{
		CJ_Variable *var = cj_parse_value(parse_data);
		cj_array_attach(array, var);

		cj_parse_whitespace(parse_data);
		if (C == ',')
		{
			cj_parse_character(parse_data);
			cj_parse_whitespace(parse_data);
		}
		else if (C == ']')
		{
			break;
		}
		else
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected character while parsing cj_array '%c' on line %d, character %d.", C, parse_data->line, parse_data->character_in_line);
		}
	}

	cj_parse_character(parse_data);

	return (CJ_Variable *)array;
}

uint32_t cj_parse_strcmp(const char *s1, const char *s2)
{
	uint64_t length = strlen(s1);
	uint64_t i;
	for (i = 0; i < length && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			return 0;
		}
	}
	if (s2[i] == '\0' && i != length)
		return 0;
	else
		return 1;
}