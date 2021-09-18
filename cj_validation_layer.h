#ifndef _CJ_VALIDATION_LAYER_H_
#define _CJ_VALIDATION_LAYER_H_

#include <stdint.h>

// variable
typedef struct _CJ_Variable CJ_Variable;

CJ_Variable *_vl_cj_variable_copy(CJ_Variable *variable);
uint64_t _vl_cj_variable_type(CJ_Variable *variable);
uint64_t _vl_cj_variable_value(CJ_Variable *variable);
void _vl_cj_variable_destroy(CJ_Variable *variable);

// null
typedef struct _CJ_Null CJ_Null;

CJ_Null *_vl_cj_null_create();
void _vl_cj_null_destroy(CJ_Null *var);

// integer
typedef struct _CJ_Integer CJ_Integer;

CJ_Integer *_vl_cj_integer_create(int64_t value);
CJ_Integer *_vl_cj_integer_copy(CJ_Integer *integer);
void _vl_cj_integer_destroy(CJ_Integer *integer);

void _vl_cj_integer_set(CJ_Integer *integer, int64_t value);
int64_t _vl_cj_integer_get(CJ_Integer *integer);

// float
typedef struct _CJ_Float CJ_Float;

CJ_Float *_vl_cj_float_create(double value);
CJ_Float *_vl_cj_float_copy(CJ_Float *_float);
void _vl_cj_float_destroy(CJ_Float *_float);

void _vl_cj_float_set(CJ_Float *_float, double value);
double _vl_cj_float_get(CJ_Float *_float);

// bool
typedef struct _CJ_Bool CJ_Bool;

CJ_Bool *_vl_cj_bool_create(uint64_t value);
CJ_Bool *_vl_cj_bool_copy(CJ_Bool *bool);
void _vl_cj_bool_destroy(CJ_Bool *bool);

void _vl_cj_bool_set(CJ_Bool *bool, uint64_t value);
uint64_t _vl_cj_bool_get(CJ_Bool *bool);

// string
typedef struct _CJ_String CJ_String;

CJ_String *_vl_cj_string_create(const char *value);
CJ_String *_vl_cj_string_copy(CJ_String *string);
void _vl_cj_string_destroy(CJ_String *string);

void _vl_cj_string_set(CJ_String *string, const char *value);
const char *_vl_cj_string_get(CJ_String *string);

// object
typedef struct _CJ_Object CJ_Object;

CJ_Object *_vl_cj_object_create();
CJ_Object *_vl_cj_object_copy(CJ_Object *object);
void _vl_cj_object_destroy(CJ_Object *object);
uint64_t _vl_cj_object_count(CJ_Object *object);
void _vl_cj_object_attach(CJ_Object *object, const char *name, CJ_Variable *variable);
CJ_Variable *_vl_cj_object_detach(CJ_Object *object, const char *name);
CJ_Variable *_vl_cj_object_get(CJ_Object *object, const char *name);

// array
typedef struct _CJ_Array CJ_Array;

CJ_Array *_vl_cj_array_create();
CJ_Array *_vl_cj_array_copy(CJ_Array *array);
void _vl_cj_array_destroy(CJ_Array *array);
uint64_t _vl_cj_array_count(CJ_Array *array);
void _vl_cj_array_attach(CJ_Array *array, uint64_t index, CJ_Variable *variable);
CJ_Variable *_vl_cj_array_detach(CJ_Array *array, uint64_t index);
CJ_Variable *_vl_cj_array_get(CJ_Array *array, uint64_t index);

// util
CJ_Variable *_vl_cj_parse(const char *string);
const char *_vl_cj_stringify(CJ_Variable *variable);

#endif