#include "test.h"

TEST(string_clone_valid) {
    puts("ТЕСТ 13.1");
    puts("---string_clone: клонирование строки---");
    AllErrors errors;
    const char* original = "Hello, World!";

    char* clone = (char*)string_clone(original, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone != NULL);
    assert(strcmp(clone, original) == 0);
    assert(clone != original);
}

TEST(string_clone_empty) {
    puts("ТЕСТ 13.2");
    puts("---string_clone: клонирование пустой строки---");
    AllErrors errors;
    const char* original = "";

    char* clone = (char*)string_clone(original, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone != NULL);
    assert(strcmp(clone, "") == 0);
    assert(strlen(clone) == 0);
}

TEST(string_clone_null) {
    puts("ТЕСТ 13.3");
    puts("---string_clone: клонирование NULL---");
    AllErrors errors;
    
    char* clone = (char*)string_clone(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(clone == NULL);
}

TEST(string_clone_long_string) {
    puts("ТЕСТ 13.4");
    puts("---string_clone: клонирование длинной строки---");
    AllErrors errors;
    const char* original = "This is a very long line i don't know what else to write hello world this is my program";
    
    char* clone = (char*)string_clone(original, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone != NULL);
    assert(strcmp(clone, original) == 0);
    assert(strlen(clone) == strlen(original));
}

TEST(string_free_valid) {
    puts("ТЕСТ 13.5");
    puts("---string_free: освобождение памяти строки---");
    AllErrors errors;
    char* str = (char*)malloc(10);
    strcpy(str, "test");
    
    string_free(str, &errors);
    
    assert(errors == ARRAY_OK);
}

TEST(string_free_null) {
    puts("ТЕСТ 13.6");
    puts("---string_free: освобождение NULL---");
    AllErrors errors;
    
    string_free(NULL, &errors);
    
    assert(errors == NULL_POINTER);
}

TEST(string_to_string_valid) {
    puts("ТЕСТ 13.7");
    puts("---string_to_string: преобразование строки в строку с кавычками---");
    AllErrors errors;
    const char* str = "hello";

    char* result = string_to_string(str, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "\"hello\"") == 0);
}

TEST(string_to_string_empty) {
    puts("ТЕСТ 13.8");
    puts("---string_to_string: преобразование пустой строки---");
    AllErrors errors;
    const char* str = "";

    char* result = string_to_string(str, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "\"\"") == 0);
}

TEST(string_to_string_with_spaces) {
    puts("ТЕСТ 13.9");
    puts("---string_to_string: строка с пробелами---");
    AllErrors errors;
    const char* str = "hello world";

    char* result = string_to_string(str, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "\"hello world\"") == 0);
}

TEST(string_to_string_special_chars) {
    puts("ТЕСТ 13.10");
    puts("---string_to_string: строка с непонятными значками---");
    AllErrors errors;
    const char* str = "!@#$%^&*()";

    char* result = string_to_string(str, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "\"!@#$%^&*()\"") == 0);
    
    free(result);
}

TEST(string_to_string_null) {
    puts("ТЕСТ 13.11");
    puts("---string_to_string: преобразование NULL---");
    AllErrors errors;
    
    char* result = string_to_string(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(get_string_type_info) {
    puts("ТЕСТ 13.12");
    puts("---get_string_type_info: получение информации о типе строки---");
    
    TypeInfo* info = get_string_type_info();
    
    assert(info != NULL);
    assert(info->elem_size != NULL);
    assert(info->clone == string_clone);
    assert(info->free == string_free);
    assert(info->to_string == string_to_string);
    
    size_t size = info->elem_size();
    assert(size == sizeof(char*));
}

TEST(get_string_type_info_singleton) {
    puts("ТЕСТ 13.13");
    puts("---get_string_type_info: проверка единственого экземпляра---");
    
    TypeInfo* info1 = get_string_type_info();
    TypeInfo* info2 = get_string_type_info();
    
    assert(info1 == info2);
}