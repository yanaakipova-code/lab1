#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 4
#define ZERO_SIZE 0

DinamicArray* create_array(TypeInfo* type, ArrayErrors* error){
    if (type == NULL){
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    DinamicArray* arr = (DinamicArray*)malloc(sizeof(DinamicArray));
    if (arr==NULL){
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    arr->data=(void**)malloc(INITIAL_CAPACITY * sizeof(void*));
    if (arr->data == NULL){
        free(arr);
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    arr->type = type;
    arr->size = ZERO_SIZE;
    arr->capacity = INITIAL_CAPACITY;

    if (error)*error = ARRAY_OK;
    return arr;
}

void destroy_array(DinamicArray* arr, ArrayErrors* error){
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
    }
    
    for (unsigned int i; i < arr->size; i++){
        if (arr->data != NULL){
            arr->type->free(arr->data[i], error);
        }
    }
    free(arr->data);
    free(arr);
    
    if (error)*error = ARRAY_OK;
}

void increasing_size(DinamicArray* arr, ArrayErrors* error){
    if (arr->size<arr->capacity){
         if (error) *error = ARRAY_OK;
        return;
    }
    unsigned int new_capacity = arr->capacity * 2;
    void** new_data = (void**)realloc(arr->data, new_capacity * sizeof(void*));
    if (new_data == NULL) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return;
    }
    arr->data = new_data;
    arr->capacity = new_capacity;
    
    if (error) *error = ARRAY_OK;

}

void append(DinamicArray* arr, const void* elem, ArrayErrors* error){
    if (elem == NULL || arr == NULL){
        if (error)*error = NULL_POINTER;
        return;
    }
    
    increasing_size(arr, error);
    if (*error != ARRAY_OK) {
        return;
    }

    void* copy = arr->type->clone(elem, error);
    if (*error != ARRAY_OK) {
        return;
    }

    arr->data[arr->size] = copy;
    arr->size++;
    
    if (error) *error = ARRAY_OK;
}

void* get(const DinamicArray* arr, int index, ArrayErrors* error){
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    if (index < 0 || index >= arr->size){
        if (error) *error = INDEX_OUT;
        return NULL;
    }
    
    if (error) *error = ARRAY_OK;
    return arr->data[index];
}

int get_size(const DinamicArray* arr, ArrayErrors* error){
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return -1;
    }
    
    if (error) *error = ARRAY_OK;
    return arr->size;
}


void print_array(const DinamicArray* arr, ArrayErrors* error){
    if (arr == NULL) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    printf("[");
    for (int i = 0; i < arr->size; i++){
        if (arr->data[i] != NULL){
            arr->type->print(arr->data[i], error);
        }
    }
    printf("]");
    
    if (error) *error = ARRAY_OK;
}

void add_to_array(DinamicArray* arr, void* elem, ArrayErrors* error){
    if (arr == NULL || elem == NULL){
        if (error) *error = NULL_POINTER;
        return;
    }
    
    increasing_size(arr, error);
    if (*error != ARRAY_OK) return;
    
    arr->data[arr->size] = elem;
    arr->size++;
    
    if (error) *error = ARRAY_OK;
}



