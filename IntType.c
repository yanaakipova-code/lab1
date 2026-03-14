#include "IntType.h"
#include <stdlib.h>
#include <stdio.h>

static TypeInfo* int_type_info = NULL;

void* int_clone(const void* elem, AllErrors* error){
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

void int_free(void* elem, AllErrors* error){
    if (elem){
        free(elem);
        if (error) *error = ARRAY_OK;
    } else{
        if (error) *error = NULL_POINTER;
    }
}

char* int_to_string(const void* elem, AllErrors* error) {
    if (!elem) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    char* str = (char*)malloc(12);
    if (!str) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    sprintf(str, "%d", *(const int*)elem);
    if (error) *error = ARRAY_OK;
    return str;
}

static size_t get_element_size() {
  return sizeof(int);
}

TypeInfo* get_int_type_info(){
    if (!int_type_info){
        int_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (int_type_info) {
            int_type_info->elem_size = get_element_size;
            int_type_info->clone = int_clone;
            int_type_info->free = int_free;
            int_type_info->to_string  = int_to_string;
            int_type_info->a_pointer = 0;
        }
    }
    return int_type_info;
}
