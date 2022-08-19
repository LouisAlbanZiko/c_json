#include "internal.h"

CJ_Variable *CJ_Variable_Copy(CJ_Variable *variable)
{
	switch (variable->type)
	{
	case CJ_TYPE_NULL:
		return (CJ_Variable *)CJ_Null_Create();
	case CJ_TYPE_INTEGER:
		return (CJ_Variable *)CJ_Integer_Copy((CJ_Integer *)variable);
	case CJ_TYPE_FLOAT:
		return (CJ_Variable *)CJ_Float_Copy((CJ_Float *)variable);
	case CJ_TYPE_BOOL:
		return (CJ_Variable *)CJ_Bool_Copy((CJ_Bool *)variable);
	case CJ_TYPE_STRING:
		return (CJ_Variable *)CJ_String_Copy((CJ_String *)variable);
	case CJ_TYPE_OBJECT:
		return (CJ_Variable *)CJ_Object_Copy((CJ_Object *)variable);
	case CJ_TYPE_ARRAY:
		return (CJ_Variable *)CJ_Array_Copy((CJ_Array *)variable);
	default:
		return NULL;
	}
}

uint64_t CJ_Variable_Type(CJ_Variable *variable)
{
	return variable->type;
}

void CJ_Variable_Destroy(CJ_Variable *variable)
{
	switch (variable->type)
	{
	case CJ_TYPE_NULL:
		CJ_Null_Destroy((CJ_Null *)variable);
		return;
	case CJ_TYPE_INTEGER:
		CJ_Integer_Destroy((CJ_Integer *)variable);
		return;
	case CJ_TYPE_FLOAT:
		CJ_Float_Destroy((CJ_Float *)variable);
		return;
	case CJ_TYPE_BOOL:
		CJ_Bool_Destroy((CJ_Bool *)variable);
		return;
	case CJ_TYPE_STRING:
		CJ_String_Destroy((CJ_String *)variable);
		return;
	case CJ_TYPE_OBJECT:
		CJ_Object_Destroy((CJ_Object *)variable);
		return;
	case CJ_TYPE_ARRAY:
		CJ_Array_Destroy((CJ_Array *)variable);
		return;
	}
}