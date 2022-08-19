#ifndef _C_JSON_H_
#define _C_JSON_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <c_core/c_core.h>

typedef enum CJ_VariableType
{
	CJ_TYPE_NULL = 0,
	CJ_TYPE_INTEGER,
	CJ_TYPE_FLOAT,
	CJ_TYPE_BOOL,
	CJ_TYPE_STRING,
	CJ_TYPE_OBJECT,
	CJ_TYPE_ARRAY,
	_CJ_TYPE_COUNT
} CJ_VariableType;

typedef struct CJ_Variable
{
	const uint64_t type;
	const uint64_t value;
} CJ_Variable;

CJ_Variable *CJ_Variable_Copy(CJ_Variable *var);
void CJ_Variable_Destroy(CJ_Variable *variable);

uint64_t CJ_Variable_Type(CJ_Variable *variable);

// null
typedef struct CJ_Null
{
	const uint64_t type;
	const uint64_t value;
} CJ_Null;

CJ_Null *CJ_Null_Create();
void CJ_Null_Destroy(CJ_Null *var);

// integer
typedef struct CJ_Integer
{
	const uint64_t type;
	int64_t value;
} CJ_Integer;

CJ_Integer *CJ_Integer_Create(int64_t value);
CJ_Integer *CJ_Integer_Copy(CJ_Integer *var);
void CJ_Integer_Destroy(CJ_Integer *var);

void CJ_Integer_Set(CJ_Integer *var, int64_t value);
int64_t CJ_Integer_Get(CJ_Integer *var);

// float
typedef struct CJ_Float
{
	const uint64_t type;
	double value;
} CJ_Float;

CJ_Float *CJ_Float_Create(double value);
CJ_Float *CJ_Float_Copy(CJ_Float *var);
void CJ_Float_Destroy(CJ_Float *var);

void CJ_Float_Set(CJ_Float *var, double value);
double CJ_Float_Get(CJ_Float *var);

// boolean
typedef struct CJ_Bool
{
	const uint64_t type;
	uint64_t value;
} CJ_Bool;

#define CJ_FALSE 0
#define CJ_TRUE 1

CJ_Bool *CJ_Bool_Create(uint64_t value);
CJ_Bool *CJ_Bool_Copy(CJ_Bool *var);
void CJ_Bool_Destroy(CJ_Bool *var);

void CJ_Bool_Set(CJ_Bool *var, uint64_t value);
uint64_t CJ_Bool_Get(CJ_Bool *var);

// string
typedef struct CJ_String
{
	const uint64_t type;
	const char *const value;
	const uint64_t length;
} CJ_String;

CJ_String *CJ_String_Create(const char * value);
CJ_String *CJ_String_Copy(CJ_String *var);
void CJ_String_Destroy(CJ_String *var);

void CJ_String_Set(CJ_String *string, const char * value);
const char * CJ_String_Get(CJ_String *string);

// object
typedef struct CJ_Object
{
	const uint64_t type;
} CJ_Object;

CJ_Object *CJ_Object_Create();
CJ_Object *CJ_Object_Copy(CJ_Object *var);
void CJ_Object_Destroy(CJ_Object *var);

uint64_t CJ_Object_Count(CJ_Object *var);
void CJ_Object_Attach(CJ_Object *object, const char * name, CJ_Variable *var);
CJ_Variable *CJ_Object_Detach(CJ_Object *object, const char * name);
CJ_Variable *CJ_Object_Get(CJ_Object *object, const char * name);

typedef struct CJ_Object_Iterator
{
	const char *const name;
	const CJ_Variable *var;
} CJ_Object_Iterator;

CJ_Object_Iterator *CJ_Object_IteratorBegin(CJ_Object *object);
CJ_Object_Iterator *CJ_Object_IteratorNext(CJ_Object *object, CJ_Object_Iterator *iterator);
CJ_Object_Iterator *CJ_Object_IteratorEnd(CJ_Object *object);

// array
typedef struct CJ_Array
{
	const uint64_t type;
} CJ_Array;

CJ_Array *CJ_Array_Create();
CJ_Array *CJ_Array_Copy(CJ_Array *var);
void CJ_Array_Destroy(CJ_Array *var);

uint64_t CJ_Array_Count(CJ_Array *array);
void CJ_Array_Attach(CJ_Array *array, CJ_Variable *variable);
CJ_Variable *CJ_Array_Detach(CJ_Array *array, uint64_t index);
void CJ_Array_Set(CJ_Array *array, uint64_t index, CJ_Variable *var);
CJ_Variable *CJ_Array_Get(CJ_Array *array, uint64_t index);

typedef struct _CJ_Array_Iterator
{
	const CJ_Variable *var;
} CJ_Array_Iterator;

CJ_Array_Iterator *CJ_Array_IteratorStart(CJ_Array *array);
CJ_Array_Iterator *CJ_Array_IteratorNext(CJ_Array *array, CJ_Array_Iterator *iterator);
CJ_Array_Iterator *CJ_Array_IteratorEnd(CJ_Array *array);

// error
typedef struct CJ_Error
{
	uint64_t error_type;
	const char * message;
} CJ_Error;
CJ_Error CJ_Get_Last_error();

typedef enum _CJ_ErrorType
{
	CJ_ERROR_NONE = 0,
	CJ_ERROR_UNEXPECTED_TOKEN,
	CJ_ERROR_UNKNOWN_CONTROL_CHARACTER,
	CJ_ERROR_VARIABLE_NULL,
	CJ_ERROR_NOT_INITIALIZED,
	CJ_ERROR_STRING_NULL
} CJ_ErrorType;

// util
CJ_Variable *CJ_Parse(const char *string);
void CJ_fprintf(FILE *file, const CJ_Variable *var);

#endif