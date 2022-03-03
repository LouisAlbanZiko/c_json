#include "internal.h"

void cj_fprintf_variable(FILE *file, const CJ_Variable *var, uint64_t depth);

void cj_fprintf(FILE *file, const CJ_Variable *var)
{
	cj_fprintf_variable(file, var, (uint64_t)0);
	fprintf(file, "\n");
}

void cj_fprintf_variable(FILE *file, const CJ_Variable *var, uint64_t depth)
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
		fprintf(file, "%I64d", cj_integer_get((CJ_Integer *)var));
		break;
	}
	case CJ_TYPE_FLOAT:
	{
		fprintf(file, "%lf", cj_float_get((CJ_Float *)var));
		break;
	}
	case CJ_TYPE_BOOL:
	{
		static const char *const _true = "true";
		static const char *const _false = "false";
		uint64_t val = cj_bool_get((CJ_Bool *)var);
		const char *val_s = (const char *)((uint64_t)_true * val + (uint64_t)_false * !val);
		fprintf(file, "%s", val_s);
		break;
	}
	case CJ_TYPE_STRING:
	{
		const char *val = cj_string_get((CJ_String *)var).data;
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
		for (CJ_Object_Iterator *iter = cj_object_iterator_begin(object); iter != cj_object_iterator_end(object); iter = cj_object_iterator_next(object, iter))
		{
			for (uint64_t i = 0; i <= depth; i++)
				fprintf(file, "\t");
			fprintf(file, "\"%s\" : ", iter->name);
			cj_fprintf_variable(file, iter->var, depth + 1);
			if (cj_object_iterator_next(object, iter) != cj_object_iterator_end(object))
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
		for (CJ_Array_Iterator *iter = cj_array_iterator_start(array); iter != cj_array_iterator_end(array); iter = cj_array_iterator_next(array, iter))
		{
			for (uint64_t i = 0; i <= depth; i++)
				fprintf(file, "\t");
			cj_fprintf_variable(file, iter->var, depth + 1);
			if (cj_array_iterator_next(array, iter) != cj_array_iterator_end(array))
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
