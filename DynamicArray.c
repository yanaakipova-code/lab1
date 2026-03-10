#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define ZERO_SIZE 0
#define RISING_AT_TWO 2


static void* element_ptr(DinamicArray* arr, int index){
    size_t elem_size = arr->type->elem_size();
    return (char*)arr->data + (index * elem_size);
}

DinamicArray* create_array(TypeInfo* type, AllErrors* error){
    if (type == NULL){
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    DinamicArray* arr = (DinamicArray*)malloc(sizeof(DinamicArray));
    if (arr==NULL){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    size_t elem_size = type->elem_size();
    arr->data = malloc(INITIAL_CAPACITY * elem_size);
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

void destroy_array(DinamicArray* arr, AllErrors* error){
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return;
    }
    size_t elem_size = arr->type->elem_size(); 
    char* ptr = (char*)arr->data;

    for (unsigned int i = 0 ; i < arr->size; i++){
         void* elem;
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            elem = *(void**)(ptr + i * elem_size);
        } else {
            elem = ptr + i * elem_size;
        }
        
        if (elem) {
            arr->type->free(elem, error);
        }
    }
    free(arr->data);
    free(arr);
    
    if (error)*error = ARRAY_OK;
}

void increasing_size(DinamicArray* arr, AllErrors* error){
    if (arr->size<arr->capacity){
         if (error) *error = ARRAY_OK;
        return;
    }
    size_t elem_size = arr->type->elem_size(); 
    unsigned int new_capacity = arr->capacity * RISING_AT_TWO;
    void* new_data = realloc(arr->data, new_capacity * elem_size);
    if (new_data == NULL) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return;
    }
    arr->data = new_data;
    arr->capacity = new_capacity;
    
    if (error) *error = ARRAY_OK;

}

void append(DinamicArray* arr, const void* elem, AllErrors* error) {
    if (elem == NULL || arr == NULL) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    increasing_size(arr, error);
    if (*error != ARRAY_OK) return;

    size_t elem_size = arr->type->elem_size(); 
    void* dest = element_ptr(arr, arr->size);
    
    if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
        void* copy = arr->type->clone(elem, error);
        if (*error != ARRAY_OK) return;
        *(void**)dest = copy;
    } else {
        memcpy(dest, elem, elem_size);
    }
    
    arr->size++;
    
    if (error) *error = ARRAY_OK;
}

