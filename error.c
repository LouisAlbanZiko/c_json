#include "internal.h"

#include <stdarg.h>

#define ERROR_STRING_SIZE ((uint64_t)1024)

uint64_t _cj_error_type = 0;
char _cj_error_string[ERROR_STRING_SIZE];

CJ_Error cj_get_last_error()
{
	CJ_Error error =
	{
		.error_type = _cj_error_type,
		.message =
		{
			.data = _cj_error_string,
			.length = strlen(_cj_error_string)
		}
	};
	return error;
}

void _cj_make_error(uint64_t error_type, const char *format, ...)
{
	_cj_error_type = error_type;

	va_list args;
	va_start(args, format);

	vsprintf_s(_cj_error_string, ERROR_STRING_SIZE, format, args);
	
	va_end(args);
}