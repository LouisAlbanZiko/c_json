#ifndef _c_json_H_
#define _c_json_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* --- init --- */
void c_json_init();
void c_json_terminate();

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

typedef enum _C_JSON_ErrorType
{
	C_JSON_ERROR_TYPE_INCORRECT_TYPE = 1,
	C_JSON_ERROR_TYPE_OUT_OF_BOUNDS,
	C_JSON_ERROR_TYPE_NEW_SIZE_TOO_SMALL
} C_JSON_ErrorType;

/* --- C_JSON_Variable --- */

typedef struct _C_JSON_Variable
{
	uint8_t type;
	uint8_t _packing_bytes[7];
	uint64_t value;
} C_JSON_Variable;

void c_json_variable_copy(C_JSON_Variable *dst, C_JSON_Variable *src);
void c_json_variable_destroy(C_JSON_Variable *value);

typedef enum _C_JSON_Type
{
	C_JSON_TYPE_NONE = 0,
	C_JSON_TYPE_STRING,
	C_JSON_TYPE_INT,
	C_JSON_TYPE_FLOAT,
	C_JSON_TYPE_BOOL,
	C_JSON_TYPE_NULL,
	C_JSON_TYPE_OBJECT,
	C_JSON_TYPE_ARRAY,
	C_JSON_TYPE_COUNT
} C_JSON_Type;

#define C_JSON_DEFAULT 0

/* --- C_JSON_String --- */

typedef const char *C_JSON_String;

void c_json_string_create(C_JSON_Variable *value_dst, const char *string);
void c_json_string_copy(C_JSON_Variable *dst, C_JSON_Variable *src);
uint64_t c_json_string_is_equal(C_JSON_Variable *val1, C_JSON_Variable *val2);
void c_json_string_destroy(C_JSON_Variable *value);

/* --- C_JSON_Object --- */

typedef uint64_t *C_JSON_Object;

typedef uint64_t (*c_json_hash_function)(const char *string);

void c_json_object_create(C_JSON_Variable *value_dst, uint64_t initial_length);
C_JSON_Variable c_json_object_get(C_JSON_Variable *obj, const char *name);
void c_json_object_resize(C_JSON_Variable *obj, uint64_t new_size);
void c_json_object_copy(C_JSON_Variable *dst, C_JSON_Variable *src);
void c_json_object_insert(C_JSON_Variable *obj, const char *name, C_JSON_Variable value);
void c_json_object_attach(C_JSON_Variable *obj, const char *name, C_JSON_Variable value);
void c_json_object_remove(C_JSON_Variable *obj, const char *name);
C_JSON_Variable c_json_object_detach(C_JSON_Variable *obj, const char *name);
void c_json_object_destroy(C_JSON_Variable *obj);

/* --- C_JSON_Array --- */

typedef uint64_t *C_JSON_Array;

void c_json_array_create(C_JSON_Variable *array, uint64_t initial_length);
C_JSON_Variable c_json_array_get(C_JSON_Variable *array, uint64_t index);
void c_json_array_resize(C_JSON_Variable *array, uint64_t new_length);
void c_json_array_copy(C_JSON_Variable *dst, C_JSON_Variable *src);
void c_json_array_push(C_JSON_Variable *array, C_JSON_Variable value);
void c_json_array_attach(C_JSON_Variable *array, C_JSON_Variable value);
void c_json_array_remove(C_JSON_Variable *array, uint64_t index);
C_JSON_Variable c_json_array_detach(C_JSON_Variable *array, uint64_t index);
void c_json_array_destroy(C_JSON_Variable *array);

/* --- util --- */

C_JSON_Variable c_json_parse(const char *string);
const char *c_json_stringify(C_JSON_Variable value);

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