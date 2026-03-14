#include "intr.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 


int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    
    interface_print();
}


 /*
 в main у нас только вызов интерфейса (вынести в отдельный файл) и тестов, никакой логики + 
в map надо переписать логику +
if (error) - надо сразу проверять, чтоьы ошибки обязательно были +
resize - вызывается только внутри метода push, когда size = capacity, и никогда больше +
concat - можно сразу вычислить размер итогового массива +
тесты в одну папку + 
 */