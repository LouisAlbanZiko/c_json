#ifndef _C_JSON_INTERNAL_H_
#define _C_JSON_INTERNAL_H_

#include <c_json/c_json.h>

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
	char *value;
} _CJ_String;

// object
typedef struct _CJ_Object
{
	uint64_t type;
	CC_HashMapString *map;
} _CJ_Object;

// array
typedef struct _CJ_Array
{
	uint64_t type;
	CC_UnorderedSet *set;
} _CJ_Array;

// error
void _CJ_Make_Error(uint64_t error_type, const char *format, ...);

#endif