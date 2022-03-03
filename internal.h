#ifndef _C_JSON_INTERNAL_H_
#define _C_JSON_INTERNAL_H_

#include "c_json.h"

typedef struct _CJ_Variable
{
	uint64_t type;
	uint64_t value;
} _CJ_Variable;

// null
typedef struct _CJ_Null
{
	uint64_t type;
	uint64_t value;
} _CJ_Null;

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

// string
typedef struct _CJ_String
{
	uint64_t type;
	CM_String value;
} _CJ_String;

// object
typedef struct _CJ_Object
{
	uint64_t type;
	CM_HashMap *map;
} _CJ_Object;

// array
typedef struct _CJ_Array
{
	uint64_t type;
	CM_UnorderedSet *set;
} _CJ_Array;

// error
typedef enum _CJ_ErrorType
{
	CJ_ERROR_NONE = 0,
	CJ_ERROR_UNEXPECTED_TOKEN,
	CJ_ERROR_UNKNOWN_CONTROL_CHARACTER,
	CJ_ERROR_VARIABLE_NULL,
	CJ_ERROR_NOT_INITIALIZED,
	CJ_ERROR_STRING_NULL
} CJ_ErrorType;

void _cj_make_error(uint64_t error_type, const char *format, ...);

#endif