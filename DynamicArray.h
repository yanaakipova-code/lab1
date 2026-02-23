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

DinamicArray* createArray(TypeInfo* type, ArrayErrors* error);
void destroyArray(DinamicArray* arr, ArrayErrors* error);
void increasing_size(DinamicArray* arr, ArrayErrors* error);
void append(DinamicArray* arr, const void* elem, ArrayErrors* error);