void* get(const DinamicArray* arr, int index, AllErrors* error) {
    if (arr == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    if (index < 0 || index >= arr->size) {
        if (error) *error = INDEX_OUT;
        return NULL;
    }
    
    size_t elem_size = arr->type->elem_size(); 
    void* elem_ptr = element_ptr((DinamicArray*)arr, index);
    
    if (error) *error = ARRAY_OK;
    if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
        return *(void**)elem_ptr;
    } else {
        return elem_ptr;
    }
}
int get_size(const DinamicArray* arr, AllErrors* error){
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return -1;
    }
    
    if (error) *error = ARRAY_OK;
    return arr->size;
}
char* array_to_string(const DinamicArray* arr, AllErrors* error) {
    if (arr == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    size_t total_size = 2;
    size_t elem_size = arr->type->elem_size(); 
    
    for (unsigned int i = 0; i < arr->size; i++) {
        void* elem_ptr = element_ptr((DinamicArray*)arr, i);
        void* elem;
        
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            elem = *(void**)elem_ptr;
        } else {
            elem = elem_ptr;
        }
        
        if (elem) {
            char* elem_str = arr->type->to_string(elem, error);
            if (*error != ARRAY_OK) {
                free(elem_str);
                return NULL;
            }
            
            total_size += strlen(elem_str);
            if (i < arr->size - 1) total_size += 2;
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
        void* elem_ptr = element_ptr((DinamicArray*)arr, i);
        void* elem;
        
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            elem = *(void**)elem_ptr;
        } else {
            elem = elem_ptr;
        }
        
        if (elem) {
            char* elem_str = arr->type->to_string(elem, error);
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

void add_to_array(DinamicArray* arr, void* elem, AllErrors* error) {
    if (arr == NULL || elem == NULL) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    increasing_size(arr, error);
    if (*error != ARRAY_OK) return;
    
    size_t elem_size = arr->type->elem_size(); 
    void* dest = element_ptr(arr, arr->size);
    
    if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
        *(void**)dest = elem;
    } else {
        memcpy(dest, elem, elem_size);
        free(elem);
    }
    
    arr->size++;
    
    if (error) *error = ARRAY_OK;
}

DinamicArray* map(const DinamicArray* arr, 
                void (*transform)(const void* src, void* dst, AllErrors*),
                TypeInfo* new_type, AllErrors* error) {
    if (arr == NULL || transform == NULL || new_type == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    size_t src_elem_size = arr->type->elem_size();
    size_t dst_elem_size = new_type->elem_size();
    DinamicArray* result = create_array(new_type, error);
    if (*error != ARRAY_OK) return NULL;

    if (result->capacity < arr->size) {
        size_t new_capacity = arr->size;
        size_t new_size = new_capacity * dst_elem_size;
        void* new_data = realloc(result->data, new_size);
        if (new_data == NULL) {
            destroy_array(result, NULL);
            if (error) *error = MEMORY_ALLOCATION_FAILED;
            return NULL;
        }
        result->data = new_data;
        result->capacity = new_capacity;
    }

    for (unsigned int i = 0; i < arr->size; i++) {
        void* src_ptr = (char*)arr->data + (i * src_elem_size);
        void* src_elem;
        
        if (src_elem_size == sizeof(char*) || src_elem_size == sizeof(void*)) {
            src_elem = *(void**)src_ptr;
        } else {
            src_elem = src_ptr;
        }
        void* dest_ptr = (char*)result->data + (i * dst_elem_size);
        transform(src_elem, dest_ptr, error);

        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
        
        result->size++;
    }
    
    if (error) *error = ARRAY_OK;
    return result;
}

DinamicArray* where(const DinamicArray* arr, 
                int (*predicate)(const void*, AllErrors*),
                AllErrors* error) {
    if (arr == NULL || predicate == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    DinamicArray* result = create_array(arr->type, error);
    if (*error != ARRAY_OK) return NULL;

    size_t elem_size = arr->type->elem_size(); 

    for (unsigned int i = 0; i < arr->size; i++) {
        void* elem_ptr = (char*)arr->data + (i * elem_size);
        void* elem;
        
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            elem = *(void**)elem_ptr;
        } else {
            elem = elem_ptr;
        }

        int condition = predicate(elem, error);
        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }

        if (condition) {
            increasing_size(result, error);
            if (*error != ARRAY_OK) {
                destroy_array(result, NULL);
                return NULL;
            }
            
            void* dest = (char*)result->data + (result->size * elem_size);
            
            if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
                void* copy = arr->type->clone(elem, error);
                if (*error != ARRAY_OK) {
                    destroy_array(result, NULL);
                    return NULL;
                }
                *(void**)dest = copy;
            } else {
                memcpy(dest, elem_ptr, elem_size);
            }
            
            result->size++;
        }
    }

    if (error) *error = ARRAY_OK;
    return result;
}

void* reduce(const DinamicArray* arr, 
                void* (*binop)(const void*, const void*, AllErrors*), 
                const void* init, AllErrors* error) {
    
    if (arr == NULL || binop == NULL || init == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    size_t elem_size =arr->type->elem_size(); 
    
    void* temp = arr->type->clone(init, error);
    if (*error != ARRAY_OK) return NULL;

    for (unsigned int i = 0; i < arr->size; i++) {
        void* elem_ptr = (char*)arr->data + (i * elem_size);
        void* elem;
        
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            elem = *(void**)elem_ptr;
        } else {
            elem = elem_ptr;
        }
        
        void* new_temp = binop(temp, elem, error);
        
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
                            AllErrors* error) {
    if (arr1 == NULL || arr2 == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    if (arr1->type->clone != arr2->type->clone ||
        arr1->type->free != arr2->type->free ||
        arr1->type->to_string != arr2->type->to_string) {
        if (error) *error = DIFFERENT_TYPE;
        return NULL;
    }
    
    DinamicArray* result = create_array(arr1->type, error);
    if (*error != ARRAY_OK) return NULL;
    
    size_t elem_size = arr1->type->elem_size();  
    
    for (unsigned int i = 0; i < arr1->size; i++) {
        increasing_size(result, error);
        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
        
        void* src_ptr = (char*)arr1->data + (i * elem_size);
        void* dest_ptr = (char*)result->data + (result->size * elem_size);
        
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            void* src_elem = *(void**)src_ptr;
            void* copy = arr1->type->clone(src_elem, error);
            if (*error != ARRAY_OK) {
                destroy_array(result, NULL);
                return NULL;
            }
            *(void**)dest_ptr = copy;
        } else {
            memcpy(dest_ptr, src_ptr, elem_size);
        }
        
        result->size++;
    }
    
    for (unsigned int i = 0; i < arr2->size; i++) {
        increasing_size(result, error);
        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
        
        void* src_ptr = (char*)arr2->data + (i * elem_size);
        void* dest_ptr = (char*)result->data + (result->size * elem_size);
        
        if (elem_size == sizeof(char*) || elem_size == sizeof(void*)) {
            void* src_elem = *(void**)src_ptr;
            void* copy = arr2->type->clone(src_elem, error);
            if (*error != ARRAY_OK) {
                destroy_array(result, NULL);
                return NULL;
            }
            *(void**)dest_ptr = copy;
        } else {
            memcpy(dest_ptr, src_ptr, elem_size);
        }
        
        result->size++;
    }
    
    if (error) *error = ARRAY_OK;
    return result;
}