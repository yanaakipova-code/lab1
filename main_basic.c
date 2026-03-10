#include "main_basic.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

DinamicArray* current_array = NULL;
AllErrors last_error;
int current_arg = 0;

void clear_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int inc(int x) {
    return x + 1;
}

int dec(int x) {
    return x - 1;
}

int square(int x) {
    return x * x;
}

void print_error(const char* context){
    printf("Ошибка в %s: ", context);
    switch (last_error){
        case ARRAY_OK: puts("нет ошибки"); break;
        case MEMORY_ALLOCATION_FAILED: puts("не удалось выделить память"); break;
        case NULL_POINTER: puts("нулевой указатель"); break;
        case INDEX_OUT: puts("индекс вне диапазона"); break;
        case DIFFERENT_TYPE: puts("несовместимые типы"); break;
        case ACTION_UNDEFINED: puts("Функция не реализована"); break;
        default: printf("неизвестная ошибка (%d)", last_error);
    }
}

void print_menu(){
    printf("-------------------------------------------------\n");
    puts("1. Создать массив (строки)");  
    puts("2. Создать массив (функции)");
    puts("3. Добавить элемент");
    puts("4. Показать массив");
    puts("5. MAP - применить преобразование");
    puts("6. WHERE - фильтрация");
    puts("7. REDUCE - свертка");
    puts("8. CONCAT - конкатенация");
    printf("Ваш выбор: ");
}

void create_string_array(){
    if (current_array){
        destroy_array(current_array, &last_error);
    }
    
    current_array = create_array(get_string_type_info(), &last_error);
    if (last_error == ARRAY_OK){
        puts("Массив строк создан");
        append(current_array, "hello", &last_error);
        append(current_array, "world", &last_error);
        append(current_array, "this", &last_error);
        append(current_array, "is", &last_error);
        append(current_array, "a", &last_error);
        append(current_array, "test", &last_error);
        append(current_array, "programming", &last_error);
        puts("Добавлены тестовые строки");
    } else{
        print_error("create_string_array");
    }
}

void create_func_array(){
    if (current_array){
        destroy_array(current_array, &last_error);
    }
    
    current_array = create_array(get_func_type_info(), &last_error);
    if (last_error == ARRAY_OK){
        puts("Массив функций создан");
        append(current_array, inc, &last_error);
        append(current_array, dec, &last_error);
        append(current_array, square, &last_error);
        puts("Добавлены тестовые функции");
    } else {
        print_error("create_func_array");
    }
}

void add_element() {
    if (!current_array) {
        puts("Сначала создайте массив");
        return;
    }

    if (current_array->type->clone == string_clone) {
        char buffer[64];
        printf("Введите строку: ");
        if (scanf("%64s", buffer) == 1) {
            clear_input();
            append(current_array, buffer, &last_error);
        } else {
            puts("Ошибка ввода");
            clear_input();
        }       
        
        if (last_error == ARRAY_OK) {
            puts("Строка добавлена");
        } else {
            print_error("add_element");
        }
    }else if (current_array->type->clone == func_clone){
        puts("Выберите функцию:");
        puts("1. inc (+1)");
        puts("2. dec (-1)");
        puts("3. square (x*x)");
        printf("Ваш выбор: ");

        unsigned int choice;
        scanf("%u", &choice);
        clear_input();

        void* func = NULL;
        const char* name = NULL;
        switch (choice){
            case 1: func = inc; name = "inc"; break;
            case 2: func = dec; name = "dec"; break;
            case 3: func = square; name = "square"; break;
            default:
                puts("Неверный выбор");
                return;
            }
            append(current_array, func, &last_error);
            if (last_error == ARRAY_OK){
                printf("Функция %s добавлена\n", name);
            } else {
                print_error("add_element");
            }
    }else {
        puts("Неподдерживаемый тип");
    }
}
            
void show_array(){
    if (!current_array){
        puts("Массив не создан");
        return;
    }
    
    puts("Текущий массив:");
    char* array_str = array_to_string(current_array, &last_error);
    if (last_error == ARRAY_OK && array_str) {
        printf("%s\n", array_str);
        free(array_str);
    } else {
        print_error("show_array");
    }
}

void string_to_upper(const void* src, void* dst, AllErrors* error){
    const char* str = (const char*)src;
    if (!str){
        if (error) *error = NULL_POINTER;
        return;
    }
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return;
    }
    
    for (unsigned int i = 0; i <= strlen(str); i++){
        result[i] = toupper(str[i]);
    }
    *(char**)dst = result;
    if (error) *error = ARRAY_OK;;
}

