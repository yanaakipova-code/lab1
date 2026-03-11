#include "main_basic.h" 
#include "DynamicArray.h"
#include "DynamicArray.c"
#include "StringType.h"
#include "FuncType.h"
#include "IntType.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void print_test_res(const char *test_name, unsigned int condition){
    if (condition){
        printf("тест функции %s прошел успешно\n", test_name);
    } else {
        printf("тест функции %s провален\n", test_name);
    }
}


void test_create_array_string(){
    puts("ТЕСТ 1");
    puts("---Создание массива строк---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == ZERO_SIZE);
    assert(arr->capacity == INITIAL_CAPACITY);

    print_test_res("test_create_array_string", 1);
}

void test_create_array_func(){ 
    puts("ТЕСТ 2");
    puts("---Создание массива функций---");
    AllErrors errors;
   
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == ZERO_SIZE);
    assert(arr->capacity == INITIAL_CAPACITY);

    print_test_res("test_create_array_func", 1);
}

void test_create_array(){
    puts("ТЕСТ 3");
    puts("---Пограничное значение функции создания массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(NULL, &errors);
    assert(errors == NULL_POINTER);

    print_test_res("test_create_array", 1);
}

void test_destroy_array_ok(){
    puts("ТЕСТ 4");
    puts("---Разрушение массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    destroy_array(arr, &errors);
    assert(errors == ARRAY_OK);

    print_test_res("test_destroy_array_ok", 1);
}

void test_destroy_array_fl(){
    puts("ТЕСТ 5");
    puts("---Разрушение массива c NULL---");
    AllErrors errors;
    destroy_array(NULL, &errors);
    assert(errors == NULL_POINTER);

    print_test_res("test_destroy_array_fl", 1);
}

void test_increasing_size(){
    puts("ТЕСТ 6");
    puts("---Увеличение/Добавление элемента ёмкости массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    const char* elem ="y";
    unsigned int start_capacity = arr->capacity;
    for (unsigned int i = 0; i < start_capacity; i++){
        append(arr, elem, &errors);
        assert(errors == ARRAY_OK);
    }
    assert(arr->size == start_capacity);
    assert(arr->size == arr->capacity);

    append(arr, elem, &errors);
    assert(errors == ARRAY_OK);
    assert(arr->capacity == start_capacity * RISING_AT_TWO);

    print_test_res("test_increasing_size", 1);
}

void test_increasing_size_fl(){
    puts("ТЕСТ 7");
    puts("---Увеличение ёмкости массива с NULL---");
    AllErrors errors;
    increasing_size(NULL,&errors);
    assert(errors == NULL_POINTER); 

    print_test_res("test_increasing_size_fl", 1);
}

void test_append_fl(){
    puts("ТЕСТ 8");
    puts("---Добавление элемента с NULL---");
    const char elem ="y";
    AllErrors errors;
    append(NULL,elem, &errors);
    assert(errors == NULL_POINTER);
    print_test_res("test_append_fl", 1);
}

void test_get(){
    puts("ТЕСТ 9");
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
    
    puts("---Отрицательный индекс массива---");
    get(arr, -1, &errors);
    assert(errors == INDEX_OUT);

    puts("---Индекс все диапазона---");
    get(arr, 5, &errors);
    assert(errors == INDEX_OUT);

    destroy_array(arr, &errors);
    print_test_res("test_get", 1);
}

void test_get_size(){
    puts("ТЕСТ 10");
    puts("---Получение размера массива---");
    AllErrors errors;
    
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);

    int size = get_size(arr, &errors);
    assert(errors == ARRAY_OK);
    assert(size == 3);
    
    DinamicArray* empty_arr = create_array(get_string_type_info(), &errors);
    size = get_size(empty_arr, &errors);
    assert(errors == ARRAY_OK);
    assert(size == 0);
    
    size = get_size(NULL, &errors);
    assert(errors == NULL_POINTER);
    assert(size == -1);
    
    destroy_array(arr, &errors);
    destroy_array(empty_arr, &errors);
    print_test_res("test_get_size", 1);
}

void test_array_to_string(){
    puts("ТЕСТ 11");
    puts("---Преобразование массива в строку---");
    AllErrors errors;
    
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "hello", &errors);
    append(arr, "world", &errors);
    append(arr, "!", &errors);
    
    char* str = array_to_string(arr, &errors);
    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[\"hello\", \"world\", \"test\"]") == 0);
    free(str);

    DinamicArray* empty_arr = create_array(get_string_type_info(), &errors);
    str = array_to_string(empty_arr, &errors);
    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[]") == 0);
    free(str);

    str = array_to_string(NULL, &errors);
    assert(errors == NULL_POINTER);
    assert(str == NULL);
    
    destroy_array(arr, &errors);
    destroy_array(empty_arr, &errors);
    
    print_test_res("test_array_to_string", 1);
}

void test_array_to_string_int(){
    puts("ТЕСТ 12");
    puts("---Преобразование массива чисел в строку---");
    AllErrors errors;
    
    DinamicArray* arr = create_array(get_int_type_info(), &errors);
    int a = 10, b = 20, c = 30;
    append(arr, &a, &errors);
    append(arr, &b, &errors);
    append(arr, &c, &errors);
    
    char* str = array_to_string(arr, &errors);
    assert(errors == ARRAY_OK);
    assert(strcmp(str, "[10, 20, 30]") == 0);
    free(str);
    
    destroy_array(arr, &errors);
    print_test_res("test_array_to_string_int", 1);
}