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

// variable
typedef struct _CJ_Variable CJ_Variable;

CJ_Variable *cj_variable_copy(CJ_Variable *variable);
void cj_variable_set(CJ_Variable *variable, uint64_t type, uint64_t value);
uint64_t cj_variable_type(CJ_Variable *variable);
uint64_t cj_variable_value(CJ_Variable *variable);
void cj_variable_destroy(CJ_Variable *variable);

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
void cj_object_destroy(CJ_Object *object);
void cj_object_attach(CJ_Object *object, const char *name, CJ_Variable *variable);
CJ_Variable *cj_object_detach(CJ_Object *object, const char *name);
CJ_Variable *cj_object_get(CJ_Object *object, const char *name);

// array
typedef struct _CJ_Array CJ_Array;

CJ_Array *cj_array_create();
void cj_array_destroy(CJ_Array *array);
void cj_array_attach(CJ_Array *array, uint64_t index, CJ_Variable *variable);
CJ_Variable *cj_array_detach(CJ_Array *array, uint64_t index);
CJ_Variable *cj_array_get(CJ_Array *array, uint64_t index);

#endif