#include "StringType.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static TypeInfo* STRING_TYPE_INFO = NULL;

void* string_clone(const void* elem, ArrayErrors* error){

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

void string_free(void* elem,ArrayErrors* error){
    if (elem != NULL) {
        free(elem);
        if(error) *error = ARRAY_OK;
        return;
    }
    if (error) *error = NULL_POINTER;
}

void string_print(const void* elem, ArrayErrors* error){
    if (elem != NULL){
        if(error) *error = ARRAY_OK;
        const char* str = (const char*)elem;
        printf("\"%s\"", str );
    } 
    if (error) *error = NULL_POINTER;
}

char* string_concatenate(const char* s1, const char* s2, ArrayErrors* error) {
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

TypeInfo* GetStringTypeInfo(){
    if (STRING_TYPE_INFO == NULL){
        STRING_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (STRING_TYPE_INFO) {
            STRING_TYPE_INFO->kind = TYPE_STRING;
            STRING_TYPE_INFO->clone = string_clone;
            STRING_TYPE_INFO->free = string_free;
            STRING_TYPE_INFO->print = string_print;
        }
    }
    return STRING_TYPE_INFO; 
}

void FreeStringTypeInfo(){
    if (STRING_TYPE_INFO != NULL){  
        free(STRING_TYPE_INFO);
        STRING_TYPE_INFO = NULL;
    }
}

