#ifndef _C_JSON_H_
#define _C_JSON_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "cj_external.h"

// setup
void cj_init();
void cj_terminate();

// util
CJ_Variable *cj_parse(const char *string);
void cj_fprintf(FILE *file, CJ_Variable *var);

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