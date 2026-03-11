#include "test.h"

TEST(int_clone_valid) {
    puts("ТЕСТ 12.1");
    puts("---int_clone: клонирование целого числа---");
    AllErrors errors;
    unsigned int value = 42;

    int* clone = (int*)int_clone(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone != NULL);
    assert(*clone == 42);
    assert(clone != &value);
}

TEST(int_clone_null) {
    puts("ТЕСТ 12.2");
    puts("---int_clone: клонирование NULL---");
    AllErrors errors;

    int* clone = (int*)int_clone(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(clone == NULL);
}

TEST(int_clone_zero) {
    puts("ТЕСТ 12.3");
    puts("---int_clone: клонирование нуля---");
    AllErrors errors;
    unsigned int value = 0;

    int* clone = (int*)int_clone(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone != NULL);
    assert(*clone == 0);
}

TEST(int_clone_negative) {
    puts("ТЕСТ 12.4");
    puts("---int_clone: клонирование отрицательного числа---");
    AllErrors errors;
    int value = -100;

    int* clone = (int*)int_clone(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone != NULL);
    assert(*clone == -100);
}

TEST(int_free_valid) {
    puts("ТЕСТ 12.5");
    puts("---int_free: освобождение памяти целого числа---");
    AllErrors errors;
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    
    int_free(ptr, &errors);
    
    assert(errors == ARRAY_OK);
}

TEST(int_free_null) {
    puts("ТЕСТ 12.6");
    puts("---int_free: освобождение NULL---");
    AllErrors errors;
    
    int_free(NULL, &errors);
    
    assert(errors == NULL_POINTER);
}

TEST(int_to_string_valid) {
    puts("ТЕСТ 12.7");
    puts("---int_to_string: преобразование числа в строку---");
    AllErrors errors;
    int value = 1234534;

    char* str = int_to_string(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "1234534") == 0);
}

TEST(int_to_string_zero) {
    puts("ТЕСТ 12.8");
    puts("---int_to_string: преобразование нуля---");
    AllErrors errors;
    unsigned int value = 0;

    char* str = int_to_string(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "0") == 0);
}

TEST(int_to_string_negative) {
    puts("ТЕСТ 12.9");
    puts("---int_to_string: преобразование отрицательного числа---");
    AllErrors errors;
    int value = -999;
    char* str = int_to_string(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "-999") == 0);
}

TEST(int_to_string_max) {
    puts("ТЕСТ 12.10");
    puts("---int_to_string: большое значение int---");
    AllErrors errors;
    int value = 2147483647;

    char* str = int_to_string(&value, &errors);
    
    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "2147483647") == 0);
}

TEST(int_to_string_null) {
    puts("ТЕСТ 12.11");
    puts("---int_to_string: преобразование NULL---");
    AllErrors errors;
    
    char* str = int_to_string(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(str == NULL);
}

TEST(get_int_type_info) {
    puts("ТЕСТ 12.12");
    puts("---get_int_type_info: получение информации о типе int---");
    
    TypeInfo* info = get_int_type_info();
    
    assert(info != NULL);
    assert(info->elem_size != NULL);
    assert(info->clone == int_clone);
    assert(info->free == int_free);
    assert(info->to_string == int_to_string);
    
    size_t size = info->elem_size();
    assert(size == sizeof(int));
}

TEST(get_int_type_info_singleton) {
    puts("ТЕСТ 12.13");
    puts("---get_int_type_info: проверка единственого экземпляра---");
    
    TypeInfo* info1 = get_int_type_info();
    TypeInfo* info2 = get_int_type_info();
    
    assert(info1 == info2);
}
