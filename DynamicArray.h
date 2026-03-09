#pragma once
#include "FuncType.h"
#include "StringType.h"
#include "ArrayEror.h"
#include "TypeInfo.h"
#include "IntType.h"

typedef struct DinamicArray{
    TypeInfo* type;
    void* data;
    unsigned int size;
    unsigned  int capacity;
}DinamicArray;

DinamicArray* create_array(TypeInfo* type, ArrayErrors* error);
void destroy_array(DinamicArray* arr, ArrayErrors* error);
void increasing_size(DinamicArray* arr, ArrayErrors* error);
void append(DinamicArray* arr, const void* elem, ArrayErrors* error);
void* get(const DinamicArray* arr, int index, ArrayErrors* error);
int get_size(const DinamicArray* arr, ArrayErrors* error);
char* array_to_string(const DinamicArray* arr, ArrayErrors* error);
void add_to_array(DinamicArray* arr, void* elem, ArrayErrors* error);

DinamicArray* map(const DinamicArray* arr, 
                void* (*transform)(const void*, ArrayErrors*),
                TypeInfo* new_type, ArrayErrors* error);
DinamicArray* where(const DinamicArray* arr, 
                int (*predicate)(const void*, ArrayErrors*),
                ArrayErrors* error);
void* reduce(const DinamicArray* arr, 
                void* (*binop)(const void*, const void*, ArrayErrors*), 
                const void* init, ArrayErrors* error);
DinamicArray* concatenation(DinamicArray* arr1, DinamicArray* arr2, 
                            ArrayErrors* error);