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

void print_array(int*arr, int len){
    for (int i = 0; i < len; i++)
    {
        printf("%3d",arr[i]);
    }
     printf("\n");
}


int* create_massive( int*len){
        smart_log(*len);
        int* arr = calloc(*len, sizeof(int));
        smart_log(*arr);
        for (int i = 0; i < *len; i++)
        {
            arr[i] = i;
        }
        return arr;
}

void delete_massive(int* arr){
    if(arr == NULL){
        printf("пустой массив");
    }
    smart_log(*arr);
    free(arr);
    arr = NULL;
}

int** init_triangle_massive(int* len){
    smart_log(*len);
    int**arr = calloc(*len,sizeof(int*));
    smart_log(*arr);
    for (int i = 0; i < *len; i++)
    {
        arr[i] = calloc(i+1, sizeof(int));
        for (int  j = 0; j < i+1; j++)
        {
            arr[i][j] = j;
        }
        
    }
    return arr;
}

void print_triangle_massive(int ** triangle, int*len){
    smart_log(*triangle);
    for (int i = 0; i < *len; i++)
    {
        for (int j = 0; j < i+1; j++)
        {
            printf("%3d",triangle[i][j]);
        }
        printf("\n");
    }
    
}

int main(){

    while(true){
            printf("\nсделайте выбор 1) изменение целочисленной 2) динамическое создание и удаление массива: ");
            int* choice = calloc(1, sizeof(int));
            scanf("%d",choice);
            switch(*choice){
                case 1:
                    printf("\nвведите число");
                    int*num =calloc(1,sizeof(int));
                    scanf("%d",num);
                    smart_log(*num);
                    print_new_value(num);
                break;
                case 2:
                    printf("\nвведите длину массива: \n");
                    int*len = calloc(1,sizeof(int));
                    scanf("%d",len);
                    smart_log(*len);
                    int* mas = create_massive(len);
                    smart_log(*mas);
                    print_array(mas,*len);
                    delete_massive(mas);
                break;

                case 3:
                    printf("ввдеите длину массива: ");
                    int*l = calloc(1,sizeof(int));
                    scanf("%d",l);
                    smart_log(*l);
                    int**arr = init_triangle_massive(l);
                    smart_log(*arr);
                    print_triangle_massive(arr,l);
                break;
            }
    }


}