#ifndef _c_json_INTERNAL_H_
#define _c_json_INTERNAL_H_

#include "c_json.h"

#include <string.h>
#include <math.h>
#include <stdarg.h>

/* --- string_buffer --- */

typedef struct _JSON_StringBuffer
{
	uint32_t size_c;
	uint32_t size_m;
	char *data;
} JSON_StringBuffer;
/* 
	size_c()
	size_m()
	data()
*/

void c_json_string_buffer_create(JSON_StringBuffer *buffer_dst, uint32_t initial_size);
/*
	buffer_dst(The pointer to the memory to be modified.)
	initial_size(The initial length of the object to be created. If [C_JSON_DEFAULT] or 0 is passed the value will be set to [C_JSON_DEFAULT_OBJECT_LENGTH])
	returns(void)
*/
void c_json_string_buffer_insert(JSON_StringBuffer *buffer, char c);
/*
	buffer(The [JSON_StringBuffer] in which the value will be inserted.)
	c(The character to be inserted in the buffer.)
	return(void)
*/
void c_json_string_buffer_end_string(JSON_StringBuffer *buffer);
/*
	buffer(The [JSON_StringBuffer] for which the string will be ended)
	returns(void)
*/

void c_json_string_buffer_destroy(JSON_StringBuffer *buffer);
/*
	buffer(The [JSON_StringBuffer] to free memmory from.)
	return(void)
*/

/* --- --- */

/* --- C_JSON_Variable --- */

typedef struct _C_JSON_Variable
{
	uint8_t type;
	uint8_t _packing_bytes[7];
	uint64_t value;
} C_JSON_Variable;

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

/* --- object --- */

typedef uint64_t (*c_json_hash_function)(const char *);

typedef struct _C_JSON_Object_Element
{
	const char *name;
	C_JSON_Variable *variable;
} C_JSON_Object_Element;

typedef struct _C_JSON_Object
{
	c_json_hash_function hash_function;
	JSON_StringBuffer buffer;
	uint64_t count_m;
	uint64_t count_c;
	C_JSON_Object_Element elements[];
} C_JSON_Object;

uint64_t _c_json_hash_default(const char *string);

/* --- array --- */

typedef C_JSON_Variable C_JSON_Array_Element;

typedef struct _C_JSON_Array
{
	JSON_StringBuffer buffer;
	uint64_t count_m;
	uint64_t count_c;
	C_JSON_Array_Element elements[];
} C_JSON_Array;

/* --- parse --- */

typedef struct _JSON_ParseData
{
	const char *current;
	const char *end;
	uint32_t line;
	uint32_t char_in_line;
	JSON_StringBuffer *string_buffer;
} JSON_ParseData;

void c_json_parse_char(JSON_ParseData *parse_data);
void c_json_parse_whitespace(JSON_ParseData *parse_data);

void c_json_parse_value(JSON_ParseData *parse_data, C_JSON_Variable *value_dst);
void c_json_parse_string(JSON_ParseData *parse_data, C_JSON_Variable *value_dst);
void c_json_parse_number(JSON_ParseData *parse_data, C_JSON_Variable *value_dst);
void c_json_parse_object(JSON_ParseData *parse_data, C_JSON_Variable *value_dst);
void c_json_parse_array(JSON_ParseData *parse_data, C_JSON_Variable *value_dst);

/* --- global_data --- */

void _c_json_make_error(uint32_t severity, uint32_t type, const char *format, ...);
const char *_c_json_json_type_string(uint8_t type);

typedef struct _JSON_GlobalData
{
	const char *json_type_strings[C_JSON_TYPE_COUNT + 1];
	uint64_t default_object_length;
	uint64_t default_array_length;
	uint64_t default_string_buffer_length;
	c_json_error_callback error_callback;
	char error_message[1024];
} JSON_GlobalData;

extern JSON_GlobalData *g_c_json_data;

#endif