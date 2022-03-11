#ifndef _C_JSON_H_
#define _C_JSON_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <c_core/c_core.h>

typedef enum CJ_VariableType
{
	CJ_TYPE_NULL = 0,
	CJ_TYPE_INTEGER,
	CJ_TYPE_FLOAT,
	CJ_TYPE_BOOL,
	CJ_TYPE_STRING,
	CJ_TYPE_OBJECT,
	CJ_TYPE_ARRAY,
	_CJ_TYPE_COUNT
} CJ_VariableType;

typedef struct CJ_Variable
{
	const uint64_t type;
	const uint64_t value;
} CJ_Variable;

CJ_Variable *cj_variable_copy(CJ_Variable *var);
void cj_variable_destroy(CJ_Variable *variable);

uint64_t cj_variable_type(CJ_Variable *variable);

// null
typedef struct CJ_Null
{
	const uint64_t type;
	const uint64_t value;
} CJ_Null;

CJ_Null *cj_null_create();
void cj_null_destroy(CJ_Null *var);

// integer
typedef struct CJ_Integer
{
	const uint64_t type;
	int64_t value;
} CJ_Integer;

CJ_Integer *cj_integer_create(int64_t value);
CJ_Integer *cj_integer_copy(CJ_Integer *var);
void cj_integer_destroy(CJ_Integer *var);

void cj_integer_set(CJ_Integer *var, int64_t value);
int64_t cj_integer_get(CJ_Integer *var);

// float
typedef struct CJ_Float
{
	const uint64_t type;
	double value;
} CJ_Float;

CJ_Float *cj_float_create(double value);
CJ_Float *cj_float_copy(CJ_Float *var);
void cj_float_destroy(CJ_Float *var);

void cj_float_set(CJ_Float *var, double value);
double cj_float_get(CJ_Float *var);

// boolean
typedef struct CJ_Bool
{
	const uint64_t type;
	uint64_t value;
} CJ_Bool;

#define CJ_FALSE 0
#define CJ_TRUE 1

CJ_Bool *cj_bool_create(uint64_t value);
CJ_Bool *cj_bool_copy(CJ_Bool *var);
void cj_bool_destroy(CJ_Bool *var);

void cj_bool_set(CJ_Bool *var, uint64_t value);
uint64_t cj_bool_get(CJ_Bool *var);

// string
typedef struct CJ_String
{
	const uint64_t type;
	const char *const value;
	const uint64_t length;
} CJ_String;

CJ_String *cj_string_create(CC_String value);
CJ_String *cj_string_copy(CJ_String *var);
void cj_string_destroy(CJ_String *var);

void cj_string_set(CJ_String *string, CC_String value);
CC_String cj_string_get(CJ_String *string);

// object
typedef struct CJ_Object
{
	const uint64_t type;
} CJ_Object;

CJ_Object *cj_object_create();
CJ_Object *cj_object_copy(CJ_Object *var);
void cj_object_destroy(CJ_Object *var);

uint64_t cj_object_count(CJ_Object *var);
void cj_object_attach(CJ_Object *object, CC_String name, CJ_Variable *var);
CJ_Variable *cj_object_detach(CJ_Object *object, CC_String name);
CJ_Variable *cj_object_get(CJ_Object *object, CC_String name);

typedef struct CJ_Object_Iterator
{
	const char *const name;
	const uint64_t name_length;
	const CJ_Variable *var;
} CJ_Object_Iterator;

CJ_Object_Iterator *cj_object_iterator_begin(CJ_Object *object);
CJ_Object_Iterator *cj_object_iterator_next(CJ_Object *object, CJ_Object_Iterator *iterator);
CJ_Object_Iterator *cj_object_iterator_end(CJ_Object *object);

// array
typedef struct CJ_Array
{
	const uint64_t type;
} CJ_Array;

CJ_Array *cj_array_create();
CJ_Array *cj_array_copy(CJ_Array *var);
void cj_array_destroy(CJ_Array *var);

uint64_t cj_array_count(CJ_Array *array);
void cj_array_attach(CJ_Array *array, CJ_Variable *variable);
CJ_Variable *cj_array_detach(CJ_Array *array, uint64_t index);
void cj_array_set(CJ_Array *array, uint64_t index, CJ_Variable *var);
CJ_Variable *cj_array_get(CJ_Array *array, uint64_t index);

typedef struct _CJ_Array_Iterator
{
	const CJ_Variable *var;
} CJ_Array_Iterator;

CJ_Array_Iterator *cj_array_iterator_start(CJ_Array *array);
CJ_Array_Iterator *cj_array_iterator_next(CJ_Array *array, CJ_Array_Iterator *iterator);
CJ_Array_Iterator *cj_array_iterator_end(CJ_Array *array);

// error
typedef struct CJ_Error
{
	uint64_t error_type;
	CC_String message;
} CJ_Error;
CJ_Error cj_get_last_error();

typedef enum _CJ_ErrorType
{
	CJ_ERROR_NONE = 0,
	CJ_ERROR_UNEXPECTED_TOKEN,
	CJ_ERROR_UNKNOWN_CONTROL_CHARACTER,
	CJ_ERROR_VARIABLE_NULL,
	CJ_ERROR_NOT_INITIALIZED,
	CJ_ERROR_STRING_NULL
} CJ_ErrorType;

// util
CJ_Variable *cj_parse(const char *string);
void cj_fprintf(FILE *file, const CJ_Variable *var);

#endif