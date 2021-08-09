#ifndef _c_json_H_
#define _c_json_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* --- init --- */
void _c_json_init(
	uint64_t default_object_length,
	uint64_t default_array_length,
	uint64_t default_string_buffer_length
);
#define c_json_init() _c_json_init(C_JSON_DEFAULT_OBJECT_LENGTH, C_JSON_DEFAULT_ARRAY_LENGTH, C_JSON_DEFAULT_STRING_BUFFER_LENGTH)
void c_json_terminate();

/* --- C_JSON_Variable --- */
typedef struct _C_JSON_Variable C_JSON_Variable;

C_JSON_Variable *c_json_string_create(const char *value);
C_JSON_Variable *c_json_string_copy(C_JSON_Variable *string);
void c_json_string_destroy(C_JSON_Variable *string);

C_JSON_Variable *c_json_integer_create(int64_t value);
C_JSON_Variable *c_json_integer_copy(C_JSON_Variable *integer);
void c_json_integer_destroy(C_JSON_Variable *integer);

C_JSON_Variable *c_json_float_create(double value);
C_JSON_Variable *c_json_float_copy(C_JSON_Variable *float_var);
void c_json_float_destroy(C_JSON_Variable *float_var);

C_JSON_Variable *c_json_bool_create(uint64_t value);
C_JSON_Variable *c_json_bool_copy(C_JSON_Variable *boolean);
void c_json_bool_destroy(C_JSON_Variable *boolean);

C_JSON_Variable *c_json_null_create();
C_JSON_Variable *c_json_null_copy(C_JSON_Variable *null);
void c_json_null_destroy(C_JSON_Variable *null);

C_JSON_Variable *c_json_object_create(uint64_t initial_length);
C_JSON_Variable *c_json_object_copy(C_JSON_Variable *object);
void c_json_object_resize(C_JSON_Variable *object, uint64_t new_length);
void c_json_object_attach(C_JSON_Variable *object, const char *name, C_JSON_Variable *variable);
void c_json_object_push(C_JSON_Variable *object, const char *name, C_JSON_Variable *variable);
C_JSON_Variable *c_json_object_detach(C_JSON_Variable *object, const char *name);
void c_json_object_remove(C_JSON_Variable *object, const char *name);
void c_json_object_destroy(C_JSON_Variable *object);

C_JSON_Variable *c_json_array_create(uint64_t initial_length);
C_JSON_Variable *c_json_array_copy(C_JSON_Variable *array);
void c_json_array_attach(C_JSON_Variable *object, C_JSON_Variable *variable);
void c_json_array_push(C_JSON_Variable *object, C_JSON_Variable *variable);
void c_json_array_destroy(C_JSON_Variable *array);

C_JSON_Variable *c_json_variable_copy(C_JSON_Variable *variable);
void c_json_variable_destroy(C_JSON_Variable *variable);

#define C_JSON_DEFAULT 0

/* --- error --- */
typedef void (*c_json_error_callback)(uint32_t severity, uint32_t type, const char *message);
void c_json_set_error_callback(c_json_error_callback error_callback);

typedef enum _C_JSON_ErrorSeverity
{
	C_JSON_ERROR_SEVERITY_FATAL = 0,
	C_JSON_ERROR_SEVERITY_ERROR,
	C_JSON_ERROR_SEVERITY_WARN,
	C_JSON_ERROR_SEVERITY_INFO,
	C_JSON_ERROR_SEVERITY_TRACE
} C_JSON_ErrorSeverity;

typedef enum _C_JSON_Error
{
	C_JSON_ERROR_INCORRECT_TYPE = 1,
	C_JSON_ERROR_OUT_OF_BOUNDS,
	C_JSON_ERROR_NEW_SIZE_TOO_SMALL
} C_JSON_Error;

/* --- external_defines --- */

#ifndef C_JSON_DEFAULT_OBJECT_LENGTH
	#define C_JSON_DEFAULT_OBJECT_LENGTH 8
#endif

#ifndef C_JSON_DEFAULT_ARRAY_LENGTH
	#define C_JSON_DEFAULT_ARRAY_LENGTH 8
#endif

#ifndef C_JSON_DEFAULT_STRING_BUFFER_LENGTH
	#define C_JSON_DEFAULT_STRING_BUFFER_LENGTH 64
#endif

#endif