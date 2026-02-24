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
