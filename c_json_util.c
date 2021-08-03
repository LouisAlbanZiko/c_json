#include "internal.h"

JSON_GlobalData *g_c_json_data = NULL;

void c_json_init()
{
	if (g_c_json_data == NULL)
	{
		g_c_json_data = malloc(sizeof(*g_c_json_data));
		g_c_json_data->error_callback = NULL;
		g_c_json_data->json_type_strings[C_JSON_TYPE_NONE] = "C_JSON_TYPE_NONE";
		g_c_json_data->json_type_strings[C_JSON_TYPE_STRING] = "C_JSON_TYPE_STRING";
		g_c_json_data->json_type_strings[C_JSON_TYPE_INT] = "C_JSON_TYPE_INT";
		g_c_json_data->json_type_strings[C_JSON_TYPE_FLOAT] = "C_JSON_TYPE_FLOAT";
		g_c_json_data->json_type_strings[C_JSON_TYPE_BOOL] = "C_JSON_TYPE_BOOL";
		g_c_json_data->json_type_strings[C_JSON_TYPE_NULL] = "C_JSON_TYPE_NULL";
		g_c_json_data->json_type_strings[C_JSON_TYPE_OBJECT] = "C_JSON_TYPE_OBJECT";
		g_c_json_data->json_type_strings[C_JSON_TYPE_ARRAY] = "C_JSON_TYPE_ARRAY";
		g_c_json_data->json_type_strings[C_JSON_TYPE_COUNT] = "C_JSON_TYPE_UNKNOWN";

	}
}

void c_json_terminate()
{
	free(g_c_json_data);
}

void c_json_set_error_callback(c_json_error_callback error_callback)
{
	if (error_callback != NULL && g_c_json_data != NULL)
		g_c_json_data->error_callback = error_callback;
}

void _c_json_make_error(uint32_t severity, uint32_t type, const char *format, ...)
{
	if (g_c_json_data != NULL && g_c_json_data->error_callback != NULL)
	{
		va_list va_args;
		va_start(va_args, format);

		vsprintf(g_c_json_data->error_message, format, va_args);

		g_c_json_data->error_callback(severity, type, g_c_json_data->error_message);

		va_end(va_args);
	}
	else
	{
		fprintf(stderr, "[C_JSON] No error callback is set but an error occured.\n");
	}
}

const char *_c_json_json_type_string(uint8_t type)
{
	if(type > C_JSON_TYPE_COUNT)
	{
		return g_c_json_data->json_type_strings[C_JSON_TYPE_COUNT];
	}
	else
	{
		return g_c_json_data->json_type_strings[type];
	}

}

/* --- JSON_StringBuffer --- */

void c_json_string_buffer_create(JSON_StringBuffer *buffer_dst, uint32_t initial_size)
{
	initial_size = (initial_size == C_JSON_DEFAULT) * C_JSON_DEFAULT_STRING_BUFFER_LENGTH + initial_size;
	buffer_dst->size_c = 0;
	buffer_dst->size_m = initial_size;
	buffer_dst->data = malloc(sizeof(*buffer_dst->data) * initial_size);
}

void c_json_string_buffer_insert(JSON_StringBuffer *buffer, char c)
{
	if (buffer->size_c == buffer->size_m)
	{
		buffer->size_m *= 2;
		buffer = realloc(buffer, buffer->size_m);
	}
	buffer->data[buffer->size_c] = c;
	buffer->size_c++;
}

void c_json_string_buffer_end_string(JSON_StringBuffer *buffer)
{
	c_json_string_buffer_insert(buffer, '\0');
}

void c_json_string_buffer_destroy(JSON_StringBuffer *buffer)
{
	free(buffer->data);
}