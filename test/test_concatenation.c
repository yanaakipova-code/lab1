#include "maintest.h"
#include "main_basic.h" 
#include "DynamicArray.h"
#include "DynamicArray.c"
#include "StringType.h"
#include "FuncType.h"
#include "IntType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inc(int x) {
    return x + 1;
}

int dec(int x) {
    return x - 1;
}

int square(int x) {
    return x * x;
}

TEST(concatenation_string_arrays) {
    puts("ТЕСТ 10.1");
    puts("---concatenation: объединение массивов строк---");
    AllErrors errors;
    DinamicArray* arr1 = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    append(arr1, "Hello", &errors);
    append(arr1, " ", &errors);
    DinamicArray* arr2 = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    append(arr2, "World", &errors);
    append(arr2, "!", &errors);
    
    DinamicArray* result = concatenation(arr1, arr2, &errors);

    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 4);
    char* val0 = (char*)get(result, 0, &errors);
    char* val1 = (char*)get(result, 1, &errors);
    char* val2 = (char*)get(result, 2, &errors);
    char* val3 = (char*)get(result, 3, &errors);
    assert(strcmp(val0, "Hello") == 0);
    assert(strcmp(val1, " ") == 0);
    assert(strcmp(val2, "World") == 0);
    assert(strcmp(val3, "!") == 0);
}

TEST(concatenation_func_arrays) {
    puts("ТЕСТ 10.2");
    puts("---concatenation: объединение массивов функций---");
    AllErrors errors;
    DinamicArray* arr1 = create_array(get_func_type_info(), &errors);
    assert(errors == ARRAY_OK);
    append(arr1, inc, &errors);
    append(arr1, dec, &errors);
    DinamicArray* arr2 = create_array(get_func_type_info(), &errors);
    assert(errors == ARRAY_OK);
    append(arr2, square, &errors);
    
    DinamicArray* result = concatenation(arr1, arr2, &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 3);
    
    IntFunc f0= (IntFunc)get(result, 0, &errors);
    IntFunc f1 = (IntFunc)get(result, 1, &errors);
    IntFunc f2 = (IntFunc)get(result, 2, &errors);
    
    assert(f0(5) == 6);
    assert(f1(5) == 4);
    assert(f2(5) == 25);
}

TEST(concatenation_empty_first) {
    puts("ТЕСТ 10.3");
    puts("---concatenation: пустой первый массив + непустой второй---");
    AllErrors errors;
    DinamicArray* empty = create_array(get_string_type_info(), &errors);
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "test", &errors);
    
    DinamicArray* result = concatenation(empty, arr, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 1);
    char* val = (char*)get(result, 0, &errors);
    assert(strcmp(val, "test") == 0);
}

TEST(concatenation_empty_second) {
    puts("ТЕСТ 10.4");
    puts("---concatenation: непустой первый + пустой второй---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "test", &errors);
    DinamicArray* empty = create_array(get_string_type_info(), &errors);
    
    DinamicArray* result = concatenation(arr, empty, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 1);
    char* val = (char*)get(result, 0, &errors);
    assert(strcmp(val, "test") == 0);
}

TEST(concatenation_both_empty) {
    puts("ТЕСТ 10.5");
    puts("---concatenation: два пустых массива---");
    AllErrors errors;
    DinamicArray* empty1 = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    DinamicArray* empty2 = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    
    DinamicArray* result = concatenation(empty1, empty2, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 0);
    char* str = array_to_string(result, &errors);
    assert(strcmp(str, "[]") == 0);
}

TEST(concatenation_different_types) {
    puts("ТЕСТ 10.6");
    puts("---concatenation: объединение массивов разных типов---");
    AllErrors errors;
    
    DinamicArray* str_arr = create_array(get_string_type_info(), &errors);
    DinamicArray* func_arr = create_array(get_func_type_info(), &errors);
    
    DinamicArray* result = concatenation(str_arr, func_arr, &errors);

    assert(errors == DIFFERENT_TYPE);
    assert(result == NULL);
}

TEST(concatenation_null_first) {
    puts("ТЕСТ 10.7");
    puts("---concatenation: первый массив NULL---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    
    DinamicArray* result = concatenation(NULL, arr, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(concatenation_null_second) {
    puts("ТЕСТ 10.5.2");
    puts("---concatenation: второй массив NULL---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    
    DinamicArray* result = concatenation(arr, NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}