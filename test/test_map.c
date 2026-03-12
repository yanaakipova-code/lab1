#include <test.h>

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