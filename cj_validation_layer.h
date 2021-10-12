#ifndef _CJ_VALIDATION_LAYER_H_
#define _CJ_VALIDATION_LAYER_H_

#include <stdint.h>

#include "cj_external.h"

// variable
CJ_Variable *_vl_cj_variable_copy(CJ_Variable *variable, const char *file, uint64_t line);
uint64_t _vl_cj_variable_type(CJ_Variable *variable, const char *file, uint64_t line);
uint64_t _vl_cj_variable_value(CJ_Variable *variable, const char *file, uint64_t line);
void _vl_cj_variable_destroy(CJ_Variable *variable, const char *file, uint64_t line);

// null
CJ_Null *_vl_cj_null_create(const char *file, uint64_t line);
void _vl_cj_null_destroy(CJ_Null *var, const char *file, uint64_t line);

// integer
CJ_Integer *_vl_cj_integer_create(int64_t value, const char *file, uint64_t line);
CJ_Integer *_vl_cj_integer_copy(CJ_Integer *integer, const char *file, uint64_t line);
void _vl_cj_integer_destroy(CJ_Integer *integer, const char *file, uint64_t line);

void _vl_cj_integer_set(CJ_Integer *integer, int64_t value, const char *file, uint64_t line);
int64_t _vl_cj_integer_get(CJ_Integer *integer, const char *file, uint64_t line);

// float
CJ_Float *_vl_cj_float_create(double value, const char *file, uint64_t line);
CJ_Float *_vl_cj_float_copy(CJ_Float *_float, const char *file, uint64_t line);
void _vl_cj_float_destroy(CJ_Float *_float, const char *file, uint64_t line);

void _vl_cj_float_set(CJ_Float *_float, double value, const char *file, uint64_t line);
double _vl_cj_float_get(CJ_Float *_float, const char *file, uint64_t line);

// bool
CJ_Bool *_vl_cj_bool_create(uint64_t value, const char *file, uint64_t line);
CJ_Bool *_vl_cj_bool_copy(CJ_Bool *bool, const char *file, uint64_t line);
void _vl_cj_bool_destroy(CJ_Bool *bool, const char *file, uint64_t line);

void _vl_cj_bool_set(CJ_Bool *bool, uint64_t value, const char *file, uint64_t line);
uint64_t _vl_cj_bool_get(CJ_Bool *bool, const char *file, uint64_t line);

// string
CJ_String *_vl_cj_string_create(const char *value, const char *file, uint64_t line);
CJ_String *_vl_cj_string_copy(CJ_String *string, const char *file, uint64_t line);
void _vl_cj_string_destroy(CJ_String *string, const char *file, uint64_t line);

void _vl_cj_string_set(CJ_String *string, const char *value, const char *file, uint64_t line);
const char *_vl_cj_string_get(CJ_String *string, const char *file, uint64_t line);

// object
CJ_Object *_vl_cj_object_create(const char *file, uint64_t line);
CJ_Object *_vl_cj_object_copy(CJ_Object *object, const char *file, uint64_t line);
void _vl_cj_object_destroy(CJ_Object *object, const char *file, uint64_t line);
uint64_t _vl_cj_object_count(CJ_Object *object, const char *file, uint64_t line);
void _vl_cj_object_attach(CJ_Object *object, const char *name, CJ_Variable *variable, const char *file, uint64_t line);
CJ_Variable *_vl_cj_object_detach(CJ_Object *object, const char *name, const char *file, uint64_t line);
CJ_Variable *_vl_cj_object_get(CJ_Object *object, const char *name, const char *file, uint64_t line);

// array
CJ_Array *_vl_cj_array_create(const char *file, uint64_t line);
CJ_Array *_vl_cj_array_copy(CJ_Array *array, const char *file, uint64_t line);
void _vl_cj_array_destroy(CJ_Array *array, const char *file, uint64_t line);
uint64_t _vl_cj_array_count(CJ_Array *array, const char *file, uint64_t line);
void _vl_cj_array_attach(CJ_Array *array, CJ_Variable *variable, const char *file, uint64_t line);
CJ_Variable *_vl_cj_array_detach(CJ_Array *array, uint64_t index, const char *file, uint64_t line);
CJ_Variable *_vl_cj_array_get(CJ_Array *array, uint64_t index, const char *file, uint64_t line);

// util
CJ_Variable *_vl_cj_parse(const char *string, const char *file, uint64_t line);
void _vl_cj_fprintf(FILE *f, CJ_Variable *var, const char *file, uint64_t line);
const char *_vl_cj_stringify(CJ_Variable *variable, const char *file, uint64_t line);

void _vl_cj_init(const char *file, uint64_t line);
void _vl_cj_terminate(const char *file, uint64_t line);

void _vl_cj_error_callback_set(cj_error_callback callback, const char *file, uint64_t line);
void _vl_cj_error_callback_print_set(uint32_t should_print, const char *file, uint64_t line);

#endif