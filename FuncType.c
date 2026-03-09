#include "FuncType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FUNCTION_COUNT  3

static TypeInfo* func_type_info = NULL;

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

static size_t get_element_size() {
  return sizeof(int);
}

TypeInfo* get_func_type_info() {
    if (func_type_info == NULL) {
        func_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));
        func_type_info->elem_size = get_element_size;
        func_type_info->clone = func_clone;
        func_type_info->free = func_free;
        func_type_info->to_string  = func_to_string;
    }
    return func_type_info;
}
