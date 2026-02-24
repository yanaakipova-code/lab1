#include "IntType.h"
#include <stdlib.h>
#include <stdio.h>

static TypeInfo* INT_TYPE_INFO = NULL;

void* int_clone(const void* elem, ArrayErrors* error){
    if (!elem){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    int* copy = (int*)malloc(sizeof(int));
    if (!copy){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    *copy = *(const int*)elem;
    if (error) *error = ARRAY_OK;
    return copy;
}

void int_free(void* elem, ArrayErrors* error){
    if (elem){
        free(elem);
        if (error) *error = ARRAY_OK;
    } else{
        if (error) *error = NULL_POINTER;
    }
}

void int_print(const void* elem, ArrayErrors* error){
    if (!elem){
        if (error) *error = NULL_POINTER;
        return;
    }
    printf("%d", *(const int*)elem);
    if (error) *error = ARRAY_OK;
}

TypeInfo* GetIntTypeInfo(){
    if (!INT_TYPE_INFO){
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (INT_TYPE_INFO) {
            INT_TYPE_INFO->kind = TYPE_INT;
            INT_TYPE_INFO->clone = int_clone;
            INT_TYPE_INFO->free = int_free;
            INT_TYPE_INFO->print = int_print;
        }
    }
    return INT_TYPE_INFO;
}

void FreeIntTypeInfo(){
    if (INT_TYPE_INFO){
        free(INT_TYPE_INFO);
        INT_TYPE_INFO = NULL;
    }
}