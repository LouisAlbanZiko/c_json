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
		_CJ_Make_Error(type, __VA_ARGS__); \
		longjmp(parse_data->ex_buf, 1);    \
	}

#define C (parse_data->current[0])

void CJ_Parse_Character(CJ_ParseData *parse_data);
void CJ_Parse_Whitespace(CJ_ParseData *parse_data);
CJ_Variable *CJ_Parse_Value(CJ_ParseData *parse_data);
CJ_Variable *CJ_Parse_String(CJ_ParseData *parse_data);
CJ_Variable *CJ_Parse_Number(CJ_ParseData *parse_data);
CJ_Variable *CJ_Parse_Object(CJ_ParseData *parse_data);
CJ_Variable *CJ_Parse_Array(CJ_ParseData *parse_data);
uint32_t CJ_Parse_Strccp(const char *s1, const char *s2);

CJ_Variable *CJ_Parse(const char *string)
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
		variable = CJ_Parse_Value(&parse_data);
		return variable;
	}
	else
	{
		if (variable != NULL)
			CJ_Variable_Destroy(variable);
		return NULL;
	}
}

void CJ_Parse_Character(CJ_ParseData *parse_data)
{
	uint32_t is_new_line = C == '\n';
	parse_data->line += is_new_line;
	parse_data->character_in_line = !is_new_line * (parse_data->character_in_line + 1);
	parse_data->current++;
}

void CJ_Parse_Whitespace(CJ_ParseData *parse_data)
{
	while (C == ' ' || C == '\t' || C == '\n' || C == '\r')
		CJ_Parse_Character(parse_data);
}

CJ_Variable *CJ_Parse_Value(CJ_ParseData *parse_data)
{
	CJ_Variable *variable = NULL;

	CJ_Parse_Whitespace(parse_data);

	if (C == '"')
	{
		variable = CJ_Parse_String(parse_data);
	}
	else if (C == '{')
	{
		variable = CJ_Parse_Object(parse_data);
	}
	else if (C == '[')
	{
		variable = CJ_Parse_Array(parse_data);
	}
	else if (C == 't' || C == 'f')
	{
		uint32_t _true = CJ_Parse_Strccp("true", &C);
		uint32_t _false = CJ_Parse_Strccp("false", &C);
		if (_true)
		{
			for (uint32_t i = 0; i < 4; i++)
				CJ_Parse_Character(parse_data);
			variable = (CJ_Variable *)CJ_Bool_Create((uint64_t)1);
		}
		else if (_false)
		{
			for (uint32_t i = 0; i < 5; i++)
				CJ_Parse_Character(parse_data);
			variable = (CJ_Variable *)CJ_Bool_Create((uint64_t)0);
		}
		else
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected token '%s' on line %d, character %d.", &C, parse_data->line, parse_data->character_in_line);
		}
	}
	else if (C == 'n')
	{
		if (CJ_Parse_Strccp("null", &C))
		{
			for (uint32_t i = 0; i < 4; i++)
				CJ_Parse_Character(parse_data);
			variable = (CJ_Variable *)CJ_Null_Create();
		}
		else
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected token '%s' on line %d, character %d.", &C, parse_data->line, parse_data->character_in_line);
		}
	}
	else if ((C >= '0' && C <= '9') || C == '-')
	{
		variable = CJ_Parse_Number(parse_data);
	}
	else
	{
		CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected character '%c' on line %d, character %d.", C, parse_data->line, parse_data->character_in_line);
	}

	return variable;
}

CJ_Variable *CJ_Parse_String(CJ_ParseData *parse_data)
{
	CJ_Parse_Character(parse_data);

	CC_StringBuffer *string_buffer = CC_StringBuffer_Create(128);
	while (C != '"')
	{
		char insert_char = C;
		if (C == '\\')
		{
			CJ_Parse_Character(parse_data);
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
					CJ_Parse_Character(parse_data);
				CJ_MAKE_PARSE_ERROR(CJ_ERROR_NONE, "Unicode isn't supported yet.");
				break;
			default:
				CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNKNOWN_CONTROL_CHARACTER, "Unknown control character '\\%c'.", C);
				break;
			}
		}
		CC_StringBuffer_InsertChar(string_buffer, insert_char);
		CJ_Parse_Character(parse_data);
	}
	CJ_Parse_Character(parse_data);

	const char * string = CC_StringBuffer_ToStringAndDestroy(string_buffer, NULL);

	CJ_String *cj_str = CJ_String_Create(string);

	return (CJ_Variable *)cj_str;
}

