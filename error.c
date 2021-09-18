#include "internal.h"

cj_error_callback _cj_error_callback = NULL;
uint32_t _cj_error_callback_print = CJ_ERROR_PRINT_DISABLED;
CL_Logger *_cj_error_logger = NULL;

void _cj_make_error(uint64_t error_type, const char *format, ...)
{
	va_list va_args;
	va_start(va_args, format);

	char message[1024];
	vsprintf(message, format, va_args);
	if (_cj_error_callback != NULL)
	{
		_cj_error_callback(error_type, message);
	}
	if (_cj_error_callback_print == CJ_ERROR_PRINT_ENABLED)
	{
		CL_LOG_ERROR(_cj_error_logger, "%s", message);
	}

	va_end(va_args);
}

void cj_error_callback_set(cj_error_callback callback)
{
	_cj_error_callback = callback;
}

void cj_error_callback_print_set(uint32_t should_print)
{
	if (_cj_error_callback_print != should_print)
	{
		if (_cj_error_callback_print == CJ_ERROR_PRINT_ENABLED)
		{
			CL_LOGGER_DESTROY(_cj_error_logger);
			_cj_error_logger = NULL;
		}
		else
		{
			_cj_error_logger = CL_LOGGER_CREATE(1, "C_JSON", CL_DEFAULT_PATTERN);
			CL_LOGGER_OUTPUT_ADD(_cj_error_logger, stdout, CL_COLOR_ENABLED);
		}
	}
	_cj_error_callback_print = should_print;
}
