#include "internal.h"

#define C *parse_data->current

void c_json_parse_char(JSON_ParseData *parse_data)
{
	parse_data->char_in_line++;
	uint32_t is_new_line = C == '\n';
	parse_data->char_in_line = (parse_data->char_in_line + 1) * !is_new_line;
	parse_data->line += is_new_line;
	parse_data->current++;
}

void c_json_parse_whitespace(JSON_ParseData *parse_data)
{
	while(C == ' ' || C == '\t' || C == '\n' || C == '\r')
		c_json_parse_char(parse_data);
}

void c_json_parse_value(JSON_ParseData *parse_data, C_JSON_Variable *value_dst)
{
	c_json_parse_whitespace(parse_data);
	switch(C)
	{
		case '{':
			c_json_parse_object(parse_data, value_dst);
			break;
		case '[':
			c_json_parse_array(parse_data, value_dst);
			break;
		case '"':
			c_json_parse_string(parse_data, value_dst);
			break;
		case 't':
			if(((uint32_t *)parse_data->current)[0] == ((uint32_t *) "true")[0])
			{
				value_dst->type = C_JSON_TYPE_BOOL;
				value_dst->value = 1;
			}
			break;
		case 'f':
			static const char const *_false_string = "false";
			if(((uint32_t *)parse_data->current)[0] == ((uint32_t *) _false_string)[0] && parse_data->current[4] == _false_string[4])
			{
				value_dst->type = C_JSON_TYPE_BOOL;
				value_dst->value = 0;
			}
			break;
		case 'n':
			if(((uint32_t *)parse_data->current)[0] == ((uint32_t *) "null")[0])
			{
				value_dst->type = C_JSON_TYPE_NULL;
				value_dst->value = 0;
			}
			break;
		default:
			if((C < '9' + 1 && C > '0' - 1) || C == '-')
			{
				c_json_parse_number(parse_data, value_dst);
			}
			else
			{
				// error no valid value found
			}
	}
}

void c_json_parse_string(JSON_ParseData *parse_data, C_JSON_Variable *value_dst)
{
	value_dst->type = C_JSON_TYPE_STRING;
	c_json_parse_char(parse_data);

	while(C != '"')
	{
		if(C == '\\')
		{
			c_json_parse_char(parse_data);
			switch(C)
			{
				case '\\':
				case '/':
				case '"':
					c_json_string_buffer_insert(parse_data->string_buffer, C);
					break;
				case 'b':
					break;
				case 'f':
					break;
				case 'n':
					c_json_string_buffer_insert(parse_data->string_buffer, '\n');
					break;
				case 'r':
					c_json_string_buffer_insert(parse_data->string_buffer, '\r');
					break;
				case 't':
					c_json_string_buffer_insert(parse_data->string_buffer, '\t');
					break;
				case 'u':
					c_json_parse_char(parse_data);
					// add unicode
				default:
					// error unknown control character
			}
		}
		else
		{
			c_json_string_buffer_insert(parse_data->string_buffer, C);
		}
		c_json_parse_char(parse_data);
	}
	c_json_string_buffer_end_string(parse_data->string_buffer);
	c_json_parse_char(parse_data);
}

void c_json_parse_number(JSON_ParseData *parse_data, C_JSON_Variable *value_dst)
{
	
	int64_t nr_sign = 1;
	if(C == '-')
	{
		nr_sign = -1;
		c_json_parse_char(parse_data);
	}
	int64_t nr_int = 0;
	while(C < '9' + 1 && C > '0' - 1)
	{
		nr_int *= 10;
		nr_int += C - '0';
		c_json_parse_char(parse_data);
	}
	if(C != '.')
	{
		value_dst->type = C_JSON_TYPE_INT;
		int64_t *output_int = (int64_t *)&value_dst->value;
		*output_int = nr_int * nr_sign;
	}
	else if(C == 'e' || C == 'E')
	{
		c_json_parse_char(parse_data);
		double exponent = 0;
		double exponent_sign = 1;
		if(C == '-')
		{
			exponent_sign = -1;
			c_json_parse_char(parse_data);
		}
		else if(C == '+')
		{
			exponent_sign = 1;
			c_json_parse_char(parse_data);
		}
		while(C < '9' + 1 && C > '0' - 1)
		{
			exponent *= 10;
			exponent += C - '0';
			c_json_parse_char(parse_data);
		}
		value_dst->type = C_JSON_TYPE_FLOAT;
		double *output_double = (double *)&value_dst->value;
		*output_double = pow(nr_int * nr_sign, exponent * exponent_sign);
	}
	else
	{
		c_json_parse_char(parse_data);

		double nr_double = (double) (nr_int);
		double dividor = 1;
		while(C < '9' + 1 && C > '0' - 1)
		{
			dividor /= 10;
			nr_double += (double) (C - '0') / dividor;
			c_json_parse_char(parse_data);
		}

		if(C == 'e' || C == 'E')
		{
			c_json_parse_char(parse_data);
			double exponent = 0;
			double exponent_sign = 1;
			if(C == '-')
			{
				exponent_sign = -1;
				c_json_parse_char(parse_data);
			}
			else if(C == '+')
			{
				exponent_sign = 1;
				c_json_parse_char(parse_data);
			}
			while(C < '9' + 1 && C > '0' - 1)
			{
				exponent *= 10;
				exponent += C - '0';
				c_json_parse_char(parse_data);
			}
			value_dst->type = C_JSON_TYPE_FLOAT;
			double *output_double = (double *)&value_dst->value;
			*output_double = pow(nr_double * nr_sign, exponent * exponent_sign);
		}
		else
		{
			value_dst->type = C_JSON_TYPE_FLOAT;
			double *output_double = (double *)&value_dst->value;
			*output_double = nr_double * nr_sign;
		}
	}
}

void c_json_parse_object(JSON_ParseData *parse_data, C_JSON_Variable *value_dst)
{
	c_json_object_create(value_dst, C_JSON_DEFAULT);

	uint64_t *object_ptr = (uint64_t *)(value_dst->value);
	JSON_Object_Element *object_list = (JSON_Object_Element *)(object_ptr);

	c_json_parse_char(parse_data);
	c_json_parse_whitespace(parse_data);

	// parse
	while(C != '}')
	{
		c_json_parse_whitespace(parse_data);
		const char *name = NULL;
		if(C == '"')
		{
			C_JSON_Variable value;
			c_json_parse_string(parse_data, &value);
			name = (const char *)value.value;
		}
		else
		{
			// error
		}
		c_json_parse_whitespace(parse_data);
		if(C != ':')
		{
			// error
		}
		c_json_parse_whitespace(parse_data);
		C_JSON_Variable new_value;
		c_json_parse_value(parse_data, &new_value);
		c_json_object_insert(value_dst, name, new_value);

		c_json_parse_whitespace(parse_data);

		if(C == ',')
		{
			c_json_parse_char(parse_data);
		}
	}
	c_json_parse_char(parse_data);


}

void c_json_parse_array(JSON_ParseData *parse_data, C_JSON_Variable *value_dst)
{
	
}

C_JSON_Variable c_json_parse(const char *string)
{
	JSON_ParseData parse_data = 
	{
		.current = string,
		.end = string + strlen(string),
		.line = 0,
		.char_in_line = 0,
		.string_buffer = NULL
	};


}

