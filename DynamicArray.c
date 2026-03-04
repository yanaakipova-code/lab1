#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 4
#define ZERO_SIZE 0
#define RISING_AT_TWO 2

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
    
    for (unsigned int i = 0 ; i < arr->size; i++){
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
    unsigned int new_capacity = arr->capacity * RISING_AT_TWO;
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
char* array_to_string(const DinamicArray* arr, ArrayErrors* error) {
    if (arr == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    size_t total_size = 2;
    for (unsigned int i = 0; i < arr->size; i++) {
        if (arr->data[i] != NULL) {
            char* elem_str = arr->type->to_string(arr->data[i], error);
            if (*error != ARRAY_OK) {
                free(elem_str);
                return NULL;
            }
            
            total_size += strlen(elem_str);
            if (i < arr->size - 1) {
                total_size += 2;
            }
            free(elem_str);
        }
    }
    total_size += 1;
    
    char* result = (char*)malloc(total_size);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    char* ptr = result;
    *ptr++ = '[';
    
    for (unsigned int i = 0; i < arr->size; i++) {
        if (arr->data[i] != NULL) {
            char* elem_str = arr->type->to_string(arr->data[i], error);
            if (*error != ARRAY_OK) {
                free(elem_str);
                free(result);
                return NULL;
            }
            
            strcpy(ptr, elem_str);
            ptr += strlen(elem_str);
            free(elem_str);
            
            if (i < arr->size - 1) {
                strcpy(ptr, ", ");
                ptr += 2;
            }
        }
    }
    
    *ptr++ = ']';
    *ptr = '\0';
    
    if (error) *error = ARRAY_OK;
    return result;
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

DinamicArray* map(const DinamicArray* arr, 
                void* (*transform)(const void*, ArrayErrors*),
                TypeInfo* new_type, ArrayErrors* error) {
    if (arr == NULL || transform == NULL || new_type == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    DinamicArray* result = create_array(new_type, error);
    if (*error != ARRAY_OK) return NULL;
    
    for (unsigned int i = 0; i < arr->size; i++) {
        void* new_elem = transform(arr->data[i], error);
        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
        
        add_to_array(result, new_elem, error);
        if (*error != ARRAY_OK) {
            new_type->free(new_elem, NULL);
            destroy_array(result, NULL);
            return NULL;
        }
    }
    
    if (error) *error = ARRAY_OK;
    return result;
}

DinamicArray* where(const DinamicArray* arr, 
                int (*predicate)(const void*, ArrayErrors*),
                ArrayErrors* error) {
    if (arr == NULL || predicate == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    DinamicArray* result = create_array(arr->type, error);
    if (*error != ARRAY_OK) return NULL;

    for (unsigned int i = 0; i < arr->size; i++) {
        bool condition = predicate(arr->data[i], error);

        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
    
        if (condition) {
            void* temp = arr->type->clone(arr->data[i], error);
            if (*error != ARRAY_OK) {
                destroy_array(result, NULL);
                return NULL;
            }
            add_to_array(result, temp, error);
            if (*error != ARRAY_OK) {
                arr->type->free(temp, NULL);
                destroy_array(result, NULL);
                return NULL;
            }
        }
    }

    if (error) *error = ARRAY_OK;
    return result;
}

void* reduce(const DinamicArray* arr, 
                void* (*binop)(const void*, const void*, ArrayErrors*), 
                const void* init, ArrayErrors* error) {
    
    if (arr == NULL || binop == NULL || init == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    void* temp = arr->type->clone(init, error);
    if (*error != ARRAY_OK) return NULL;

    for (unsigned int i = 0; i < arr->size; i++) {
        void* new_temp = binop(temp, arr->data[i], error);
        
        if (*error != ARRAY_OK) {
            arr->type->free(temp, NULL);
            return NULL;
        }
        
        arr->type->free(temp, NULL);
        temp = new_temp;
    }
    if (error) *error = ARRAY_OK;
    return temp;
}

DinamicArray* concatenation(DinamicArray* arr1, DinamicArray* arr2, 
                            ArrayErrors* error){
    if (arr1 == NULL || arr2 == NULL){
        if(error)*error = NULL_POINTER;
        return NULL;
    }

    if(arr1->type != arr2->type){
        if(error)*error = DIFFERENT_TYPE;
        return NULL;
    }
    DinamicArray* result = create_array(arr1->type, error);
    if (*error != ARRAY_OK)return NULL;
    
    for (unsigned int i=0; i < arr1->size; i++){
        void* temp = arr1->type->clone(arr1->data[i], error);
        if (*error != ARRAY_OK){
            destroy_array(result, NULL);
            return NULL;
        }

        add_to_array(result, temp, error);
        if (*error != ARRAY_OK) {
            arr1->type->free(temp, NULL);
            destroy_array(result, NULL);
            return NULL;
        }
    }

    for (unsigned int i=0; i < arr2->size; i++){
        void* temp = arr2->type->clone(arr2->data[i], error);
        if (*error != ARRAY_OK){
            destroy_array(result, NULL);
            return NULL;
        }

        add_to_array(result, temp, error);
        if (*error != ARRAY_OK) {
            arr2->type->free(temp, NULL);
            destroy_array(result, NULL);
            return NULL;
        }
    }

    if (error) *error = ARRAY_OK;
    return result;
}