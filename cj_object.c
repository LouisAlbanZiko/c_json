#include "internal.h"

CJ_Object *cj_object_create()
{
	CJ_Object *object = malloc(sizeof(*object));
	object->type = CJ_TYPE_OBJECT;
	object->count_c = 0;
	object->count_m = C_JSON_DEFAULT_OBJECT_LENGTH;
	cj_string_buffer_create(&object->string_buffer);
	// hash_mask generation
	{
		object->hash_mask = 0;
		uint64_t length = object->count_m;
		while (length > 0)
		{
			object->hash_mask <<= 1;
			object->hash_mask |= 1;
			length >>= 1;
		}
	}
	object->elements = malloc(sizeof(*object->elements) * object->count_m);

	for (uint32_t i = 0; i < object->count_m; i++)
	{
		object->elements[i].name = NULL;
		object->elements[i].variable = NULL;
	}
	return object;
}

CJ_Object *cj_object_copy(CJ_Object *object)
{
	CJ_Object *copy = malloc(sizeof(*copy));
	*copy = *object;
	copy->elements = malloc(sizeof(*copy->elements) * copy->count_m);

	cj_string_buffer_create(&copy->string_buffer);

	for (uint64_t i = 0; i < copy->count_m; i++)
	{
		if (copy->elements[i].name != NULL)
		{
			char *name_copy = cj_string_buffer_current(&copy->string_buffer);
			cj_string_buffer_insert_string(&copy->string_buffer, object->elements[i].name);
			copy->elements[i].name = name_copy;
			copy->elements[i].variable = cj_variable_copy(object->elements[i].variable);
		}
		else
		{
			copy->elements[i].name = NULL;
			copy->elements[i].variable = NULL;
		}
	}

	return copy;
}

void cj_object_destroy(CJ_Object *object)
{
	for (uint64_t i = 0; i < object->count_m; i++)
	{
		if (object->elements[i].name != NULL)
		{
			cj_variable_destroy(object->elements[i].variable);
		}
	}
	cj_string_buffer_destroy(&object->string_buffer);
	free(object->elements);
	free(object);
}

void cj_object_size_increase(CJ_Object *object)
{
	object->count_m = object->count_m << 1;
	CJ_Object_Element *old_elements = object->elements;
	object->elements = malloc(sizeof(*object->elements) * object->count_m);
	object->hash_mask = object->hash_mask << 1;
	object->hash_mask |= 1;
	for (uint64_t i = 0; i < object->count_m; i++)
	{
		object->elements[i].name = NULL;
		object->elements[i].variable = NULL;
	}
	for (uint64_t i = 0; i < object->count_m; i++)
	{
		if (old_elements[i].name != NULL)
		{
			uint32_t hash = hashlittle(old_elements[i].name, strlen(old_elements[i].name), 0) & object->hash_mask;
			CJ_Object_Element *list = object->elements;
			while (list[hash].name != NULL)
			{
				hash = (hash + 1) & object->hash_mask;
			}
			list[hash].name = old_elements[i].name;
			list[hash].variable = old_elements[i].variable;
		}
	}
	free(old_elements);
}

void cj_object_attach(CJ_Object *object, const char *name, CJ_Variable *variable)
{
	if (object->count_c == object->count_m)
	{
		cj_object_size_increase(object);
	}
	uint32_t hash = hashlittle(name, strlen(name), 0) & object->hash_mask;
	CJ_Object_Element *list = object->elements;
	while (list[hash].name != NULL)
	{
		if (strcmp(name, list[hash].name) == 0)
		{
			list[hash].variable = variable;
			return;
		}
		hash = (hash + 1) & object->hash_mask;
	}
	char *name_copy = cj_string_buffer_current(&object->string_buffer);
	cj_string_buffer_insert_string(&object->string_buffer, name);
	list[hash].name = name_copy;
	list[hash].variable = variable;
	object->count_c++;
}

CJ_Variable *cj_object_detach(CJ_Object *object, const char *name)
{
	uint32_t hash = hashlittle(name, strlen(name), 0) & object->hash_mask;
	CJ_Object_Element *list = object->elements;
	if (list[hash].name != NULL)
	{
		while (strcmp(name, list[hash].name) != 0)
		{
			hash = (hash + 1) & object->hash_mask;
			if (list[hash].name == NULL)
				return NULL;
		}
		CJ_Variable *variable = list[hash].variable;
		list[hash].name = NULL;
		list[hash].variable = NULL;
		return variable;
	}
	else
	{
		return NULL;
	}
}

CJ_Variable *cj_object_get(CJ_Object *object, const char *name)
{
	uint32_t hash = hashlittle(name, strlen(name), 0) & object->hash_mask;
	CJ_Object_Element *list = object->elements;
	if (list[hash].name != NULL)
	{
		while (strcmp(name, list[hash].name) != 0)
		{
			hash = (hash + 1) & object->hash_mask;
			if (list[hash].name == NULL)
				return NULL;
		}
		return list[hash].variable;
	}
	else
	{
		return NULL;
	}
}
