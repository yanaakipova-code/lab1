#include "main_basic.h" 
#include "DynamicArray.h"
#include "StringType.h"
#include "FuncType.h"
#include "IntType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"

unsigned int total_tests = 0;
unsigned int passed_tests = 0;
unsigned int failed_tests = 0;

static int current_arg = 0;

void print_test_result(const char* test_name, int passed) {
    printf("%s: ", test_name);
    if (passed) {
        printf(COLOR_GREEN "Успешно" COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "Провалено" COLOR_RESET "\n");
    }
}

void print_test_summary() {
    puts("-------------------------------------------------");
    printf("Bceго тестов: %d\n", total_tests);
    printf(COLOR_GREEN "Успешно: %d\n" COLOR_RESET, passed_tests);
    printf(COLOR_RED "Провалено: %d\n" COLOR_RESET, failed_tests);
    puts("-------------------------------------------------");
}

void test_create_array() {
    puts("--- тест для функции create_array ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    
    total_tests++;
    DinamicArray* arr = create_array(string_type, &error);
    print_test_result("Create array - успешно", arr != NULL && error == ARRAY_OK);
    if (arr != NULL && error == ARRAY_OK) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    if (arr) destroy_array(arr, NULL);
    
    total_tests++;
    arr = create_array(NULL, &error);
    print_test_result("Create array с NULL type", arr == NULL && error == NULL_POINTER);
    if (arr == NULL && error == NULL_POINTER) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
}

void test_append() {
    puts("--- тест для функции append ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    total_tests++;
    append(arr, "Hello", &error);
    append(arr, "World", &error);
    print_test_result("Append несколько элементов", error == ARRAY_OK && arr->size == 2);
    if (error == ARRAY_OK && arr->size == 2) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    int old_size = arr->size;
    append(arr, NULL, &error);
    print_test_result("Append c NULL элементом", error == NULL_POINTER && arr->size == old_size);
    if (error == NULL_POINTER && arr->size == old_size) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    append(NULL, "Test", &error);
    print_test_result("Append c NULL массивом", error == NULL_POINTER);
    if (error == NULL_POINTER) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_get() {
    puts("--- тест для функции get ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    append(arr, "Первый", &error);
    append(arr, "Второй", &error);
    append(arr, "Третий", &error);
    
    total_tests++;
    void* elem = get(arr, 1, &error);
    print_test_result("Get по существующему индексу", elem != NULL && error == ARRAY_OK);
    if (elem != NULL && error == ARRAY_OK) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    elem = get(arr, -1, &error);
    print_test_result("Get c отрицательным индексом", elem == NULL && error == INDEX_OUT);
    if (elem == NULL && error == INDEX_OUT) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    elem = get(arr, 10, &error);
    print_test_result("Get c индексом больше размера", elem == NULL && error == INDEX_OUT);
    if (elem == NULL && error == INDEX_OUT) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    elem = get(NULL, 0, &error);
    print_test_result("Get c NULL массивом", elem == NULL && error == NULL_POINTER);
    if (elem == NULL && error == NULL_POINTER) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_get_size() {
    puts("--- тест для функции get_size ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    total_tests++;
    int size = get_size(arr, &error);
    print_test_result("Get size для пустого массива", size == 0 && error == ARRAY_OK);
    if (size == 0 && error == ARRAY_OK) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    append(arr, "Элемент", &error);
    total_tests++;
    size = get_size(arr, &error);
    print_test_result("Get size после добавления", size == 1 && error == ARRAY_OK);
    if (size == 1 && error == ARRAY_OK) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    size = get_size(NULL, &error);
    print_test_result("Get size c NULL массивом", size == -1 && error == NULL_POINTER);
    if (size == -1 && error == NULL_POINTER) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_add_to_array() {
    puts("--- тест для функции add_to_array ---");
    
    AllErrors error;
    TypeInfo* int_type = GetIntTypeInfo();
    DinamicArray* arr = create_array(int_type, &error);
    
    int* val1 = malloc(sizeof(int));
    *val1 = 42;
    
    total_tests++;
    add_to_array(arr, val1, &error);
    print_test_result("Add to array - успешно", error == ARRAY_OK && arr->size == 1);
    if (error == ARRAY_OK && arr->size == 1) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    int old_size = arr->size;
    add_to_array(arr, NULL, &error);
    print_test_result("Add to array c NULL элементом", error == NULL_POINTER && arr->size == old_size);
    if (error == NULL_POINTER && arr->size == old_size) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    add_to_array(NULL, val1, &error);
    print_test_result("Add to array c NULL массивом", error == NULL_POINTER);
    if (error == NULL_POINTER) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_array_to_string() {
    puts("--- тест для функции array_to_string ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    total_tests++;
    char* str = array_to_string(arr, &error);
    print_test_result("Array to string для пустого массива", str != NULL && strcmp(str, "[]") == 0);
    if (str != NULL && strcmp(str, "[]") == 0) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    free(str);
    
    append(arr, "Hello", &error);
    append(arr, "World", &error);
    
    total_tests++;
    str = array_to_string(arr, &error);
    print_test_result("Array to string c элементами", str != NULL && strstr(str, "Hello") != NULL);
    if (str != NULL && strstr(str, "Hello") != NULL) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    free(str);
    
    total_tests++;
    str = array_to_string(NULL, &error);
    print_test_result("Array to string c NULL массивом", str == NULL && error == NULL_POINTER);
    if (str == NULL && error == NULL_POINTER) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_destroy_array() {
    puts("--- тест для функции destroy_array ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    total_tests++;
    DinamicArray* arr = create_array(string_type, &error);
    if (arr) {
        destroy_array(arr, &error);
        print_test_result("Destroy array - успешно", error == ARRAY_OK);
        if (error == ARRAY_OK) {
            passed_tests++;
        } else {
            failed_tests++;
        }
    } else {
        print_test_result("Destroy array - успешно", 0);
        failed_tests++;
    }
    total_tests++;
    error = ARRAY_OK;
    destroy_array(NULL, &error);
    print_test_result("Destroy array с NULL массивом", error == NULL_POINTER);
    if (error == NULL_POINTER) {
        passed_tests++;
    } else {
        failed_tests++;
    }
}

void test_increasing_size() {
    puts("--- тест для увеличения размера массива ---");
    
    AllErrors error;
    TypeInfo* int_type = GetIntTypeInfo();
    DinamicArray* arr = create_array(int_type, &error);
    
    if (!arr) {
        print_test_result("Добавление 20 элементов", 0);
        failed_tests++;
        print_test_result("Capacity увеличилась", 0);
        failed_tests++;
        return;
    }
    
    unsigned int initial_capacity = arr->capacity;
    
    total_tests++;
    int success = 1;
    for (int i = 0; i < 20; i++) {
        int* val = malloc(sizeof(int));
        if (!val) {
            success = 0;
            break;
        }
        *val = i;
        add_to_array(arr, val, &error);
        if (error != ARRAY_OK) {
            free(val);
            success = 0;
            break;
        }
    }
    print_test_result("Добавление 20 элементов", success && arr->size == 20);
    if (success && arr->size == 20) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    total_tests++;
    print_test_result("Capacity увеличилась", arr->capacity > initial_capacity);
    if (arr->capacity > initial_capacity) {
        passed_tests++; 
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_string_functions() {
    puts("--- тест для функций работы со строками ---");
    
    AllErrors error;
    
    total_tests++;
    char* upper = (char*)string_to_upper("hello", &error);
    print_test_result("string_to_upper", upper != NULL && strcmp(upper, "HELLO") == 0);
    if (upper != NULL && strcmp(upper, "HELLO") == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    free(upper);
    
    total_tests++;
    char* lower = (char*)string_to_lower("HELLO", &error);
    print_test_result("string_to_lower", lower != NULL && strcmp(lower, "hello") == 0);
    if (lower != NULL && strcmp(lower, "hello") == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    free(lower);
    
    total_tests++;
    int len_result = string_length_4("hello", &error);
    print_test_result("string_length_4 (hello > 4)", len_result == 1);
    if (len_result == 1) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    len_result = string_length_4("hi", &error);
    print_test_result("string_length_4 (hi <= 4)", len_result == 0);
    if (len_result == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    int contains_result = string_contains_y("yana", &error);
    print_test_result("string_contains_y (yana содержит y)", contains_result == 1);
    if (contains_result == 1) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    contains_result = string_contains_y("hello", &error);
    print_test_result("string_contains_y (hello не содержит y)", contains_result == 0);
    if (contains_result == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    char* concat = (char*)string_concat_op("hello", "world", &error);
    print_test_result("string_concat_op", concat != NULL && strcmp(concat, "helloworld") == 0);
    if (concat != NULL && strcmp(concat, "helloworld") == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    free(concat);
}

void test_func_functions() {
    puts("--- тест для функций работы с функциями ---");
    
    AllErrors error;
    
    total_tests++;
    int* res1 = (int*)func_apply_to_8_wrapper(inc, &error);
    print_test_result("func_apply_to_8_wrapper (inc)", res1 != NULL && *res1 == 9);
    if (res1 != NULL && *res1 == 9) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    free(res1);
    
    total_tests++;
    int* res2 = (int*)func_apply_to_8_wrapper(square, &error);
    print_test_result("func_apply_to_8_wrapper (square)", res2 != NULL && *res2 == 64);
    if (res2 != NULL && *res2 == 64) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    free(res2);
    
    current_arg = 10;
    total_tests++;
    int* res3 = (int*)func_apply_to_arg_wrapper(inc, &error);
    print_test_result("func_apply_to_arg_wrapper (inc, arg=10)", res3 != NULL && *res3 == 11);
    if (res3 != NULL && *res3 == 11) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    free(res3);
    
    total_tests++;
    int even_result = func_even_wrapper(inc, &error);
    print_test_result("func_even_wrapper (inc)", even_result == 1);
    if (even_result == 1) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    even_result = func_even_wrapper(square, &error);
    print_test_result("func_even_wrapper (square)", even_result == 0);
    if (even_result == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    int greater_result = func_greater_than_10_wrapper(square, &error);
    print_test_result("func_greater_than_10_wrapper (square)", greater_result == 1);
    if (greater_result == 1) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    total_tests++;
    greater_result = func_greater_than_10_wrapper(inc, &error);
    print_test_result("func_greater_than_10_wrapper (inc)", greater_result == 0);
    if (greater_result == 0) {
        passed_tests++;
    } else {
        failed_tests++;
    }
}

void test_map_string() {
    puts("--- тест для функции map со строками ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    append(arr, "hello", &error);
    append(arr, "world", &error);
    
    total_tests++;
    DinamicArray* result = map(arr, string_to_upper, string_type, &error);
    print_test_result("Map с string_to_upper", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        char* elem = (char*)get(result, 0, &error);
        total_tests++;
        print_test_result("Map преобразовал hello в HELLO", elem != NULL && strcmp(elem, "HELLO") == 0);
        if (elem != NULL && strcmp(elem, "HELLO") == 0) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        destroy_array(result, NULL);
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_map_func() {
    puts("--- тест для функции map с функциями ---");
    
    AllErrors error;
    TypeInfo* func_type = GetFuncTypeInfo();
    TypeInfo* int_type = GetIntTypeInfo();
    DinamicArray* arr = create_array(func_type, &error);
    
    append(arr, inc, &error);
    append(arr, square, &error);
    
    total_tests++;
    DinamicArray* result = map(arr, func_apply_to_8_wrapper, int_type, &error);
    print_test_result("Map с func_apply_to_8_wrapper", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        int* val = (int*)get(result, 0, &error);
        total_tests++;
        print_test_result("inc(8) = 9", val != NULL && *val == 9);
        if (val != NULL && *val == 9) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        val = (int*)get(result, 1, &error);
        total_tests++;
        print_test_result("square(8) = 64", val != NULL && *val == 64);
        if (val != NULL && *val == 64) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        destroy_array(result, NULL);
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_where_string() {
    puts("--- тест для функции where со строками ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    append(arr, "hello", &error);
    append(arr, "world", &error);
    append(arr, "hi", &error);
    append(arr, "yes", &error);
    
    total_tests++;
    DinamicArray* result = where(arr, string_length_4, &error);
    print_test_result("Where с фильтром длины > 4", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        total_tests++;
        print_test_result("Where отфильтровал строки", result->size == 2);
        if (result->size == 2) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        destroy_array(result, NULL);
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_where_func() {
    puts("--- тест для функции where с функциями ---");
    
    AllErrors error;
    TypeInfo* func_type = GetFuncTypeInfo();
    DinamicArray* arr = create_array(func_type, &error);
    
    append(arr, inc, &error);
    append(arr, dec, &error);
    append(arr, square, &error);
    
    total_tests++;
    DinamicArray* result = where(arr, func_even_wrapper, &error);
    print_test_result("Where с фильтром четности", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        total_tests++;
        print_test_result("Where отфильтровал функции (четные)", result->size == 2);
        if (result->size == 2) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        destroy_array(result, NULL);
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_reduce_string() {
    puts("--- тест для функции reduce со строками ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    DinamicArray* arr = create_array(string_type, &error);
    
    append(arr, "Hello", &error);
    append(arr, " ", &error);
    append(arr, "World", &error);
    
    char* init = "";
    total_tests++;
    void* result = reduce(arr, string_concat_op, init, &error);
    print_test_result("Reduce с конкатенацией строк", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        char* str_result = (char*)result;
        total_tests++;
        print_test_result("Reduce соединил строки", strcmp(str_result, "Hello World") == 0);
        if (strcmp(str_result, "Hello World") == 0) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        free(result);
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_reduce_func() {
    puts("--- тест для функции reduce с функциями ---");
    
    AllErrors error;
    TypeInfo* func_type = GetFuncTypeInfo();
    DinamicArray* arr = create_array(func_type, &error);
    
    append(arr, inc, &error);
    append(arr, square, &error);
    append(arr, dec, &error);
    
    void* init = get(arr, 0, &error);
    total_tests++;
    void* result = reduce(arr, func_compose_op, init, &error);
    print_test_result("Reduce с композицией функций", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        int test_val = ((IntFunc)result)(7);
        total_tests++;
        print_test_result("Композиция работает", test_val == 6);
        if (test_val == 6) {
            passed_tests++;
        } else {
            failed_tests++;
        }
    } else {
        failed_tests++;
    }
    
    destroy_array(arr, NULL);
}

void test_concatenation() {
    puts("--- тест для функции concatenation ---");
    
    AllErrors error;
    TypeInfo* string_type = GetStringTypeInfo();
    
    DinamicArray* arr1 = create_array(string_type, &error);
    DinamicArray* arr2 = create_array(string_type, &error);
    
    append(arr1, "Hello", &error);
    append(arr1, "World", &error);
    append(arr2, "Test", &error);
    append(arr2, "Array", &error);
    
    total_tests++;
    DinamicArray* result = concatenation(arr1, arr2, &error);
    print_test_result("Concatenation двух массивов", result != NULL && error == ARRAY_OK);
    if (result != NULL && error == ARRAY_OK) {
        passed_tests++;
        
        total_tests++;
        print_test_result("Concatenation правильный размер", result->size == 4);
        if (result->size == 4) {
            passed_tests++;
        } else {
            failed_tests++;
        }
        
        destroy_array(result, NULL);
    } else {
        failed_tests++;
    }
    
    total_tests++;
    result = concatenation(NULL, arr2, &error);
    print_test_result("Concatenation с NULL первым массивом", result == NULL && error == NULL_POINTER);
    if (result == NULL && error == NULL_POINTER) {
        passed_tests++;
    } else {
        failed_tests++;
    }
    
    destroy_array(arr1, NULL);
    destroy_array(arr2, NULL);
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);  // УБРАТЬ &
    #endif
    
    puts("--------------------------------------------");
    puts("ТЕСТИРОВАНИЕ DYNAMIC ARRAY");
    puts("--------------------------------------------");
    
    test_create_array();
    test_append();
    test_get();
    test_get_size();
    test_add_to_array();
    test_array_to_string();
    test_destroy_array();
    test_increasing_size();
    test_string_functions();
    test_func_functions();
    test_map_string();
    test_map_func();
    test_where_string();
    test_where_func();
    test_reduce_string();
    test_reduce_func();
    test_concatenation();
    
    print_test_summary();
    
    FreeStringTypeInfo();
    FreeFuncTypeInfo();
    FreeIntTypeInfo();
    
    if (failed_tests == 0) {
        return 0;
    } else {
        return 1;
    }
}