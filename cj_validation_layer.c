#include "internal.h"
#include "cj_validation_layer.h"

CJ_Variable *_vl_cj_variable_copy(CJ_Variable *variable, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_variable_copy", file, line);
	}
	else
	{
		return cj_variable_copy(variable);
	}
	return NULL;
}

uint64_t _vl_cj_variable_type(CJ_Variable *variable, const char *file, uint64_t line)
{
	if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_variable_type", file, line);
	}
	else
	{
		return cj_variable_type(variable);
	}
	return CJ_TYPE_NULL;
}

uint64_t _vl_cj_variable_value(CJ_Variable *variable, const char *file, uint64_t line)
{
	if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_variable_value", file, line);
	}
	else
	{
		return cj_variable_type(variable);
	}
	return 0;
}

void _vl_cj_variable_destroy(CJ_Variable *variable, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_variable_destroy", file, line);
	}
	else
	{
		cj_variable_type(variable);
	}
}

// null
CJ_Null *_vl_cj_null_create(const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else
	{
		return cj_null_create();
	}
	return NULL;
}

void _vl_cj_null_destroy(CJ_Null *var, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(var == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_null_destroy", file, line);
	}
	else
	{
		cj_null_destroy(var);
	}
}

// integer
CJ_Integer *_vl_cj_integer_create(int64_t value, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else
	{
		return cj_integer_create(value);
	}
	return NULL;
}

CJ_Integer *_vl_cj_integer_copy(CJ_Integer *integer, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(integer == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_integer_copy", file, line);
	}
	else
	{
		return cj_integer_copy(integer);
	}
	return NULL;
}

void _vl_cj_integer_destroy(CJ_Integer *integer, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(integer == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_integer_destroy", file, line);
	}
	else
	{
		cj_integer_destroy(integer);
	}
}

void _vl_cj_integer_set(CJ_Integer *integer, int64_t value, const char *file, uint64_t line)
{
	if(integer == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_integer_set", file, line);
	}
	else
	{
		cj_integer_set(integer, value);
	}
}

int64_t _vl_cj_integer_get(CJ_Integer *integer, const char *file, uint64_t line)
{
	if(integer == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_integer_get", file, line);
	}
	else
	{
		return cj_integer_get(integer);
	}
	return 0;
}

// float
CJ_Float *_vl_cj_float_create(double value, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else
	{
		return cj_float_create(value);
	}
	return NULL;
}

CJ_Float *_vl_cj_float_copy(CJ_Float *_float, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(_float == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_float_copy", file, line);
	}
	else
	{
		return cj_float_copy(_float);
	}
	return NULL;
}

void _vl_cj_float_destroy(CJ_Float *_float, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(_float == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_float_destroy", file, line);
	}
	else
	{
		cj_float_destroy(_float);
	}
}

void _vl_cj_float_set(CJ_Float *_float, double value, const char *file, uint64_t line)
{
	if(_float == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_float_set", file, line);
	}
	else
	{
		cj_float_set(_float, value);
	}
}

double _vl_cj_float_get(CJ_Float *_float, const char *file, uint64_t line)
{
	if(_float == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_float_get", file, line);
	}
	else
	{
		return cj_float_get(_float);
	}
	return 0.0;
}

// bool
CJ_Bool *_vl_cj_bool_create(uint64_t value, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else
	{
		return cj_bool_create(value);
	}
	return NULL;
}

CJ_Bool *_vl_cj_bool_copy(CJ_Bool *bool, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(bool == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_bool_copy", file, line);
	}
	else
	{
		return cj_bool_copy(bool);
	}
	return NULL;
}

void _vl_cj_bool_destroy(CJ_Bool *bool, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(bool == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_bool_destroy", file, line);
	}
	else
	{
		cj_bool_destroy(bool);
	}
}

