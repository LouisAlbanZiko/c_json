#include "internal.h"

CJ_Array *cj_array_create()
{
	CJ_Array *array = (CJ_Array *)cm_heap_alloc(g_cj_heap_variable, sizeof(*array));
	array->type = CJ_TYPE_ARRAY;
	array->count_c = 0;
	array->count_m = C_JSON_DEFAULT_ARRAY_LENGTH;
	array->elements = malloc(sizeof(*array->elements) * array->count_m);
	
	for(uint32_t i = 0; i < array->count_m; i++)
	{
		array->elements[i].variable = NULL;
	}
	return array;
}

CJ_Array *cj_array_copy(CJ_Array *array)
{
	CJ_Array *copy = cm_heap_alloc(g_cj_heap_variable, sizeof(*copy));
	*copy = *array;
	copy->elements = malloc(sizeof(*copy->elements) * copy->count_m);

	for(uint64_t i = 0; i < copy->count_m; i++)
	{
		if(copy->elements[i].variable != NULL)
		{
			copy->elements[i].variable = cj_variable_copy(array->elements[i].variable);
		}
		else
		{
			copy->elements[i].variable = NULL;
		}
	}

	return copy;
}

void cj_array_destroy(CJ_Array *array)
{
	for(uint64_t i = 0; i < array->count_m; i++)
	{
		if(array->elements[i].variable != NULL)
		{
			cj_variable_destroy(array->elements[i].variable);
		}
	}
	free(array->elements);
	cm_heap_free(g_cj_heap_variable, array);
}

uint64_t cj_array_count(CJ_Array *array)
{
	return array->count_c;
}

void cj_array_size_increase(CJ_Array *array)
{
	array->count_m = array->count_m << 1;
	array->elements = realloc(array->elements, sizeof(*array->elements) * array->count_m);
}

void cj_array_attach(CJ_Array *array, CJ_Variable *variable)
{
	if (array->count_c == array->count_m)
	{
		cj_array_size_increase(array);
	}
	CJ_Array_Element *list = array->elements;
	list[array->count_c++].variable = variable;
}

CJ_Variable *cj_array_detach(CJ_Array *array, uint64_t index)
{
	CJ_Array_Element *list = array->elements;
	CJ_Variable *variable = list[index].variable;
	list[index].variable = NULL;
	return variable;
}

CJ_Variable *cj_array_get(CJ_Array *array, uint64_t index)
{
	CJ_Array_Element *list = array->elements;
	return list[index].variable;
}

CJ_Array_Iterator *cj_array_iterator_start(CJ_Array *array)
{
	return cj_array_iterator_next(array, (CJ_Array_Iterator *)(array->elements - 1));
}

CJ_Array_Iterator *cj_array_iterator_next(CJ_Array *array, CJ_Array_Iterator *iterator)
{
	do
	{
		iterator++;
	} while (iterator->var == NULL && iterator != cj_array_iterator_end(array));
	return iterator;
}
CJ_Array_Iterator *cj_array_iterator_end(CJ_Array *array)
{
	return (CJ_Array_Iterator *)(array->elements + array->count_c);
}