void string_to_lower(const void* src, void* dst, AllErrors* error) {
    const char* str = (const char*)src;
    if (!str) {
        if (error) *error = NULL_POINTER;
        return;
    }
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return;
    }
    
    for (unsigned int i = 0; i <= strlen(str); i++) {
        result[i] = tolower(str[i]);
    }
    *(char**)dst = result;
    if (error) *error = ARRAY_OK;
}

int string_length_4(const void * elem, AllErrors* error) {
    if (!elem){
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    const char* str = (const char*)elem;
    if (error) *error = ARRAY_OK;
    
    if(strlen(str) > 4){
        return 1;
    }else return 0;
}

int string_contains_y(const void* elem, AllErrors* error) {
    if (!elem) {
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    const char* str = (const char*)elem;
    if (error) *error = ARRAY_OK;
    if (strchr(str, 'y') != NULL || strchr(str, 'Y') != NULL){
        return 1;
    }else return 0;
}

void* string_concat_op(const void* a, const void* b, AllErrors* error){
    if (!a || !b){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    const char* s1 = (const char*)a;
    const char* s2 = (const char*)b;
    
    char* result = (char*)malloc(strlen(s1) + strlen(s2) + 1);
    if (!result){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    strcpy(result, s1);
    strcat(result, s2);
    
    if (error) *error = ARRAY_OK;
    return result;
}


void func_apply_to_arg(const void* src, void* dst, AllErrors* error) {
     IntFunc f = (IntFunc)src;
    if (!f) {
        if (error) *error = NULL_POINTER;
        return;
    }
    int current_arg;
    int result = f(current_arg);
    
    *(int*)dst = result;

    if(error)*error = NULL_POINTER;
}

void func_apply_to_8(const void* src, void* dst, AllErrors* error) {
    IntFunc f = (IntFunc)src;
    if (!f){
        if(!error)*error = NULL_POINTER;
        return;
    }
    int result = f(8);
}

int func_even(const void * elem, AllErrors* error) {
    if (!elem) {
        if (error) *error = NULL_POINTER;
        return 0;
    }
    IntFunc f = (IntFunc)elem;
    if (error) *error = ARRAY_OK;
    if (f(7) % 2 == 0){
        return 1;
    }else return 0;
}

int func_greater_than_10(const void * elem, AllErrors* error) {
    if (!elem) {
        if (error) *error = NULL_POINTER;
        return 0;
    }
    IntFunc f = (IntFunc)elem;
    if (error) *error = ARRAY_OK;
    if(f(7) > 10){
        return 1;
    }else return 0;
}

void * func_compose( const void * a, const void * b, AllErrors* error) {
    if (!a || !b) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    if (error) *error = ARRAY_OK;
    return (void*)b;
}

void do_map() {
    if (!current_array) {
        puts("Массив не создан");
        return;
    }
    
    if (current_array->type->clone == string_clone) {
        puts("Выберите преобразование:");
        puts("1. toUpperCase");
        puts("2. toLowerCase");
        printf("Ваш выбор: ");
        
        unsigned int choice;
        scanf("%u", &choice);
        clear_input();

        void (*transform)(const void*, void*, AllErrors*) = NULL;
        
        switch (choice) {
            case 1: transform = string_to_upper; break;
            case 2: transform = string_to_lower; break;
            default: puts("Неверный выбор"); return;
        }
        
        DinamicArray* result = map(current_array, transform,
                                   get_string_type_info(), &last_error);
        if (result) {
            puts("Результат map:");
            char* str = array_to_string(result, &last_error);
            if (str) {
                printf("%s\n", str);
                free(str);
            }
            destroy_array(result, &last_error);
        } else {
            print_error("map");
        }
    }
    else if (current_array->type->clone == func_clone) {
        puts("Выберите аргумент:");
        puts("1. Применить к 8");
        puts("2. Применить к введенному числу");
        printf("Ваш выбор: ");
        
        unsigned int choice;
        scanf("%u", &choice);
        clear_input();
        
        void (*transform)(const void*, void*, AllErrors*) = NULL;
        
        if (choice == 1) {
            transform = func_apply_to_8;
        } else if (choice == 2) {
            printf("Введите число: ");
            scanf("%d", &current_arg);
            clear_input();
            transform = func_apply_to_arg;
        } else {
            puts("Неверный выбор");
            return;
        }
        
        DinamicArray* result = map(current_array, transform,
                                   get_int_type_info(), &last_error);
        if (result) {
            puts("Результаты применения функций:");
            char* str = array_to_string(result, &last_error);
            if (str) {
                printf("%s\n", str);
                free(str);
            }
            destroy_array(result, &last_error);
        } else {
            print_error("map");
        }
    }
    else {
        puts("Неподдерживаемый тип для map");
    }
}

void do_where() {
    if (!current_array) {
        puts("Массив не создан");
        return;
    }
    
    if (current_array->type->clone == string_clone) {
        puts("Выберите условие:");
        puts("1. Длина > 4");
        puts("2. Содержит букву 'y'");
        printf("Ваш выбор: ");
        
        unsigned int choice;
        scanf("%u", &choice);
        clear_input();
        
        int (*predicate)(const void*, AllErrors*) = NULL;
        
        switch (choice) {
            case 1: predicate = string_length_4; break;
            case 2: predicate = string_contains_y; break;
            default: puts("Неверный выбор"); return;
        }
        
        DinamicArray* result = where(current_array, predicate, &last_error);
        if (result) {
            printf("Результат where: ");
            if (get_size(result, &last_error) > 0) {
                char* str = array_to_string(result, &last_error);
                if (str) {
                    printf("%s\n", str);
                    free(str);
                }
            } else {
                puts("пусто");
            }
            destroy_array(result, &last_error);
        } else {
            print_error("where");
        }
    }
    else if (current_array->type->clone == func_clone) {
        puts("Выберите условие:");
        puts("1. f(7) > 10");
        puts("2. f(7) - четное");
        printf("Ваш выбор: ");
        
        unsigned int choice;
        scanf("%u", &choice);
        clear_input();
        
        int (*predicate)(const void*, AllErrors*) = NULL;
        
        switch (choice) {
            case 1: predicate = func_greater_than_10; break;
            case 2: predicate = func_even; break;
            default: puts("Неверный выбор"); return;
        }
        
        DinamicArray* result = where(current_array, predicate, &last_error);
        if (result) {
            printf("Результат where: ");
            if (get_size(result, &last_error) > 0) {
                char* str = array_to_string(result, &last_error);
                if (str) {
                    printf("%s\n", str);
                    free(str);
                }
            } else {
                puts("пусто");
            }
            destroy_array(result, &last_error);
        } else {
            print_error("where");
        }
    }
    else {
        puts("Неподдерживаемый тип для where");
    }
}


void do_reduce() {
    if (!current_array) {
        puts("Массив не создан");
        return;
    }
    
    if (get_size(current_array, &last_error) == 0) {
        puts("Массив пуст");
        return;
    }
    
    if (current_array->type->clone == string_clone) {
        puts("Выберите операцию:");
        puts("1. Конкатенация строк");
        printf("Ваш выбор: ");
        
        unsigned int choice;
        scanf("%u", &choice);
        clear_input();
        
        if (choice != 1) {
            puts("Неверный выбор");
            return;
        }
        
        void* init = "";
        void* result = reduce(current_array, string_concat_op, init, &last_error);
        
        if (result) {
            printf("Результат reduce: ");
            char* str = current_array->type->to_string(result, &last_error);
            if (str) {
                printf("%s\n", str);
                free(str);
            }
            current_array->type->free(result, &last_error);
        } else {
            print_error("reduce");
        }
    }
    else if (current_array->type->clone == func_clone) {
        puts("Выберите операцию:");
        puts("1. Композиция функций");
        printf("Ваш выбор: ");
        
        unsigned int choice;
        scanf("%u", &choice);
        clear_input();

        if (choice != 1) {
            puts("Неверный выбор");
            return;
        }
        
        void* init = get(current_array, 0, &last_error);
        void* result = reduce(current_array, func_compose, init, &last_error);
        
        if (result) {
            printf("Результат reduce: композиция функций\n");
            int test_val = ((IntFunc)result)(5);
        } else {
            print_error("reduce");
        }
    }
    else {
        puts("Неподдерживаемый тип для reduce");
    }
}

void do_concatenation(){
    if (!current_array) {
        puts("Сначала создайте первый массив");
        return;
    }
    
    DinamicArray* second_array = NULL;
    
    if (current_array->type->clone == string_clone){
        second_array = create_array(get_string_type_info(), &last_error);
        if (last_error == ARRAY_OK) {
            append(second_array, "extra", &last_error);
            append(second_array, "data", &last_error);
            puts("Создан второй массив: [\"extra\", \"data\"]");
        }
    } else if (current_array->type->clone == func_clone) {
        second_array = create_array(get_func_type_info(), &last_error);
        if (last_error == ARRAY_OK) {
            append(second_array, inc, &last_error);
            append(second_array, square, &last_error);
            puts("Создан второй массив: [inc, square]");
        }
    } else {
        puts("Неподдерживаемый тип для конкатенации");
        return;
    }

    if (!second_array){
        print_error("create second array");
        return;
    }
    
    DinamicArray* result = concatenation(current_array, second_array, &last_error);
    
    if (result){
        puts("Результат конкатенации:");
        char* str = array_to_string(result, &last_error);
        if (str) {
            printf("%s\n", str);
            free(str);
        }
        destroy_array(result, &last_error);
    } else {
        print_error("concatenation");
    }
    
    destroy_array(second_array, &last_error);
}