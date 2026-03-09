#include "FuncType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FUNCTION_COUNT  3

static TypeInfo* FUNC_TYPE_INFO = NULL;

typedef int (*IntFunc)(int);

void* func_clone(const void* elem, ArrayErrors* error){
    if (elem == NULL){
        if (error)*error = NULL_POINTER;
        return NULL;
    }
    if (error)*error = ARRAY_OK;
    return (void*)elem;
}

void func_free(void* elem, ArrayErrors* error) {
    if (error) *error = ACTION_UNDEFINED;
}

static char* func_to_string(const void* elem, ArrayErrors* error) {
    if (elem == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    IntFunc f = (IntFunc)elem;
    char* result = (char*)malloc(20);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    sprintf(result, "func at %p", f);
    if (error) *error = ARRAY_OK;
    return result;
}

TypeInfo* GetFuncTypeInfo() {
    if (FUNC_TYPE_INFO == NULL) {
        FUNC_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        FUNC_TYPE_INFO->clone = func_clone;
        FUNC_TYPE_INFO->free = func_free;
        FUNC_TYPE_INFO->to_string  = func_to_string;
    }
    return FUNC_TYPE_INFO;
}
