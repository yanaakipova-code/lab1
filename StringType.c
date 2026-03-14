#include "StringType.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static TypeInfo* string_type_info = NULL;

static size_t get_element_size() {
  return sizeof(char*);
}

void* string_clone(const void* elem, AllErrors* error){

    if (elem == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
     
    const char* str = (const char*)elem;
    char* copy = malloc(strlen(str)+1);
    if (copy == NULL){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }else{
         strcpy(copy, str);
         if (error) *error = ARRAY_OK;
        return copy;
        }
}

void string_free(void* elem,AllErrors* error){
    if (elem != NULL) {
        free(elem);
        if(error) *error = ARRAY_OK;
        return;
    }
    if (error) *error = NULL_POINTER;
}

char* string_to_string(const void* elem, AllErrors* error) {
    if (elem == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    const char* str = (const char*)elem;
    char* result = (char*)malloc(strlen(str) + 3);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    sprintf(result, "\"%s\"", str);
    if (error) *error = ARRAY_OK;
    return result;
}

char* string_concatenate(const char* s1, const char* s2, AllErrors* error) {
    if (!s1 || !s2) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1);
    
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    strcpy(result, s1);
    strcat(result, s2);
    
    if (error) *error = ARRAY_OK;
    return result;
}

TypeInfo* get_string_type_info() {
    if (string_type_info == NULL) {
        string_type_info = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (string_type_info) {
            string_type_info->elem_size=get_element_size;
            string_type_info->clone = string_clone;
            string_type_info->free = string_free;
            string_type_info->to_string = string_to_string;
            string_type_info->a_pointer = 1;
        }
    }
    return string_type_info;
}
