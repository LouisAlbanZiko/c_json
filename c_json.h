#ifndef _C_JSON_H_
#define _C_JSON_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

enum CJ_Variable_Type
{
	CJ_TYPE_NULL = 0,
	CJ_TYPE_INT,
	CJ_TYPE_FLOAT,
	CJ_TYPE_BOOL,
	CJ_TYPE_STRING,
	CJ_TYPE_OBJECT,
	CJ_TYPE_ARRAY,
	CJ_TYPE_COUNT
};

// setup
void cj_init();
void cj_terminate();

// variable
typedef struct _CJ_Variable CJ_Variable;

CJ_Variable *cj_variable_copy(CJ_Variable *variable);
uint64_t cj_variable_type(CJ_Variable *variable);
uint64_t cj_variable_value(CJ_Variable *variable);
void cj_variable_destroy(CJ_Variable *variable);

// null
typedef struct _CJ_Null CJ_Null;

CJ_Null *cj_null_create();
void cj_null_destroy(CJ_Null *var);

// integer
typedef struct _CJ_Integer CJ_Integer;

CJ_Integer *cj_integer_create(int64_t value);
CJ_Integer *cj_integer_copy(CJ_Integer *integer);
void cj_integer_destroy(CJ_Integer *integer);

void cj_integer_set(CJ_Integer *integer, int64_t value);
int64_t cj_integer_get(CJ_Integer *integer);

// float
typedef struct _CJ_Float CJ_Float;

CJ_Float *cj_float_create(double value);
CJ_Float *cj_float_copy(CJ_Float *_float);
void cj_float_destroy(CJ_Float *_float);

void cj_float_set(CJ_Float *_float, double value);
double cj_float_get(CJ_Float *_float);

// bool
typedef struct _CJ_Bool CJ_Bool;

CJ_Bool *cj_bool_create(uint64_t value);
CJ_Bool *cj_bool_copy(CJ_Bool *bool);
void cj_bool_destroy(CJ_Bool *bool);

void cj_bool_set(CJ_Bool *bool, uint64_t value);
uint64_t cj_bool_get(CJ_Bool *bool);

// string
typedef struct _CJ_String CJ_String;

CJ_String *cj_string_create(const char *value);
CJ_String *cj_string_copy(CJ_String *string);
void cj_string_destroy(CJ_String *string);

void cj_string_set(CJ_String *string, const char *value);
const char *cj_string_get(CJ_String *string);

// object
typedef struct _CJ_Object CJ_Object;

CJ_Object *cj_object_create();
CJ_Object *cj_object_copy(CJ_Object *object);
void cj_object_destroy(CJ_Object *object);
uint64_t cj_object_count(CJ_Object *object);
void cj_object_attach(CJ_Object *object, const char *name, CJ_Variable *variable);
CJ_Variable *cj_object_detach(CJ_Object *object, const char *name);
CJ_Variable *cj_object_get(CJ_Object *object, const char *name);

typedef struct _CJ_Object_Iterator
{
	const char *name;
	const CJ_Variable *var;
} CJ_Object_Iterator;

CJ_Object_Iterator *cj_object_iterator_start(CJ_Object *object);
CJ_Object_Iterator *cj_object_iterator_next(CJ_Object *object, CJ_Object_Iterator *iterator);
CJ_Object_Iterator *cj_object_iterator_end(CJ_Object *object);

// array
typedef struct _CJ_Array CJ_Array;

CJ_Array *cj_array_create();
CJ_Array *cj_array_copy(CJ_Array *array);
void cj_array_destroy(CJ_Array *array);
uint64_t cj_array_count(CJ_Array *array);
void cj_array_attach(CJ_Array *array, CJ_Variable *variable);
CJ_Variable *cj_array_detach(CJ_Array *array, uint64_t index);
CJ_Variable *cj_array_get(CJ_Array *array, uint64_t index);

typedef struct _CJ_Array_Iterator
{
	const CJ_Variable *var;
} CJ_Array_Iterator;

CJ_Array_Iterator *cj_array_iterator_start(CJ_Array *array);
CJ_Array_Iterator *cj_array_iterator_next(CJ_Array *array, CJ_Array_Iterator *iterator);
CJ_Array_Iterator *cj_array_iterator_end(CJ_Array *array);

