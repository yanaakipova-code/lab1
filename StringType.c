#include "StringType.h"

#include <stdlib.h>
#include <string.h>

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

TypeInfo* GetStringTypeInfo(){
    if (STRING_TYPE_INFO == NULL){
        STRING_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        STRING_TYPE_INFO->clone = string_clone;
        STRING_TYPE_INFO->free = string_free;
        STRING_TYPE_INFO->print = string_print;
    }
    return STRING_TYPE_INFO; 
}

void FreeStringTypeInfo(){
    if (STRING_TYPE_INFO != NULL){  
        free(STRING_TYPE_INFO);
        STRING_TYPE_INFO = NULL;
    }
}

