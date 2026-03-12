#include <test.h>

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