#include "test.h"

TEST(func_clone_valid) {
    puts("ТЕСТ 11.1");
    puts("---func_clone: клонирование указателя на функцию---");
    AllErrors errors;
    int (*test_func)(int) = inc;

    void* clone = func_clone(test_func, &errors);
    
    assert(errors == ARRAY_OK);
    assert(clone == test_func);
}

TEST(func_clone_null) {
    puts("ТЕСТ 11.2");
    puts("---func_clone: клонирование NULL указателя---");
    AllErrors errors;
    
    void* clone = func_clone(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(clone == NULL);
}

TEST(func_free) {
    puts("ТЕСТ 11.3");
    puts("---func_free: освобождение функции---");
    AllErrors errors;
    int x = 42;

    func_free(&x, &errors);
    
    assert(errors == ACTION_UNDEFINED);
}

TEST(func_to_string_valid) {
    puts("ТЕСТ 11.4");
    puts("---func_to_string: преобразование функции в строку---");
    AllErrors errors;
    int (*test_func)(int) = square;

    char* str = func_to_string(test_func, &errors);
    
    assert(errors == ARRAY_OK);
    assert(str != NULL);
}

TEST(func_to_string_null) {
    puts("ТЕСТ 11.5");
    puts("---func_to_string: c NULL---");
    AllErrors errors;
    char* str = func_to_string(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(str == NULL);
}

TEST(get_func_type_info) {
    puts("ТЕСТ 11.6");
    puts("---get_func_type_info: получение информации о типе функции---");

    TypeInfo* info = get_func_type_info();
    size_t size = info->elem_size();

    assert(info != NULL);
    assert(info->elem_size != NULL);
    assert(info->clone == func_clone);
    assert(info->free == func_free);
    assert(info->to_string == func_to_string);
    assert(size == sizeof(int));
}

TEST(get_func_type_info_singleton) {
    puts("ТЕСТ 11.7");
    puts("---get_func_type_info: проверка единственого экземпляра---");
    
    TypeInfo* info1 = get_func_type_info();
    TypeInfo* info2 = get_func_type_info();
    
    assert(info1 == info2);
}
