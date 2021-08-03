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

/* --- object --- */

typedef struct _JSON_Object_Element
{
	const char *name;
	uint8_t type;
	uint8_t _packing_bytes[7];
	uint64_t value;
} JSON_Object_Element;

#define C_JSON_INDEX_COUNT_C -1
#define C_JSON_INDEX_COUNT_M -2
#define C_JSON_INDEX_STRING_BUFFER -4
#define C_JSON_INDEX_HASH_FUNCTION -5

uint64_t _c_json_hash_default(const char *string);

/* --- array --- */

typedef C_JSON_Variable JSON_Array_Element;

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
	c_json_error_callback error_callback;
	char error_message[1024];
	const char *json_type_strings[C_JSON_TYPE_COUNT + 1];
} JSON_GlobalData;

extern JSON_GlobalData *g_c_json_data;

#endif