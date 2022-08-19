#include "internal.h"

CJ_Array *CJ_Array_Create()
{
	_CJ_Array *array = CC_Malloc(sizeof(*array));

	array->type = CJ_TYPE_ARRAY;
	array->set = CC_UnorderedSet_Create(sizeof(CJ_Variable *), 8);

	return (CJ_Array *)array;
}

CJ_Array *CJ_Array_Copy(CJ_Array *var)
{
	_CJ_Array *_var = (_CJ_Array *)var;
	_CJ_Array *array = CC_Malloc(sizeof(*array));

	array->type = CJ_TYPE_ARRAY;
	array->set = CC_UnorderedSet_Create(sizeof(CJ_Variable *), CC_UnorderedSet_Count(_var->set));

	for (CJ_Variable **e = CC_UnorderedSet_IteratorBegin(_var->set); e != CC_UnorderedSet_IteratorEnd(_var->set); e = CC_UnorderedSet_IteratorNext(_var->set, e))
	{
		CC_UnorderedSet_Insert(array->set, e);
	}

	return (CJ_Array *)array;
}

void CJ_Array_Destroy(CJ_Array *var)
{
	_CJ_Array *_var = (_CJ_Array *)var;
	CC_UnorderedSet_Destroy(_var->set);
	CC_Free(_var);
}

uint64_t CJ_Array_Count(CJ_Array *array)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return CC_UnorderedSet_Count(_var->set);
}

void CJ_Array_Attach(CJ_Array *array, CJ_Variable *variable)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	CC_UnorderedSet_Insert(_var->set, &variable);
}

CJ_Variable *CJ_Array_Detach(CJ_Array *array, uint64_t index)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	CJ_Variable *var = CJ_Array_Get(array, index);
	CC_UnorderedSet_Remove(_var->set, index);
	return var;
}

void CJ_Array_Set(CJ_Array *array, uint64_t index, CJ_Variable *var)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	CC_UnorderedSet_Set(_var->set, index, &var);
}

CJ_Variable *CJ_Array_Get(CJ_Array *array, uint64_t index)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	CJ_Variable *var = *((CJ_Variable **)CC_UnorderedSet_Get(_var->set, index));
	return var;
}

CJ_Array_Iterator *CJ_Array_IteratorStart(CJ_Array *array)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return CC_UnorderedSet_IteratorBegin(_var->set);
}

CJ_Array_Iterator *CJ_Array_IteratorNext(CJ_Array *array, CJ_Array_Iterator *iterator)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return CC_UnorderedSet_IteratorNext(_var->set, iterator);
}

CJ_Array_Iterator *CJ_Array_IteratorEnd(CJ_Array *array)
{
	_CJ_Array *_var = (_CJ_Array *)array;
	return CC_UnorderedSet_IteratorEnd(_var->set);
}