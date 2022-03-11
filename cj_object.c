#include "internal.h"

CJ_Object *cj_object_create()
{
	_CJ_Object *object = malloc(sizeof(*object));
	
	object->type = CJ_TYPE_OBJECT;
	object->map = cc_hash_map_create(sizeof(CJ_Variable *), 8);

	return (CJ_Object *)object;
}

CJ_Object *cj_object_copy(CJ_Object *var)
{
	_CJ_Object *_var = (_CJ_Object *)var;
	_CJ_Object *object = malloc(sizeof(*object));

	object->type = CJ_TYPE_OBJECT;
	object->map = cc_hash_map_create(sizeof(CJ_Variable *), cc_hash_map_count(_var->map));

	for (CC_HashMap_Element *e = cc_hash_map_iterator_begin(_var->map); e != cc_hash_map_iterator_end(_var->map); e = cc_hash_map_iterator_next(_var->map, e))
	{
		cc_hash_map_insert(object->map, e->name, (void *)e->data);
	}

	return (CJ_Object *)object;
}

void cj_object_destroy(CJ_Object *var)
{
	_CJ_Object *_var = (_CJ_Object *)var;
	cc_hash_map_destroy(_var->map);
	free(_var);
}

uint64_t cj_object_count(CJ_Object *var)
{
	_CJ_Object *_var = (_CJ_Object *)var;
	return cc_hash_map_count(_var->map);
}

void cj_object_attach(CJ_Object *object, CC_String name, CJ_Variable *var)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	cc_hash_map_insert(_var->map, name, &var);
}

CJ_Variable *cj_object_detach(CJ_Object *object, CC_String name)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return *((CJ_Variable **)cc_hash_map_remove(_var->map, name));
}

CJ_Variable *cj_object_get(CJ_Object *object, CC_String name)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	CJ_Variable **lookup = cc_hash_map_lookup(_var->map, name);
	if (lookup != NULL)
	{
		return *lookup;
	}
	else
	{
		return NULL;
	}
}

CJ_Object_Iterator *cj_object_iterator_begin(CJ_Object *object)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return (CJ_Object_Iterator *)cc_hash_map_iterator_begin(_var->map);
}

CJ_Object_Iterator *cj_object_iterator_next(CJ_Object *object, CJ_Object_Iterator *iterator)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return (CJ_Object_Iterator *)cc_hash_map_iterator_next(_var->map, (CC_HashMap_Element *)iterator);
}

CJ_Object_Iterator *cj_object_iterator_end(CJ_Object *object)
{
	_CJ_Object *_var = (_CJ_Object *)object;
	return (CJ_Object_Iterator *)cc_hash_map_iterator_end(_var->map);
}