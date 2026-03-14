#include "test.h"

extern int current_arg;

TEST(inc_function) {
    puts("ТЕСТ 14.1");
    puts("---inc: функция инкремента---");
    
    assert(inc(0) == 1);
    assert(inc(5) == 6);
    assert(inc(-5) == -4);
    assert(inc(100) == 101);
}

TEST(dec_function) {
    puts("ТЕСТ 14.2");
    puts("---dec: функция декремента---");
    
    assert(dec(0) == -1);
    assert(dec(5) == 4);
    assert(dec(-5) == -6);
    assert(dec(100) == 99);
}

TEST(square_function) {
    puts("ТЕСТ 14.3");
    puts("---square: функция возведения в квадрат---");
    
    assert(square(0) == 0);
    assert(square(5) == 25);
    assert(square(-5) == 25);
    assert(square(10) == 100);
    assert(square(2) == 4);
}

TEST(string_to_upper_valid) {
    puts("ТЕСТ 15.1");
    puts("---string_to_upper: преобразование в верхний регистр---");
    AllErrors errors;
    const char* input = "hello";
    char* output;
    
    string_to_upper(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "HELLO") == 0);
}

TEST(string_to_upper_mixed_case) {
    puts("ТЕСТ 15.2");
    puts("---string_to_upper: смешанный регистр---");
    AllErrors errors;
    const char* input = "HeLlO wOrLd";
    char* output;
    
    string_to_upper(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "HELLO WORLD") == 0);
}

TEST(string_to_upper_empty) {
    puts("ТЕСТ 15.3");
    puts("---string_to_upper: пустая строка---");
    AllErrors errors;
    const char* input = "";
    char* output;
    
    string_to_upper(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "") == 0);
}

TEST(string_to_upper_numbers) {
    puts("ТЕСТ 15.4");
    puts("---string_to_upper: строка с цифрами---");
    AllErrors errors;
    const char* input = "hello123";
    char* output;
    
    string_to_upper(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "HELLO123") == 0);
}

TEST(string_to_upper_null) {
    puts("ТЕСТ 15.5");
    puts("---string_to_upper: NULL указатель---");
    AllErrors errors;
    char* output;

    string_to_upper(NULL, &output, &errors);
    
    assert(errors == NULL_POINTER);
}

TEST(string_to_lower_valid) {
    puts("ТЕСТ 16.1");
    puts("---string_to_lower: преобразование в нижний регистр---");
    AllErrors errors;
    const char* input = "HELLO";
    char* output;
    
    string_to_lower(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "hello") == 0);

}

TEST(string_to_lower_mixed_case) {
    puts("ТЕСТ 16.2");
    puts("---string_to_lower: смешанный регистр---");
    AllErrors errors;
    const char* input = "HeLlO WoRlD";
    char* output;
    
    string_to_lower(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "hello world") == 0);
}

TEST(string_to_lower_empty) {
    puts("ТЕСТ 16.3");
    puts("---string_to_lower: пустая строка---");
    AllErrors errors;
    const char* input = "";
    char* output;
    
    string_to_lower(input, &output, &errors);
    
    assert(errors == ARRAY_OK);
    assert(output != NULL);
    assert(strcmp(output, "") == 0);
}

TEST(string_to_lower_null) {
    puts("ТЕСТ 16.4");
    puts("---string_to_lower: NULL указатель---");
    AllErrors errors;
    char* output;

    string_to_lower(NULL, &output, &errors);
    
    assert(errors == NULL_POINTER);
}

TEST(string_length_4_valid) {
    puts("ТЕСТ 17.1");
    puts("---string_length_4: проверка длины > 4---");
    AllErrors errors;
    
    int result1 = string_length_4("cat", &errors); 
    int result2 = string_length_4("elephant", &errors);
    int result3 = string_length_4("dog", &errors);
    int result4 = string_length_4("butterfly", &errors);
    
    assert(errors == ARRAY_OK);
    assert(result1 == 0);
    assert(result2 == 1);
    assert(result3 == 0);
    assert(result4 == 1);
}

TEST(string_length_4_boundary) {
    puts("ТЕСТ 17.2");
    puts("---string_length_4: граничные значения---");
    AllErrors errors;
    
    int result1 = string_length_4("four", &errors);
    int result2 = string_length_4("five", &errors);
    int result3 = string_length_4("six!", &errors);
    
    assert(errors == ARRAY_OK);
    assert(result1 == 0); 
    assert(result2 == 0);
    assert(result3 == 0);
}

TEST(string_length_4_null) {
    puts("ТЕСТ 17.3");
    puts("---string_length_4: NULL указатель---");
    AllErrors errors;
    
    int result = string_length_4(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == 0);
}

TEST(string_contains_y_valid) {
    puts("ТЕСТ 18.1");
    puts("---string_contains_y: проверка наличия 'y'---");
    AllErrors errors;
    
    int result1 = string_contains_y("sky", &errors);
    int result2 = string_contains_y("cat", &errors);
    int result3 = string_contains_y("YELLOW", &errors);
    int result4 = string_contains_y("python", &errors);
    
    assert(errors == ARRAY_OK);
    assert(result1 == 1);
    assert(result2 == 0);
    assert(result3 == 1);
    assert(result4 == 1);
}

TEST(string_contains_y_empty) {
    puts("ТЕСТ 18.2");
    puts("---string_contains_y: пустая строка---");
    AllErrors errors;
    
    int result = string_contains_y("", &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 0);
}

TEST(string_contains_y_null) {
    puts("ТЕСТ 18.3");
    puts("---string_contains_y: NULL указатель---");
    AllErrors errors;
    
    int result = string_contains_y(NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == 0);
}

