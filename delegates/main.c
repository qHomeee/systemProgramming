#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "mm_malloc.h"
#include "stdlib.h"


int* return_two_cores(int a, int b, int c){
    int *result[2] = {0,0};
    return *result;
}


int main()
{
    typedef int* (*Operation)(int, int, int);

    Operation x = return_two_cores;
    printf("%d", x(1,2,3));
    

}