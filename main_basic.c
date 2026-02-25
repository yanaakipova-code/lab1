#include "main_basic.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

DinamicArray* current_array = NULL;
ArrayErrors last_error;

void clear_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void print_error(const char* context){
    printf("Ошибка в %s: ", context);
    switch (last_error){
        case ARRAY_OK: printf("нет ошибки"); break;
        case MEMORY_ALLOCATION_FAILED: printf("не удалось выделить память"); break;
        case NULL_POINTER: printf("нулевой указатель"); break;
        case INDEX_OUT: printf("индекс вне диапазона"); break;
        case DIFFERENT_TYPE: printf("несовместимые типы"); break;
        default: printf("неизвестная ошибка (%d)", last_error);
    }
}

void print_menu(){
    printf("-------------------------------------------------\n");
    puts("1. Создать массив (строки)");  
    puts("2. Создать массив (функции)");
    puts("3. Добавить элемент");
    puts("4. Показать массив");
    puts("5. Информация o массиве");
    puts("6. MAP - применить преобразование");
    puts("7. WHERE - фильтрация");
    puts("8. REDUCE - свертка");
    puts("9. CONCAT - конкатенация");
    puts("0. Выход");
    printf("Ваш выбор: ");
}

void create_string_array(){
    if (current_array){
        destroy_array(current_array, &last_error);
    }
    
    current_array = create_array(GetStringTypeInfo(), &last_error);
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
    
    current_array = create_array(GetFuncTypeInfo(), &last_error);
    if (last_error == ARRAY_OK){
        puts("Массив функций создан");
        append(current_array, inc, &last_error);
        append(current_array, dec, &last_error);
        append(current_array, square, &last_error);
        puts("Добавлены тестовые функции");
    } else{
        print_error("create_func_array");
    }
}

void add_element() {
    if (!current_array) {
        printf("Сначала создайте массив\n");
        return;
    }
    
    switch (current_array->type->kind){
        case TYPE_STRING:{
            char buffer[256];
            printf("Введите строку: ");
            clear_input();
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            
            if (strlen(buffer) == 0) {
                printf("Строка не может быть пустой\n");
                return;
            }
            
            append(current_array, buffer, &last_error);
            if (last_error == ARRAY_OK) {
                printf("Строка \"%s\" добавлена\n", buffer);
            } else{
                print_error("add_element");
            }
            break;
        }
        
        case TYPE_FUNC: {
            puts("Выберите функцию:\n");
            puts("1. inc (+1)\n");
            puts("2. dec (-1)\n");
            puts("3. square (x*x)\n");
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
                    printf("Неверный выбор\n");
                    return;
            }
            
            append(current_array, func, &last_error);
            if (last_error == ARRAY_OK){
                printf("Функция %s добавлена\n", name);
            } else {
                print_error("add_element");
            }
            break;
        }
        
        default:
            puts("Неподдерживаемый тип\n");
    }
}


