# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "malloc.h"

void log_int(int x) {
    printf("\nзначение: %d\n", x);
}

void log_double(double x) {
    printf("\nзначение: %g\n", x);
}

void log_char(char x) {
    printf("\nзначение: '%c'\n", x);
}

void log_string(const char *x) {
    printf("\nстрока: \"%s\"\n", x ? x : "(null)");
}

void log_pointer(const void *x) {
    printf("\nуказывает на: %p\n", (void *)x);
}

#define smart_log(X) do {                                   \
    printf("\n[LOG] %s | адрес: %p | ", #X, (void *)&(X));     \
    _Generic((X),                                          \
        int:         log_int,                              \
        float:       log_double,                           \
        double:      log_double,                           \
        char:        log_char,                             \
        char *:      log_string,                           \
        const char *: log_string,                          \
        default:     log_pointer                           \
    )(X);                                                  \
} while (0)


void print_new_value(int* num){
    smart_log(*num);
        if(num ==NULL)
        {
                printf("ошибка: пустое значение");
                return;
        }
        printf("\nстарое значение: %d",*num);
        printf("\nвведите значение замененное: ");
        scanf("%d",num);
        printf("\nновое значение: %d",*num);
        smart_log(*num);

}



int main(){

    while(true){
            printf("\nсделайте выбор 1) изменение целочисленной: ");
            int* choice = calloc(1, sizeof(int));
            scanf("%d",choice);
            smart_log(choice);
            switch(*choice){
                case 1:
                    printf("\nвведите число");
                    int*num =calloc(1,sizeof(int));
                    scanf("%d",num);
                    smart_log(*num);
                    print_new_value(num);
                break;

            }
    }


}