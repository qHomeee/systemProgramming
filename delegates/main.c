#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "mm_malloc.h"
#include "stdlib.h"



int*  my_type_addition(int a, int b, int c){
    if(c == 0){
        int* result = calloc(1, sizeof(int));
        *result = 0;
        return result;
    }
    int *result = (a+b)/c;
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
    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", y[i]);
    }
    

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
                y =  arr[i];
                for (int j = 0; j < 2; j++)
                {
                    printf("%d\n", y[j]);
                }
                continue;
            case 1:
                y = arr[i];
                printf("%d\n",y);
                continue;
            case 2:
                y =  arr[i];
                for (int j = 0; j < 2; j++)
                {
                    printf("%d\n", y[j]);
                }
                continue;
                
        }
    }
    
    

}