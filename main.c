#include "main_basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #endif

    int choice;
    
    while (1) {
        print_menu();
        
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
    return 0;
}


 