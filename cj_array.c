#include "internal.h"

CJ_Array *cj_array_create()
{
	_CJ_Array *array = malloc(sizeof(*array));

	array->type = CJ_TYPE_ARRAY;
	array->set = cm_unordered_set_create(sizeof(CJ_Variable *), 8);

	return (CJ_Array *)array;
}

CJ_Array *cj_array_copy(CJ_Array *var)
{
	_CJ_Array *_var = (_CJ_Array *)var;
	_CJ_Array *array = malloc(sizeof(*array));

	array->type = CJ_TYPE_ARRAY;
	array->set = cm_unordered_set_create(sizeof(CJ_Variable *), cm_unordered_set_count(_var->set));

	for (CJ_Variable **e = cm_unordered_set_iterator_begin(_var->set); e != cm_unordered_set_iterator_end(_var->set); e = cm_unordered_set_iterator_next(_var->set, e))
	{
		cm_unordered_set_insert(array->set, e);
	}

	return (CJ_Array *)array;
}

void cj_array_destroy(CJ_Array *var)
{
	_CJ_Array *_var = (_CJ_Array *)var;
	cm_unordered_set_destroy(_var->set);
	free(_var);
}

uint64_t cj_array_count(CJ_Array *array)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return cm_unordered_set_count(_var->set);
}

void cj_array_attach(CJ_Array *array, CJ_Variable *variable)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	cm_unordered_set_insert(_var->set, &variable);
}

CJ_Variable *cj_array_detach(CJ_Array *array, uint64_t index)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	CJ_Variable *var = cj_array_get(array, index);
	cm_unordered_set_remove(_var->set, index);
	return var;
}

void cj_array_set(CJ_Array *array, uint64_t index, CJ_Variable *var)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	cm_unordered_set_set(_var->set, index, &var);
}

CJ_Variable *cj_array_get(CJ_Array *array, uint64_t index)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	CJ_Variable *var = *((CJ_Variable **)cm_unordered_set_get(_var->set, index));
	return var;
}

CJ_Array_Iterator *cj_array_iterator_start(CJ_Array *array)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return cm_unordered_set_iterator_begin(_var->set);
}

CJ_Array_Iterator *cj_array_iterator_next(CJ_Array *array, CJ_Array_Iterator *iterator)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return cm_unordered_set_iterator_next(_var->set, iterator);
}

CJ_Array_Iterator *cj_array_iterator_end(CJ_Array *array)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return cm_unordered_set_iterator_end(_var->set);
}