void _vl_cj_bool_set(CJ_Bool *bool, uint64_t value, const char *file, uint64_t line)
{
	if(bool == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_bool_set", file, line);
	}
	else
	{
		cj_bool_set(bool, value);
	}
}

uint64_t _vl_cj_bool_get(CJ_Bool *bool, const char *file, uint64_t line)
{
	if(bool == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_bool_get", file, line);
	}
	else
	{
		return cj_bool_get(bool);
	}
	return 0;
}

// string
CJ_String *_vl_cj_string_create(const char *value, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL || g_cj_heap_string == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(value == NULL)
	{
		_cj_make_error(CJ_ERROR_STRING_NULL, "Passed string value is NULL on function '%s'. %s, %lu", "cj_string_create", file, line);
	}
	else
	{
		return cj_string_create(value);
	}
	return NULL;
}

CJ_String *_vl_cj_string_copy(CJ_String *string, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL || g_cj_heap_string == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(string == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_string_copy", file, line);
	}
	else
	{
		return cj_string_copy(string);
	}
	return NULL;
}

void _vl_cj_string_destroy(CJ_String *string, const char *file, uint64_t line)
{
	if(g_cj_heap_variable == NULL || g_cj_heap_string == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if(string == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_string_destroy", file, line);
	}
	else
	{
		cj_string_destroy(string);
	}
}

void _vl_cj_string_set(CJ_String *string, const char *value, const char *file, uint64_t line)
{
	if(string == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_string_set", file, line);
	}
	else if(value == NULL)
	{
		_cj_make_error(CJ_ERROR_STRING_NULL, "Passed string value is NULL on function '%s'. %s, %lu", "cj_string_set", file, line);
	}
	else
	{
		cj_string_set(string, value);
	}
}

const char *_vl_cj_string_get(CJ_String *string, const char *file, uint64_t line)
{
	if(string == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_string_get", file, line);
	}
	else
	{
		return cj_string_get(string);
	}
	return NULL;
}

// object
CJ_Object *_vl_cj_object_create(const char *file, uint64_t line)
{
	if (g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else
	{
		return cj_object_create();
	}
	return NULL;
}

CJ_Object *_vl_cj_object_copy(CJ_Object *object, const char *file, uint64_t line)
{
	if (g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if (object == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_object_copy", file, line);
	}
	else
	{
		return cj_object_copy(object);
	}
	return NULL;
}

void _vl_cj_object_destroy(CJ_Object *object, const char *file, uint64_t line)
{
	if (g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if (object == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_object_destroy", file, line);
	}
	else
	{
		cj_object_destroy(object);
	}
}

uint64_t _vl_cj_object_count(CJ_Object *object, const char *file, uint64_t line)
{
	if (object == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_object_count", file, line);
	}
	else
	{
		return cj_object_count(object);
	}
	return 0;
}

void _vl_cj_object_attach(CJ_Object *object, const char *name, CJ_Variable *variable, const char *file, uint64_t line)
{
	if (object == NULL || variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_object_attach", file, line);
	}
	else if (name == NULL)
	{
		_cj_make_error(CJ_ERROR_STRING_NULL, "Passed string value for 'name' is NULL on function '%s'. %s, %lu", "cj_object_attach", file, line);
	}
	else
	{
		cj_object_attach(object, name, variable);
	}
}

CJ_Variable *_vl_cj_object_detach(CJ_Object *object, const char *name, const char *file, uint64_t line)
{
	if (object == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_object_detach", file, line);
	}
	else if (name == NULL)
	{
		_cj_make_error(CJ_ERROR_STRING_NULL, "Passed string value for 'name' is NULL on function '%s'. %s, %lu", "cj_object_detach", file, line);
	}
	else
	{
		return cj_object_detach(object, name);
	}
	return NULL;
}

CJ_Variable *_vl_cj_object_get(CJ_Object *object, const char *name, const char *file, uint64_t line)
{
	if (object == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_object_get", file, line);
	}
	else if (name == NULL)
	{
		_cj_make_error(CJ_ERROR_STRING_NULL, "Passed string value for 'name' is NULL on function '%s'. %s, %lu", "cj_object_get", file, line);
	}
	else
	{
		return cj_object_get(object, name);
	}
	return NULL;
}

// array
CJ_Array *_vl_cj_array_create(const char *file, uint64_t line)
{
	if (g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else
	{
		return cj_array_create();
	}
	return NULL;
}

CJ_Array *_vl_cj_array_copy(CJ_Array *array, const char *file, uint64_t line)
{
	if (g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if (array == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_array_copy", file, line);
	}
	else
	{
		return cj_array_copy(array);
	}
	return NULL;
}

void _vl_cj_array_destroy(CJ_Array *array, const char *file, uint64_t line)
{
	if (g_cj_heap_variable == NULL)
	{
		_cj_make_error(CJ_ERROR_NOT_INITIALIZED, "C_JSON hasn't been initialized. A call to cj_init() is required before any other function of this library. %s, %lu", file, line);
	}
	else if (array == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_array_destroy", file, line);
	}
	else
	{
		cj_array_destroy(array);
	}
}

uint64_t _vl_cj_array_count(CJ_Array *array, const char *file, uint64_t line)
{
	if (array == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_array_count", file, line);
	}
	else
	{
		return cj_array_count(array);
	}
	return 0;
}

void _vl_cj_array_attach(CJ_Array *array, CJ_Variable *variable, const char *file, uint64_t line)
{
	if (array == NULL || variable == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_array_attach", file, line);
	}
	else
	{
		cj_array_attach(array, variable);
	}
}

CJ_Variable *_vl_cj_array_detach(CJ_Array *array, uint64_t index, const char *file, uint64_t line)
{
	if (array == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_array_detach", file, line);
	}
	else
	{
		return cj_array_detach(array, index);
	}
	return NULL;
}

CJ_Variable *_vl_cj_array_get(CJ_Array *array, uint64_t index, const char *file, uint64_t line)
{
	if (array == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable is NULL on function '%s'. %s, %lu", "cj_array_get", file, line);
	}
	else
	{
		return cj_array_detach(array, index);
	}
	return NULL;
}

// util
CJ_Variable *_vl_cj_parse(const char *string, const char *file, uint64_t line)
{
	if (string == NULL)
	{
		_cj_make_error(CJ_ERROR_STRING_NULL, "Passed string value for 'string' is NULL on function '%s'. %s, %lu", "cj_parse", file, line);
	}
	else
	{
		return cj_parse(string);
	}
	return NULL;
}

void _vl_cj_fprintf(FILE *f, CJ_Variable *var, const char *file, uint64_t line)
{
	if (f == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed string value for 'FILE *f' is NULL on function '%s'. %s, %lu", "cj_fprintf", file, line);
	}
	else if (var == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed variable 'var' is NULL on function '%s'. %s, %lu", "cj_fprintf", file, line);
	}
	else
	{
		cj_fprintf(f, var);
	}
}

const char *_vl_cj_stringify(CJ_Variable *variable, const char *file, uint64_t line)
{
	//_cj_make_error()
	return NULL;
}

void _vl_cj_init(const char *file, uint64_t line)
{
	cj_init();
}

void _vl_cj_terminate(const char *file, uint64_t line)
{
	cj_terminate();
}

void _vl_cj_error_callback_set(cj_error_callback callback, const char *file, uint64_t line)
{
	if (callback == NULL)
	{
		_cj_make_error(CJ_ERROR_VARIABLE_NULL, "Passed callback is NULL on function '%s'. %s, %lu", "cj_error_callback_set", file, line);
	}
	else
	{
		cj_error_callback_set(callback);
	}
}

void _vl_cj_error_callback_print_set(uint32_t should_print, const char *file, uint64_t line)
{
	cj_error_callback_print_set(should_print);
}