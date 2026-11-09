#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OUTPUT_FILE "result.txt"
#define BUFFER_SIZE 256
#define RESULT_SIZE 512

void solve(double a, double b, double c, char result[])
{
    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
                snprintf(result, RESULT_SIZE, "Infinitely many solutions.\n");
            else
                snprintf(result, RESULT_SIZE, "Roots: 0\nNo solutions.\n");
        }
        else
        {
            double x = -c / b;
            if (isfinite(x))
                snprintf(result, RESULT_SIZE,
                         "Linear equation.\nRoots: 1\nx = %.10g\n", x);
            else
                snprintf(result, RESULT_SIZE, "Error: number is too large.\n");
        }
        return;
    }

    double d = b * b - 4 * a * c;

    if (!isfinite(d))
    {
        snprintf(result, RESULT_SIZE, "Error: discriminant is too large.\n");
    }
    else if (d < 0)
    {
        snprintf(result, RESULT_SIZE,
                 "D = %.10g\nRoots: 0\nNo real roots.\n", d);
    }
    else if (d == 0)
    {
        double x = -b / (2 * a);
        if (isfinite(x))
            snprintf(result, RESULT_SIZE, "D = 0\nRoots: 1\nx = %.10g\n", x);
        else
            snprintf(result, RESULT_SIZE, "Error: root is too large.\n");
    }
    else
    {
        double x1 = (-b + sqrt(d)) / (2 * a);
        double x2 = (-b - sqrt(d)) / (2 * a);

        if (isfinite(x1) && isfinite(x2))
            snprintf(result, RESULT_SIZE, "D = %.10g\n количество корней: 2\nx1 = %.10g\nx2 = %.10g\n", d, x1, x2);
        else
            snprintf(result, RESULT_SIZE, "Error: roots are too large.\n");
    }
}



int main(int argc, char* argv[])
{
     if (argc != 4) {
        printf("Ошибка: нужно передать 3 коэффициента\n");
        return 1;
    }

    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    double c = strtod(argv[3], NULL);
    
    printf("Полученные коэффициенты:\n");
    printf("a = %g\n", a);
    printf("b = %g\n", b);
    printf("c = %g\n", c);
    HANDLE output = CreateFileA(OUTPUT_FILE, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    char result[RESULT_SIZE];

    solve(a,b,c,result);

    DWORD bytesWritten = 0;
    if (output == INVALID_HANDLE_VALUE)
    {
        printf("Error: cannot create result.txt.\n");
        return -1;
    }

    DWORD length = (DWORD)strlen(result);
    BOOL ok = WriteFile(output, result, length, &bytesWritten, NULL);
    CloseHandle(output);

    if (!ok || bytesWritten != length)
    {
        printf("Error: cannot write result.txt.\n");
        return -1;
    }

    printf("Result saved to result.txt\n");
    return 100500;
}