#include "internal.h"

#include <stdarg.h>

#define ERROR_STRING_SIZE ((uint64_t)1024)

uint64_t _CJ_Error_Type = 0;
char _CJ_Error_String[ERROR_STRING_SIZE];

CJ_Error CJ_Get_Last_error()
{
	CJ_Error error =
	{
		.error_type = _CJ_Error_Type,
		.message =_CJ_Error_String
	};
	return error;
}

void _CJ_Make_Error(uint64_t error_type, const char *format, ...)
{
	_CJ_Error_Type = error_type;

	va_list args;
	va_start(args, format);

	vsprintf_s(_CJ_Error_String, ERROR_STRING_SIZE, format, args);
	
	va_end(args);
}