#include "internal.h"

void CJ_Fprintf_Variable(FILE *file, const CJ_Variable *var, uint64_t depth);

void CJ_fprintf(FILE *file, const CJ_Variable *var)
{
	CJ_Fprintf_Variable(file, var, (uint64_t)0);
	fprintf(file, "\n");
}

void CJ_Fprintf_Variable(FILE *file, const CJ_Variable *var, uint64_t depth)
{
	//for(uint64_t i = 0; i < depth; i++)
	//	fprintf(file, "\t");
	switch (var->type)
	{
	case CJ_TYPE_NULL:
	{
		fprintf(file, "null");
		break;
	}
	case CJ_TYPE_INTEGER:
	{
		fprintf(file, "%lld", CJ_Integer_Get((CJ_Integer *)var));
		break;
	}
	case CJ_TYPE_FLOAT:
	{
		fprintf(file, "%lf", CJ_Float_Get((CJ_Float *)var));
		break;
	}
	case CJ_TYPE_BOOL:
	{
		static const char *const _true = "true";
		static const char *const _false = "false";
		uint64_t val = CJ_Bool_Get((CJ_Bool *)var);
		const char *val_s = (const char *)((uint64_t)_true * val + (uint64_t)_false * !val);
		fprintf(file, "%s", val_s);
		break;
	}
	case CJ_TYPE_STRING:
	{
		const char *val = CJ_String_Get((CJ_String *)var);
		fprintf(file, "\"%s\"", val);
		break;
	}
	case CJ_TYPE_OBJECT:
	{
		CJ_Object *object = (CJ_Object *)var;
		fprintf(file, "\n");
		for (uint64_t i = 0; i < depth; i++)
			fprintf(file, "\t");
		fprintf(file, "{\n");
		for (CJ_Object_Iterator *iter = CJ_Object_IteratorBegin(object); iter != CJ_Object_IteratorEnd(object); iter = CJ_Object_IteratorNext(object, iter))
		{
			for (uint64_t i = 0; i <= depth; i++)
				fprintf(file, "\t");
			fprintf(file, "\"%s\" : ", iter->name);
			CJ_Fprintf_Variable(file, iter->var, depth + 1);
			if (CJ_Object_IteratorNext(object, iter) != CJ_Object_IteratorEnd(object))
			{
				fprintf(file, ",\n");
			}
		}
		fprintf(file, "\n");
		for (uint64_t i = 0; i < depth; i++)
			fprintf(file, "\t");
		fprintf(file, "}");
		break;
	}
	case CJ_TYPE_ARRAY:
	{
		CJ_Array *array = (CJ_Array *)var;
		fprintf(file, "\n");
		for (uint64_t i = 0; i < depth; i++)
			fprintf(file, "\t");
		fprintf(file, "[\n");
		for (CJ_Array_Iterator *iter = CJ_Array_IteratorStart(array); iter != CJ_Array_IteratorEnd(array); iter = CJ_Array_IteratorNext(array, iter))
		{
			for (uint64_t i = 0; i <= depth; i++)
				fprintf(file, "\t");
			CJ_Fprintf_Variable(file, iter->var, depth + 1);
			if (CJ_Array_IteratorNext(array, iter) != CJ_Array_IteratorEnd(array))
			{
				fprintf(file, ",\n");
			}
		}
		fprintf(file, "\n");
		for (uint64_t i = 0; i < depth; i++)
			fprintf(file, "\t");
		fprintf(file, "]");
		break;
	}
	}
}
