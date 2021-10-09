#ifndef _C_JSON_INTERNAL_H_
#define _C_JSON_INTERNAL_H_

#include "c_json.h"

#include <c_log/c_log.h>
#include <c_mem/c_mem.h>

#include <setjmp.h>
#include <stdarg.h>

// CJ_Variable heap
extern CM_Heap *g_cj_heap_variable;
extern CM_HeapString *g_cj_heap_string;

// variable

typedef struct _CJ_Variable
{
	uint64_t type;
	uint64_t value;
} _CJ_Variable;

CJ_Variable *_cj_variable_alloc();
void _cj_variable_free(CJ_Variable *var);

// object

typedef struct _CJ_Object_Element
{
	const char *name;
	CJ_Variable *variable;
} CJ_Object_Element;

typedef struct _CJ_Object
{
	uint64_t type;
	CM_HeapString *name_heap;
	uint64_t count_c;
	uint64_t count_m;
	uint64_t hash_mask;
	CJ_Object_Element *elements;
} _CJ_Object;

#define C_JSON_DEFAULT_OBJECT_LENGTH 16

// array

typedef struct _CJ_Array_Element
{
	CJ_Variable *variable;
} CJ_Array_Element;

typedef struct _CJ_Array
{
	uint64_t type;
	uint64_t count_c;
	uint64_t count_m;
	CJ_Array_Element *elements;
} _CJ_Array;

#define C_JSON_DEFAULT_ARRAY_LENGTH 16

// hash function

uint32_t hashlittle(const void *key, size_t length, uint32_t initval);

// string
typedef struct _CJ_String
{
	uint64_t type;
	char *value;
} _CJ_String;

// int
typedef struct _CJ_Integer
{
	uint64_t type;
	int64_t value;
} _CJ_Integer;

// float
typedef struct _CJ_Float
{
	uint64_t type;
	double value;
} _CJ_Float;

// bool
typedef struct _CJ_Bool
{
	uint64_t type;
	uint64_t value;
} _CJ_Bool;

// error
extern cj_error_callback _cj_error_callback;
extern uint32_t _cj_error_callback_print;
extern CL_Logger *_cj_error_logger;
void _cj_make_error(uint64_t error_type, const char *format, ...);

#endif