#include "internal.h"

CJ_Object *CJ_Object_Create()
{
	_CJ_Object *object = CC_Malloc(sizeof(*object));
	
	object->type = CJ_TYPE_OBJECT;
	object->map = CC_HashMapString_Create(sizeof(CJ_Variable *), 8);

	return (CJ_Object *)object;
}

CJ_Object *CJ_Object_Copy(CJ_Object *var)
{
	_CJ_Object *_var = (_CJ_Object *)var;
	_CJ_Object *object = CC_Malloc(sizeof(*object));

	object->type = CJ_TYPE_OBJECT;
	object->map = CC_HashMapString_Create(sizeof(CJ_Variable *), CC_HashMapString_Count(_var->map));

	for (CC_HashMapString_Element *e = CC_HashMapString_IteratorBegin(_var->map); e != CC_HashMapString_IteratorEnd(_var->map); e = CC_HashMapString_IteratorNext(_var->map, e))
	{
		CC_HashMapString_Insert(object->map, e->name, (void *)e->data);
	}

	return (CJ_Object *)object;
}

void CJ_Object_Destroy(CJ_Object *var)
{
	_CJ_Object *_var = (_CJ_Object *)var;
	CC_HashMapString_Destroy(_var->map);
	CC_Free(_var);
}

uint64_t CJ_Object_Count(CJ_Object *var)
{
	_CJ_Object *_var = (_CJ_Object *)var;
	return CC_HashMapString_Count(_var->map);
}

void CJ_Object_Attach(CJ_Object *object, const char * name, CJ_Variable *var)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	CC_HashMapString_Insert(_var->map, name, &var);
}

CJ_Variable *CJ_Object_Detach(CJ_Object *object, const char * name)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return *((CJ_Variable **) CC_HashMapString_Remove(_var->map, name));
}

CJ_Variable *CJ_Object_Get(CJ_Object *object, const char *name)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	CJ_Variable **lookup = CC_HashMapString_Lookup(_var->map, name);
	if (lookup != NULL)
	{
		return *lookup;
	}
	else
	{
		return NULL;
	}
}

CJ_Object_Iterator *CJ_Object_IteratorBegin(CJ_Object *object)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return (CJ_Object_Iterator *)CC_HashMapString_IteratorBegin(_var->map);
}

CJ_Object_Iterator *CJ_Object_IteratorNext(CJ_Object *object, CJ_Object_Iterator *iterator)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return (CJ_Object_Iterator *)CC_HashMapString_IteratorNext(_var->map, (CC_HashMapString_Element *)iterator);
}

CJ_Object_Iterator *CJ_Object_IteratorEnd(CJ_Object *object)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return (CJ_Object_Iterator *)CC_HashMapString_IteratorEnd(_var->map);
}
