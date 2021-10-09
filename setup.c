#include "internal.h"

CM_Heap *g_cj_heap_variable = NULL;
CM_HeapString* g_cj_heap_string = NULL;

void cj_init()
{
	cj_error_callback_print_set(CJ_ERROR_PRINT_ENABLED);
	g_cj_heap_variable = cm_heap_create();
	g_cj_heap_string = cm_heap_string_create();
}

void cj_terminate()
{
	cm_heap_destroy(g_cj_heap_variable);
	cm_heap_string_destroy(g_cj_heap_string);
}