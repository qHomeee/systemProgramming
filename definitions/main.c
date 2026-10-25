#define _CRT_SECURE_NO_WARNINGS

#define NUM1 2
#define NUM2 3
#define NUM_TO_STR 5
#define BUFFER_SIZE 20

#define FILE_NAME "dsd.txt"
#define FILE_TEXT "12321312312"
#define STR1 "hello "
#define STR2 "world"
#define NUMBER_TEXT "203"

#include "mf.h"

int main(void) {

    // Предыдущее задание
    FILE* f = fopen(FILE_NAME, "w");

    if (f != NULL) {
        fprintf(f, "%s", FILE_TEXT);
        fclose(f);
    }

    printf("Сложение: %d\n", addition(NUM1, NUM2));

    char* s = concat_strings(STR1, STR2);
    if (s != NULL) {
        printf("Строка: %s\n", s);
        free(s);
    }

    char text[BUFFER_SIZE];
    to_str(text, NUM_TO_STR);
    printf("Число в строку: %s\n", text);

    printf("Строка в число: %d\n", to_int(NUMBER_TEXT));

    // Новое задание
    double x1, y1, x2, y2, x3, y3;

    printf("\nВведите координаты первой точки: ");
    if (scanf("%lf %lf", &x1, &y1) != 2) return 1;

    printf("Введите координаты второй точки: ");
    if (scanf("%lf %lf", &x2, &y2) != 2) return 1;

    printf("Введите координаты третьей точки: ");
    if (scanf("%lf %lf", &x3, &y3) != 2) return 1;

    triangle(x1, y1, x2, y2, x3, y3);

    return 0;
}