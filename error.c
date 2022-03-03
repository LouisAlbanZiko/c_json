#include "internal.h"

#include <stdarg.h>

#define ERROR_STRING_SIZE ((uint64_t)1024)

char _cj_error_string[ERROR_STRING_SIZE];

CM_String cj_get_last_error()
{
	CM_String string =
	{
		.data = _cj_error_string,
		.length = strlen(_cj_error_string)
	};
	return string;
}

void _cj_make_error(uint64_t error_type, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	vsprintf_s(_cj_error_string, ERROR_STRING_SIZE, format, args);
	
	va_end(args);
}