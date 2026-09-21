#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>


int  kvadratnoeUravnenie(int a, int b, int c)
{
    double result1[2];
    double D =  b* b - 4* a * c;
    
    if(D > 0)
    {
        result1[0] = (-b + sqrt(D)) / (2 * a);
        result1[1] = (-b - sqrt(D)) / (2 * a);
        for (int i = 0; i < 2; i++)
        {
            printf("%f ",result1[i]);
        }
        return 2;
    }
    
    else if(D == 0)
    {
        result1[0] = (-b + sqrt(D)) / (2 * a);
        printf("%f", result1[0]);
        return 1;
    }
    
    else if(D < 0)
    {
        printf("Корней нет");
        return 0;
    }
    else{
        printf("Корней нет");
        return 0;
    }
}

int systemOfTwoLinageUravneniy(double a1, double b1,double c1, double a2, double b2, 
    double c2, double* result){

    double D;
    double Dx;
    double Dy;

    D = a1 * b2 - a2 * b1;
    if(D != 0)
    {
        Dx = c1 * b2 - c2 * b1;
        Dy = a1 * c2 - a2 * c1;

        result[0] = Dx/D;
        result[1] = Dy/D;

        return 1;

    }

    if(a1 * c2 == a2  *c1 && b1 * c2 == b2 * c1)
    {
        return 2;
    }
    return 0;

}


int factorial(int n)
{
    int result = 1;

    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
    
}


void choice()
{
    printf("Enter number of task: ");
    int ch;
    scanf("%d", &ch);
    switch(ch){
        case 1:
            printf("\nВведите три значения для квадратного уравнения(a, b , c) через пробел: ");
            int a, b,c;
            scanf("%d %d %d",&a, &b,&c);
            kvadratnoeUravnenie(a,b,c);
            break;
        case 2:
            double * result = calloc(4, sizeof(double));
            double a1,b1,c1,a2,b2,c2;
            printf("Введите шесть значения для квадратного уравнения(a, b , c) через пробел: ");
            scanf("%f %f %f %f %f %f",&a1,&b1,&c1,&a2,&b2,&c2);
            systemOfTwoLinageUravneniy(a1,b1,c1,a2,b2,c2,result);
            printf("%f", result);
            break;
        case 3:
            int n;
            scanf("%d",&n);
            printf("Факториал = %llu\n", factorial(n));
            
    }
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    choice();
    return 0;
}