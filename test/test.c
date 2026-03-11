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

TEST(create_array_string){
    puts("ТЕСТ 1.1");
    puts("---Создание массива строк---");
    AllErrors errors;

    DinamicArray* arr = create_array(get_string_type_info(), &errors);

    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == ZERO_SIZE);
    assert(arr->capacity == INITIAL_CAPACITY);

}

TEST(test_create_array_func){ 
    puts("ТЕСТ 1.1");
    puts("---Создание массива функций---");
    AllErrors errors;

    DinamicArray* arr = create_array(get_func_type_info(), &errors);

    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == ZERO_SIZE);
    assert(arr->capacity == INITIAL_CAPACITY);
}

TEST(test_create_array){
    puts("ТЕСТ 1.1");
    puts("---Пограничное значение функции создания массива---");
    AllErrors errors;

    DinamicArray* arr = create_array(NULL, &errors);

    assert(errors == NULL_POINTER);
}

TEST(test_destroy_array_ok){
    puts("ТЕСТ 2.1");
    puts("---Разрушение массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);

    destroy_array(arr, &errors);

    assert(errors == ARRAY_OK);
}

TEST(test_destroy_array_fl){
    puts("ТЕСТ 2.2");
    puts("---Разрушение массива c NULL---");
    AllErrors errors;

    destroy_array(NULL, &errors);

    assert(errors == NULL_POINTER);
}

TEST(test_append){
    puts("ТЕСТ 3.1");
    puts("---добавление элемента в массив---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    const char* elem ="y";
    unsigned int start_capacity = arr->capacity;

    append(arr, elem, &errors);

    assert(errors == ARRAY_OK);
    assert(arr->size == start_capacity++);
}

TEST(test_increasing_size){
    puts("ТЕСТ 3.2");
    puts("---Увеличение емкости массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    const char* elem ="y";
    unsigned int start_capacity = arr->capacity;

    for (unsigned int i = 0; i < start_capacity; i++){
        append(arr, elem, &errors);
    }
    append(arr, elem, &errors);

    assert(errors == ARRAY_OK);
    assert(arr->capacity == start_capacity * RISING_AT_TWO);
}

TEST(test_increasing_size_fl){
    puts("ТЕСТ 3.3");
    puts("---Увеличение ёмкости массива с NULL---");
    AllErrors errors;
    increasing_size(NULL,&errors);

    assert(errors == NULL_POINTER); 
}

TEST(test_append_fl){
    puts("ТЕСТ 3.4");
    puts("---Добавление элемента с NULL---");
    const char elem ="y";
    AllErrors errors;

    append(NULL,elem, &errors);

    assert(errors == NULL_POINTER);
}

TEST(get_by_valid_index){
    puts("ТЕСТ 4.1");
    puts("---Получение элемента по индексу---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);
    append(arr, "l", &errors);
    append(arr, "o", &errors);
    char* element = (char*)get(arr, 2, &errors);

    assert(errors == ARRAY_OK);
    assert(strcmp(element, "l") == 0);
}
TEST(get_by_index_negative){
    puts("ТЕСТ 4.2");
    puts("---Отрицательный индекс массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);
    append(arr, "l", &errors);
    append(arr, "o", &errors);
    char* element = (char*)get(arr, 2, &errors);

    get(arr, -1, &errors);

    assert(errors == INDEX_OUT);
}

TEST(get_by_index_out_bounds){
    puts("ТЕСТ 4.3");
    puts("---Индекс все диапазона---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);
    append(arr, "l", &errors);
    append(arr, "o", &errors);
    char* element = (char*)get(arr, 2, &errors);

    get(arr, 5, &errors);
    assert(errors == INDEX_OUT);
}

TEST(get_by_empty_array){
    puts("ТЕСТ 4.4");
    puts("---Индекс пустого массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);

    get(arr, 0, &errors);
    assert(errors == INDEX_OUT);
}

TEST(test_get_size){
    puts("ТЕСТ 5.1");
    puts("---Получение размера массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);

    unsigned size = get_size(arr, &errors);

    assert(size == 3);
}

TEST(test_get_size_empty_array){
    puts("ТЕСТ 5.2");
    puts("---Получение размера массива с нулевой длиной---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);

    unsigned size = get_size(arr, &errors);

    assert(size == 0);
}
  
TEST(test_get_size_null_array){
    puts("ТЕСТ 5.3");
    puts("---Получение размера массива с NULL---");
    AllErrors errors;

    unsigned size = get_size(NULL, &errors);

    assert(errors == NULL_POINTER);
}

TEST(test_array_to_string){
    puts("ТЕСТ 6.1");
    puts("---Преобразование массива в строку---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "hello", &errors);
    append(arr, "world", &errors);
    append(arr, "!", &errors);

    char* str = array_to_string(arr, &errors);

    assert(errors == ARRAY_OK);
    assert(strcmp(str, "[\"hello\", \"world\", \"!\"]") == 0);
    
    free(arr);
}
TEST(test_array_to_string_empty_array){
    puts("ТЕСТ 6.2");
    puts("---Преобразование пустого массива в строку---");
    AllErrors errors;
    DinamicArray* empty_arr = create_array(get_string_type_info(), &errors);

    unsigned str = array_to_string(empty_arr, &errors);

    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[]") == 0);

    free(str);
}
TEST(test_array_to_string_null){
    puts("ТЕСТ 6.3");
    puts("---Преобразование массива в строку с NULL указателем---");
    AllErrors errors;
    unsigned str = array_to_string(NULL, &errors);

    assert(errors == NULL_POINTER);
    assert(str == NULL);
    
}

TEST(array_to_string_int){
    puts("ТЕСТ 6.4");
    puts("---Преобразование массива чисел в строку---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_int_type_info(), &errors);
    int a = 10, b = 20, c = 30;
    append(arr, &a, &errors);
    append(arr, &b, &errors);
    append(arr, &c, &errors);

    char* str = array_to_string(arr, &errors);

    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[10, 20, 30]") == 0);
}


TEST(map_string_to_upper) {
    puts("ТЕСТ 7.1");
    puts("---map: преобразование строк в верхний регистр---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "hello", &errors);
    append(arr, "world", &errors);
    append(arr, "test", &errors);
    assert(errors == ARRAY_OK);
    
    DinamicArray* result = map(arr, string_to_upper, get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 3);
    
    char* val0 = (char*)get(result, 0, &errors);
    char* val1 = (char*)get(result, 1, &errors);
    char* val2 = (char*)get(result, 2, &errors);
    assert(strcmp(val0, "HELLO") == 0);
    assert(strcmp(val1, "WORLD") == 0);
    assert(strcmp(val2, "TEST") == 0);
}

TEST(map_string_to_lower) {
    puts("ТЕСТ 7.2");
    puts("---map: преобразование строк в нижний регистр---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "HELLO", &errors);
    append(arr, "WORLD", &errors);
    append(arr, "TEST", &errors);
    DinamicArray* result = map(arr, string_to_lower, get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 3);
    
    char* val0 = (char*)get(result, 0, &errors);
    char* val1 = (char*)get(result, 1, &errors);
    char* val2 = (char*)get(result, 2, &errors);
    assert(strcmp(val0, "hello") == 0);
    assert(strcmp(val1, "world") == 0);
    assert(strcmp(val2, "test") == 0);
}

TEST(map_func_apply_to_8) {
    puts("ТЕСТ 7.3");
    puts("---map: применение функций к числу 8---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    append(arr, inc, &errors);
    append(arr, dec, &errors);
    append(arr, square, &errors);
    assert(errors == ARRAY_OK);
    
    DinamicArray* result = map(arr, func_apply_to_8, get_int_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 3);
    
    int* val0 = (int*)get(result, 0, &errors);
    int* val1 = (int*)get(result, 1, &errors);
    int* val2 = (int*)get(result, 2, &errors);
    
    assert(*val0 == 9);
    assert(*val1 == 7);
    assert(*val2 == 64);
  }

TEST(map_null_array) {
    puts("ТЕСТ 7.4");
    puts("---map: проверка с NULL массивом---");
    AllErrors errors;
    DinamicArray* result = map(NULL, string_to_upper, get_string_type_info(), &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(map_null_transform) {
    puts("ТЕСТ 7.5");
    puts("---map: проверка с NULL transform функцией---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    DinamicArray* result = map(arr, NULL, get_string_type_info(), &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
    
}

TEST(map_null_type) {
    puts("ТЕСТ 7.6");
    puts("---map: проверка с NULL type info---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    
    DinamicArray* result = map(arr, string_to_upper, NULL, &errors);

    assert(errors == NULL_POINTER);
    assert(result == NULL);
    
    destroy_array(arr, &errors);
}


TEST(where_string_length_gt_4) {
    puts("ТЕСТ 8.1");
    puts("---where: фильтрация строк длиной больше 4---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "cat", &errors);
    append(arr, "elephant", &errors);
    append(arr, "dog", &errors);
    append(arr, "butterfly", &errors);
    append(arr, "fox", &errors);
    
    DinamicArray* result = where(arr, string_length_4, &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 2);
    char* val0 = (char*)get(result, 0, &errors);
    char* val1 = (char*)get(result, 1, &errors);
    
    assert(strcmp(val0, "elephant") == 0);
    assert(strcmp(val1, "butterfly") == 0);
    
}

TEST(where_string_contains_y) {
    puts("ТЕСТ 8.2");
    puts("---where: фильтрация строк содержащих 'y'---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "yak", &errors);
    append(arr, "elephant", &errors);
    append(arr, "dog", &errors);
    append(arr, "butterfly", &errors);
    append(arr, "yabby ", &errors);

    DinamicArray* result = where(arr, string_contains_y, &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 3);
    char* val0 = (char*)get(result, 0, &errors);
    char* val1 = (char*)get(result, 1, &errors);
    char* val2 = (char*)get(result, 2, &errors);
    
    assert(strcmp(val0, "yak") == 0);
    assert(strcmp(val1, "butterfly") == 0);
    assert(strcmp(val2, "yabby") == 0);
}

TEST(where_func_even) {
    puts("ТЕСТ 8.3");
    puts("---where: фильтрация функций с четным f(7)---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    append(arr, inc, &errors);
    append(arr, dec, &errors);
    append(arr, square, &errors);

    DinamicArray* result = where(arr, func_even, &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 2);
    IntFunc f0 = (IntFunc)get(result, 0, &errors);
    IntFunc f1 = (IntFunc)get(result, 1, &errors);
    
    assert(f0(5) == 6);
    assert(f1(5) == 4);
    
    destroy_array(arr, &errors);
    destroy_array(result, &errors);
}

TEST(where_func_greater_than_10) {
    puts("ТЕСТ 8.4");
    puts("---where: фильтрация функций с f(7) > 10---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    append(arr, inc, &errors);
    append(arr, dec, &errors);
    append(arr, square, &errors);
    
    DinamicArray* result = where(arr, func_greater_than_10, &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 1);
    
    IntFunc f0 = (IntFunc)get(result, 0, &errors);
    assert(f0(5) == 25);
}

TEST(where_empty_result) {
    puts("ТЕСТ 8.5");
    puts("---where: пустой результат фильтрации---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "cat", &errors);
    append(arr, "dog", &errors);
    append(arr, "fox", &errors);

    DinamicArray* result = where(arr, string_length_4, &errors);
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(result->size == 0);
    char* str = array_to_string(result, &errors);
    assert(strcmp(str, "[]") == 0);
}

TEST(where_null_array) {
    puts("ТЕСТ 8.6");
    puts("---where: проверка с NULL массивом---");
    AllErrors errors;
    
    DinamicArray* result = where(NULL, string_length_4, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(where_null_predicate) {
    puts("ТЕСТ 8.7");
    puts("---where: проверка с NULL predicate функцией---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    
    DinamicArray* result = where(arr, NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}