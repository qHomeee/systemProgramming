#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"



int*  my_type_addition(int a, int b, int c){
    int* result = calloc(1, sizeof(int));
    if(c == 0){
        *result = 0;
        return result;
    }
    *result=(a+b)/c;
    return result;
}

int* my_substraction(int a, int b, int c){
    int* result = calloc(2, sizeof(int));
    result[0] = a;
    result[1] = b-c;
    return result;
}


int main()
{
    typedef int* (*Operation)(int, int, int);

    Operation x = my_substraction;
    int* y = x(5,4,2);
    printf("первое задание\n");
    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", y[i]);
    }
    
    printf("второе задание\n");
    typedef Operation Operations[3];
    Operations arr;
    arr[0] = my_substraction;
    arr[1] = my_type_addition;
    arr[2] = my_substraction;

    for (int i = 0; i < 3; i++)
    {
        int* y;
        switch(i){
            case 0:
                y = arr[i](5,3,4);
                for (int j = 0; j < 2; j++)
                {
                    printf("%d\n", y[j]);
                }
                continue;
            case 1:
                 y = arr[i](0, 0, 0);
                printf("%d\n",*y);
                continue;
            case 2:
                y = arr[i](5, 4, 2);
                for (int j = 0; j < 2; j++)
                {
                    printf("%d\n", y[j]);
                }
                continue;
                
        }
    }
    
    

}