TEST(string_concat_op_valid) {
    puts("ТЕСТ 19.1");
    puts("---string_concat_op: конкатенация двух строк---");
    AllErrors errors;
    const char* s1 = "Hello";
    const char* s2 = "World";
    
    char* result = (char*)string_concat_op(s1, s2, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "HelloWorld") == 0);
}

TEST(string_concat_op_with_space) {
    puts("ТЕСТ 19.2");
    puts("---string_concat_op: конкатенация с пробелом---");
    AllErrors errors;
    const char* s1 = "Hello ";
    const char* s2 = "World";
    
    char* result = (char*)string_concat_op(s1, s2, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "Hello World") == 0);
}

TEST(string_concat_op_empty_first) {
    puts("ТЕСТ 19.3");
    puts("---string_concat_op: первая строка пустая---");
    AllErrors errors;
    const char* empty = "";
    const char* s = "Hello";
    
    char* result = (char*)string_concat_op(empty, s, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
}

TEST(string_concat_op_empty_second) {
    puts("ТЕСТ 19.4");
    puts("---string_concat_op: вторая строка пустая---");
    AllErrors errors;
    const char* s = "Hello";
    const char* empty = "";
    
    char* result = (char*)string_concat_op(s, empty, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
}

TEST(string_concat_op_null_first) {
    puts("ТЕСТ 19.5");
    puts("---string_concat_op: первый аргумент NULL---");
    AllErrors errors;
    const char* s = "Hello";
    
    char* result = (char*)string_concat_op(NULL, s, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(string_concat_op_null_second) {
    puts("ТЕСТ 19.6");
    puts("---string_concat_op: второй аргумент NULL---");
    AllErrors errors;
    const char* s = "Hello";
    
    char* result = (char*)string_concat_op(s, NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(string_concat_op_both_null) {
    puts("ТЕСТ 19.7");
    puts("---string_concat_op: оба аргумента NULL---");
    AllErrors errors;
    
    char* result = (char*)string_concat_op(NULL, NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(func_apply_to_arg_inc) {
    puts("ТЕСТ 21.1");
    puts("---func_apply_to_arg: применение inc к аргументу---");
    AllErrors errors;
    current_arg = 10;
    int result;
    
    func_apply_to_arg(inc, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 11);
}

TEST(func_apply_to_arg_dec) {
    puts("ТЕСТ 21.2");
    puts("---func_apply_to_arg: применение dec к аргументу---");
    AllErrors errors;
    current_arg = 10;
    int result;
    
    func_apply_to_arg(dec, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 9);
}

TEST(func_apply_to_arg_square) {
    puts("ТЕСТ 21.3");
    puts("---func_apply_to_arg: применение square к аргументу---");
    AllErrors errors;
    current_arg = 10;
    int result;
    
    func_apply_to_arg(square, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 100);
}
TEST(func_apply_to_arg_negative_inc) {
    puts("ТЕСТ 21.4");
    puts("---func_apply_to_arg: отрицательный аргумент с inc---");
    AllErrors errors;
    current_arg = -5;
    int result;
    
    func_apply_to_arg(inc, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == -4);
}

TEST(func_apply_to_arg_negative_dec) {
    puts("ТЕСТ 21.5");
    puts("---func_apply_to_arg: отрицательный аргумент с dec---");
    AllErrors errors;
    current_arg = -5;
    int result;
    
    func_apply_to_arg(dec, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == -6);
}

TEST(func_apply_to_arg_negative_square) {
    puts("ТЕСТ 21.6");
    puts("---func_apply_to_arg: отрицательный аргумент с square---");
    AllErrors errors;
    current_arg = -5;
    int result;
    
    func_apply_to_arg(square, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 25);
}

TEST(func_apply_to_arg_zero_inc) {
    puts("ТЕСТ 21.7");
    puts("---func_apply_to_arg: нулевой аргумент с inc---");
    AllErrors errors;
    current_arg = 0;
    int result;
    
    func_apply_to_arg(inc, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 1);
}

TEST(func_apply_to_arg_zero_dec) {
    puts("ТЕСТ 21.8");
    puts("---func_apply_to_arg: нулевой аргумент с dec---");
    AllErrors errors;
    current_arg = 0;
    int result;
    
    func_apply_to_arg(dec, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == -1);
}

TEST(func_apply_to_arg_zero_square) {
    puts("ТЕСТ 21.9");
    puts("---func_apply_to_arg: нулевой аргумент с square---");
    AllErrors errors;
    current_arg = 0;
    int result;
    
    func_apply_to_arg(square, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 0);
}

TEST(func_apply_to_arg_large_inc) {
    puts("ТЕСТ 21.10");
    puts("---func_apply_to_arg: большой аргумент с inc---");
    AllErrors errors;
    
    current_arg = 10000;
    int result;
    
    func_apply_to_arg(inc, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 10001);
}

TEST(func_apply_to_arg_large_dec) {
    puts("ТЕСТ 21.11");
    puts("---func_apply_to_arg: большой аргумент с dec---");
    AllErrors errors;
    
    current_arg = 10000;
    int result;
    
    func_apply_to_arg(dec, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 9999);
}

TEST(func_apply_to_arg_large_square) {
    puts("ТЕСТ 21.12");
    puts("---func_apply_to_arg: большой аргумент с square---");
    AllErrors errors;
    current_arg = 1000;
    int result;
    
    func_apply_to_arg(square, &result, &errors);
    
    assert(errors == ARRAY_OK);
    assert(result == 1000000);
}
TEST(func_apply_to_arg_null) {
    puts("ТЕСТ 21.13");
    puts("---func_apply_to_arg: NULL функция---");
    AllErrors errors;
    current_arg = 10;
    int result;
    
    func_apply_to_arg(NULL, &result, &errors);
    
    assert(errors == NULL_POINTER);
}