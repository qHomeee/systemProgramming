#ifndef MF_H
#define MF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Макрос возведения в квадрат
#define SQUARE(x) ((x) * (x))

// Режим проверки треугольника
#define CHECK_MODE 1
#define EPS 0.000001

// Старые арифметические функции
static int addition(int a, int b) {
    return a + b;
}

static int minus(int a, int b) {
    return a - b;
}

static int plural(int a, int b) {
    return a * b;
}

static double division(double a, double b) {
    return a / b;
}


static char* concat_strings(const char* s1, const char* s2) {
    char* result = calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));

    if (result == NULL)
        return NULL;

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

// Число в строку
static char* to_str(char* dest, int a) {
    sprintf(dest, "%d", a);
    return dest;
}

// Строка в число
static int to_int(const char* string) {
    return atoi(string);
}

// Длина отрезка по координатам
static double distance(double x1, double y1, double x2, double y2) {
    return sqrt(SQUARE(x2 - x1) + SQUARE(y2 - y1));
}

// Проверка треугольника
static void triangle(double x1, double y1,
                     double x2, double y2,
                     double x3, double y3) {

    double a = distance(x1, y1, x2, y2);
    double b = distance(x2, y2, x3, y3);
    double c = distance(x1, y1, x3, y3);

#if CHECK_MODE == 1

    if (a + b <= c + EPS ||
        a + c <= b + EPS ||
        b + c <= a + EPS) {
        printf("Треугольник не существует\n");
        return;
    }

#elif CHECK_MODE == 2

    double d = (x2 - x1) * (y3 - y1) -
               (y2 - y1) * (x3 - x1);

    if (fabs(d) <= EPS) {
        printf("Треугольник не существует\n");
        return;
    }

#else

    printf("Неверный режим проверки\n");
    return;

#endif

    // Периметр
    double perimeter = a + b + c;

    // Полупериметр
    double p = perimeter / 2;

    // Площадь по формуле Герона
    double area = sqrt(p * (p - a) * (p - b) * (p - c));

    printf("Периметр: %.2f\n", perimeter);
    printf("Площадь: %.2f\n", area);
}

#endif