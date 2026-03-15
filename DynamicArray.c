#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define ZERO_SIZE 0
#define RISING_AT_TWO 2

static void error_null(AllErrors* error){
    if(error == NULL){
        return;
    }
}

static void* element_ptr(DinamicArray* arr, int index){
    size_t elem_size = arr->type->elem_size();
    return (char*)arr->data + (index * elem_size);
}

DinamicArray* create_array(TypeInfo* type, AllErrors* error){
    error_null(error);
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
    error_null(error);
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return;
    }
    if (arr->type->a_pointer) {
        size_t elem_size = arr->type->elem_size();
        for (unsigned int i = 0; i < arr->size; i++) {
            void* elem_ptr = *(void**)((char*)arr->data + i * elem_size);
            if (elem_ptr) {
                arr->type->free(elem_ptr, error);
            }
        }
    }
    
    free(arr->data);
    free(arr);
    
    if (error) *error = ARRAY_OK;
}

//обычно это называют resize ?
void increasing_size(DinamicArray* arr, AllErrors* error){
    error_null(error);
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return;
    }
    /* все ок, ничего не надо делать*/
    if (arr->size < arr->capacity){
        if (error) *error = ARRAY_OK;
        return;
    }
    /*надо увеличить*/
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
    error_null(error);
    if (elem == NULL || arr == NULL) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    increasing_size(arr, error);
    if (*error != ARRAY_OK) return;

    size_t elem_size = arr->type->elem_size(); 
    void* dest = element_ptr(arr, arr->size);
    
    if (arr->type->a_pointer) {
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
    error_null(error);
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
    if (arr->type->a_pointer) {
        return *(void**)elem_ptr;
    } else {
        return elem_ptr;
    }
}
int get_size(const DinamicArray* arr, AllErrors* error){
    error_null(error);
    if (arr == NULL){
        if (error) *error = NULL_POINTER;
        return -1;
    }
    
    if (error) *error = ARRAY_OK;
    return arr->size;
}
char* array_to_string(const DinamicArray* arr, AllErrors* error) {
    error_null(error);
    if (arr == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    size_t total_size = 2;
    size_t elem_size = arr->type->elem_size(); 
    
    for (unsigned int i = 0; i < arr->size; i++) {
        void* elem_ptr = element_ptr((DinamicArray*)arr, i);
        void* elem;
        
        if (arr->type->a_pointer) {
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
        
        if (arr->type->a_pointer) {
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
    error_null(error);
    if (arr == NULL || elem == NULL) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    increasing_size(arr, error);
    if (*error != ARRAY_OK) return;
    
    size_t elem_size = arr->type->elem_size(); 
    void* dest = element_ptr(arr, arr->size);
    
    if (arr->type->a_pointer) {
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
    error_null(error);
    
    if(arr == NULL || transform == NULL || new_type == NULL){
        if (error)*error == NULL_POINTER;
    }

    DinamicArray* result = create_array(new_type, error);
    if(*error != ARRAY_OK) return NULL;

    for (unsigned int i = 0; i < arr->size; i++){
        void* src_ptr = (char*)arr->data + (i*arr->type->elem_size());
        void* src_elem;
        if(arr->type->a_pointer){
            src_elem = *(void**)src_ptr;
        }else{
            src_elem = src_ptr;
        }
        void* temp = malloc(new_type->elem_size());
        if (!temp) {
            if (error) *error = MEMORY_ALLOCATION_FAILED;
            destroy_array(result, NULL);
            return NULL;
        }
        transform(src_elem, temp, error);
        if (*error != ARRAY_OK) {
            free(temp);
            destroy_array(result, NULL);
            return NULL;
        }
        if (new_type->a_pointer) {
            add_to_array(result, *(void**)temp, error);
        } else {
            append(result, temp, error);
        }
        free(temp);
        
        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
    }
    return result;

}

DinamicArray* where(const DinamicArray* arr, 
                int (*predicate)(const void*, AllErrors*),
                AllErrors* error) {
    error_null(error);
    if (arr == NULL || predicate == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }

    DinamicArray* result = create_array(arr->type, error);
    if (*error != ARRAY_OK) return NULL;

    size_t elem_size = arr->type->elem_size(); 

    for (unsigned int i = 0; i < elem_size; i++) {
        void* elem_ptr = (char*)arr->data + (i * elem_size);
        void* elem;
        
        if (arr->type->a_pointer) {
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
            
            if (arr->type->a_pointer) {
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
    
    error_null(error);
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
        
        if (arr->type->a_pointer) {
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
    error_null(error);
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
    size_t total_size = arr1->size + arr2->size;  
    
    if(result->capacity < total_size){
        void* new_data = realloc(result->data,total_size*elem_size);
        if (new_data == NULL){
            destroy_array(result, error);
            if(error)*error = NULL_POINTER;
            return NULL;
        }
        result->data = new_data;
        result->capacity = total_size;

    }

    for (unsigned int i = 0; i < arr1->size; i++) {
        increasing_size(result, error);
        if (*error != ARRAY_OK) {
            destroy_array(result, NULL);
            return NULL;
        }
        
        void* src_ptr = (char*)arr1->data + (i * elem_size);
        void* dest_ptr = (char*)result->data + (result->size * elem_size);
        
        if (arr1->type->a_pointer) {
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
        
        if (arr2->type->a_pointer) {
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