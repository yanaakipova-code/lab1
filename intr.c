#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include "intr.h"
#include "main_basic.h"
void interface_print(){
    int choice;
    
    while (1) {
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
        
        if (scanf("%d", &choice) != 1) {
            puts("Ошибка ввода. Пожалуйста, введите число.");
            clear_input();
        }
        clear_input();
        
        switch (choice) {
            case 1:
                create_string_array();
                break;
                
            case 2:
                create_func_array();
                break;
                
            case 3:
                add_element();
                break;
                
            case 4:
                show_array();
                break;

            case 5:
                do_map();
                break;
                
            case 6:
                do_where();
                break;
                
            case 7:
                do_reduce();
                break;
                
            case 8:
                do_concatenation();
                break;
                
            default:
                puts("Неверный выбор. Пожалуйста, выберите от 0 до 8.");
        }
    }
    return;
}