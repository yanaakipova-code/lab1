#pragma once
#include "FuncType.h"
#include "StringType.h"
#include "ArrayEror.h"
#include "TypeInfo.h"

typedef struct DinamicArray{
    TypeInfo* type;
    void** data;
    unsigned int size;
    unsigned  int capacity;
}DinamicArray;

DinamicArray* create_array(TypeInfo* type, ArrayErrors* error);
void destroy_array(DinamicArray* arr, ArrayErrors* error);
void increasing_size(DinamicArray* arr, ArrayErrors* error);
void append(DinamicArray* arr, const void* elem, ArrayErrors* error);
void* get(const DinamicArray* arr, int index, ArrayErrors* error);
int get_size(const DinamicArray* arr, ArrayErrors* error);
void print_array(const DinamicArray* arr, ArrayErrors* error);
void add_to_array(DinamicArray* arr, void* elem, ArrayErrors* error);

DinamicArray* map(const DinamicArray* arr, 
                void* (*transform)(const void*, void*, ArrayErrors*),
                void* context,TypeInfo* new_type,ArrayErrors* error);
DinamicArray* where(DinamicArray* arr, 
                int(*predicate)(const void*, void*, ArrayErrors*),
                void* context,ArrayErrors* error);
DinamicArray* reduce(const DinamicArray* arr, 
                void* (*binop)(const void*, const void*, void*, ArrayErrors*), 
                void* context,const void* init,ArrayErrors* error);
DinamicArray* Concatenation(DinamicArray* arr1, DinamicArray* arr2, 
                            ArrayErrors* error);