CJ_Variable *CJ_Parse_Number(CJ_ParseData *parse_data)
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
		CJ_Parse_Character(parse_data);
	}
	while (C >= '0' && C <= '9')
	{
		nr *= 10;
		nr += C - '0';
		CJ_Parse_Character(parse_data);
	}
	if (C == '.')
	{
		CJ_Parse_Character(parse_data);
		while (C >= '0' && C <= '9')
		{
			mantis *= 10;
			mantis_divisor *= 10;
			mantis += C - '0';
			CJ_Parse_Character(parse_data);
		}
	}
	if (C == 'e' || C == 'E')
	{
		exponent = 0;
		CJ_Parse_Character(parse_data);
		if (C == '-' || C == '+')
		{
			exponent_sign = (C == '-') * (-1) + (C == '+') * 1;
			CJ_Parse_Character(parse_data);
		}
		while (C >= '0' && C <= '9')
		{
			exponent *= 10;
			exponent += C - '0';
			CJ_Parse_Character(parse_data);
		}
	}
	if (mantis_divisor == 1)
	{
		return (CJ_Variable *)CJ_Integer_Create(sign * (int64_t)pow((double)nr, (double)exponent_sign * (double)exponent));
	}
	else
	{
		return (CJ_Variable *)CJ_Float_Create((double)sign * pow((double)nr + (double)mantis / (double)mantis_divisor, (double)exponent * (double)exponent_sign));
	}
}

CJ_Variable *CJ_Parse_Object(CJ_ParseData *parse_data)
{
	CJ_Object *object = CJ_Object_Create();

	CJ_Parse_Character(parse_data);
	CJ_Parse_Whitespace(parse_data);
	uint32_t i = 0;
	while (C == '"')
	{
		i++;
		// parse name
		CJ_String *name = (CJ_String *)CJ_Parse_String(parse_data);
		if (name == NULL)
		{
			CJ_MAKE_PARSE_ERROR(CJ_ERROR_UNEXPECTED_TOKEN, "Unexpected character while parsing cj_object '%c' on line %d, character %d.", C, parse_data->line, parse_data->character_in_line);
		}

		CJ_Parse_Character(parse_data);
		CJ_Parse_Whitespace(parse_data);
		if (C == ':')
		{
			CJ_Parse_Character(parse_data);
		}
		CJ_Parse_Whitespace(parse_data);

		CJ_Variable *var = CJ_Parse_Value(parse_data);
		CJ_Object_Attach(object, CJ_String_Get(name), var);

		CJ_Parse_Whitespace(parse_data);
		if (C == ',')
		{
			CJ_Parse_Character(parse_data);
			CJ_Parse_Whitespace(parse_data);
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

	CJ_Parse_Character(parse_data);

	return (CJ_Variable *)object;
}

CJ_Variable *CJ_Parse_Array(CJ_ParseData *parse_data)
{
	CJ_Array *array = CJ_Array_Create();

	CJ_Parse_Character(parse_data);
	CJ_Parse_Whitespace(parse_data);
	if (C != ']')
	{
		while (1)
		{
			CJ_Variable *var = CJ_Parse_Value(parse_data);
			CJ_Array_Attach(array, var);

			CJ_Parse_Whitespace(parse_data);
			if (C == ',')
			{
				CJ_Parse_Character(parse_data);
				CJ_Parse_Whitespace(parse_data);
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
	}

	CJ_Parse_Character(parse_data);

	return (CJ_Variable *)array;
}

uint32_t CJ_Parse_Strccp(const char *s1, const char *s2)
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