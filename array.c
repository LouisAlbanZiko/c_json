#include "internal.h"

CJ_Array *cj_array_create()
{
	CJ_Array *array = malloc(sizeof(*array));
	array->type = CJ_TYPE_ARRAY;
	array->count_c = 0;
	array->count_m = C_JSON_DEFAULT_ARRAY_LENGTH;
	// hash_mask generation
	{
		array->hash_mask = 0;
		uint64_t length = array->count_m;
		while(length > 0)
		{
			array->hash_mask <<= 1;
			array->hash_mask |= 1;
			length >>= 1;
		}
	}
	array->elements = malloc(sizeof(*array->elements) * array->count_m);
	
	for(uint32_t i = 0; i < array->count_m; i++)
	{
		array->elements[i].name = 0;
		array->elements[i].variable = NULL;
	}
	return array;
}

void cj_array_destroy(CJ_Array *array)
{
	for(uint64_t i = 0; i < array->count_m; i++)
	{
		if(array->elements[i].name != NULL)
		{
			cj_variable_destroy(array->elements[i].variable);
		}
	}
	free(array->elements);
	free(array);
}

void cj_array_attach(CJ_Array *array, uint64_t index, CJ_Variable *variable)
{
	if (array->count_c == array->count_m)
	{
		array->count_m = array->count_m << 1;
		array->elements = realloc(array->elements, array->count_m);
		array->hash_mask = array->hash_mask << 1;
		array->hash_mask != 1;
	}
	uint32_t hash = hashlittle(&index, 8, 0) & array->hash_mask;
	CJ_Array_Element *list = array->elements;
	while(list[hash].variable != NULL)
	{
		if(list[hash].name == index)
		{
			list[hash].name = index;
			list[hash].variable = variable;
		}
		hash = (hash + 1) & array->hash_mask;
	}
	list[hash].name = index;
	list[hash].variable = variable;
	array->count_c++;
}

CJ_Variable *cj_array_detach(CJ_Array *array, uint64_t index)
{
	uint32_t hash = hashlittle(&index, 8, 0) & array->hash_mask;
	CJ_Array_Element *list = array->elements;
	if(list[hash].variable != NULL)
	{
		while(list[hash].name != index)
		{
			hash = (hash + 1) & array->hash_mask;
			if(list[hash].variable == NULL)
				return NULL;
		}
		CJ_Variable *variable = list[hash].variable;
		list[hash].name = 0;
		list[hash].variable = NULL;
		return variable;
	}
	else
	{
		return NULL;
	}
}

CJ_Variable *cj_array_get(CJ_Array *array, uint64_t index)
{
	uint32_t hash = hashlittle(&index, 8, 0) & array->hash_mask;
	CJ_Array_Element *list = array->elements;
	if(list[hash].variable != NULL)
	{
		while(list[hash].name != index)
		{
			hash = (hash + 1) & array->hash_mask;
			if(list[hash].variable == NULL)
				return NULL;
		}
		return list[hash].variable;
	}
	else
	{
		return NULL;
	}
}
