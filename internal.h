#ifndef _C_JSON_INTERNAL_H_
#define _C_JSON_INTERNAL_H_

#include "c_json.h"

// string_buffer

typedef struct _CJ_String_Buffer
{
	uint32_t count_c;
	uint32_t count_m;
	char *data;
} CJ_String_Buffer;

#define C_JSON_DEFAULT_STRING_BUFFER_LENGTH 64

void cj_string_buffer_create(CJ_String_Buffer *buffer);
void cj_string_buffer_insert(CJ_String_Buffer *buffer, const char *string);
char *cj_string_buffer_current(CJ_String_Buffer *buffer);
void cj_string_buffer_destroy(CJ_String_Buffer *buffer);

// variable

typedef struct _CJ_Variable
{
	uint64_t type;
	uint64_t value;
} CJ_Variable;

// object

typedef struct _CJ_Object_Element
{
	const char *name;
	CJ_Variable *variable;
} CJ_Object_Element;

typedef struct _CJ_Object
{
	uint64_t type;
	CJ_String_Buffer string_buffer;
	uint64_t count_c;
	uint64_t count_m;
	uint64_t hash_mask;
	CJ_Object_Element *elements;
} CJ_Object;

#define C_JSON_DEFAULT_OBJECT_LENGTH 16

// array

typedef struct _CJ_Array_Element
{
	uint64_t name;
	CJ_Variable *variable;
} CJ_Array_Element;

typedef struct _CJ_Array
{
	uint64_t type;
	uint64_t count_c;
	uint64_t count_m;
	uint64_t hash_mask;
	CJ_Array_Element *elements;
} CJ_Array;

#define C_JSON_DEFAULT_ARRAY_LENGTH 16

// hash function

uint32_t hashlittle(const void *key, size_t length, uint32_t initval);

// string

typedef struct _CJ_String
{
	uint64_t type;
	const char *value;
} CJ_String;

// int

typedef struct _CJ_Integer
{
	uint64_t type;
	int64_t value;
} CJ_Integer;

// float

typedef struct _CJ_Float
{
	uint64_t type;
	double value;
} CJ_Float;

// bool

typedef struct _CJ_Bool
{
	uint64_t type;
	uint64_t value;
} CJ_Bool;



#endif