// util
CJ_Variable *cj_parse(const char *string);

typedef struct _CJ_Stringify_Options
{
	uint32_t padding;
	uint32_t number_options;
} CJ_Stringify_Options;
const char *cj_stringify(CJ_Variable *variable, CJ_Stringify_Options *options);

// error
typedef enum _CJ_ErrorType
{
	CJ_ERROR_NONE = 0,
	CJ_ERROR_UNEXPECTED_TOKEN,
	CJ_ERROR_UNKNOWN_CONTROL_CHARACTER,
	CJ_ERROR_VARIABLE_NULL
} CJ_ErrorType;
typedef void (*cj_error_callback)(uint64_t type, const char *message);
void cj_error_callback_set(cj_error_callback callback);
#define CJ_ERROR_PRINT_ENABLED 1
#define CJ_ERROR_PRINT_DISABLED 0
void cj_error_callback_print_set(uint32_t should_print);

// validation layer

#ifdef CJ_VALIDATION_LAYER

// variable
#define cj_variable_copy(variable) _vl_cj_variable_copy(variable)
#define cj_variable_type(variable) _vl_cj_variable_type(variable)
#define cj_variable_value(variable) _vl_cj_variable_value(variable)
#define cj_variable_destroy(variable) _vl_cj_variable_destroy(variable)

// null
#define cj_null_create() _vl_cj_null_create()
#define cj_null_destroy() _vl_cj_null_destroy()

// integer
#define cj_integer_create(value) _vl_cj_integer_create(value)
#define cj_integer_copy(integer) _vl_cj_integer_copy(integer)
#define cj_integer_destroy(integer) _vl_cj_integer_destroy(integer)

#define cj_integer_set(integer, value) _vl_cj_integer_set(integer, value)
#define cj_integer_get(integer) _vl_cj_integer_get(integer)

// float
#define cj_float_create(value) _vl_cj_float_create(value)
#define cj_float_copy(_float) _vl_cj_float_copy(_float)
#define cj_float_destroy(_float) _vl_cj_float_destroy(_float)

#define cj_float_set(_float, value) _vl_cj_float_set(_float, value)
#define cj_float_get(_float) _vl_cj_float_get(_float)

// bool
#define cj_bool_create(value) _vl_cj_bool_create(value)
#define cj_bool_copy(bool) _vl_cj_bool_copy(bool)
#define cj_bool_destroy(bool) _vl_cj_bool_destroy(bool)

#define cj_bool_set(bool, value) _vl_cj_bool_set(bool)
#define cj_bool_get(bool) _vl_cj_bool_get(bool)

// string
#define cj_string_create(value) _vl_cj_string_create(value)
#define cj_string_copy(string) _vl_cj_string_copy(string)
#define cj_string_destroy(string) _vl_cj_string_destroy(string)

#define cj_string_set(string, value) _vl_cj_string_set(string, value)
#define cj_string_get(string) _vl_cj_string_get(string)

// object
#define cj_object_create() _vl_cj_object_create()
#define cj_object_copy(object) _vl_cj_object_copy(object)
#define cj_object_destroy(object) _vl_cj_object_destroy(object)
#define cj_object_count(object) _vl_cj_object_count(object)
#define cj_object_attach(object, name, var) _vl_cj_object_attach(object, name, var)
#define cj_object_detach(object, name) _vl_cj_object_detach(object, name)
#define cj_object_get(object, name) _vl_cj_object_get(object, name)

// array
#define cj_array_create() _vl_cj_array_create()
#define cj_array_copy(array) _vl_cj_array_copy(array)
#define cj_array_destroy(array) _vl_cj_array_destroy(array)
#define cj_array_count(array) _vl_cj_array_count(array)
#define cj_array_attach(array, index, var) _vl_cj_array_attach(array, index, var)
#define cj_array_detach(array, index) _vl_cj_array_detach(array, index)
#define cj_array_get(array, index) _vl_cj_array_get(array, index)

// util
#define cj_parse(string) _vl_cj_parse(string)
#define cj_stringify(var) _vl_cj_stringify(var)

#include "cj_validation_layer.h"

#endif

#endif