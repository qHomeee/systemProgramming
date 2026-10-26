#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define INPUT_FILE "input.txt"
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

int main(void)
{
    char buffer[BUFFER_SIZE];
    char result[RESULT_SIZE];
    double a, b, c;
    char extra;
    DWORD bytesRead = 0, bytesWritten = 0;

    HANDLE input = CreateFileA(INPUT_FILE, GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (input == INVALID_HANDLE_VALUE)
    {
        snprintf(result, RESULT_SIZE, "Error: cannot open input.txt.\n");
    }
    else
    {
        BOOL ok = ReadFile(input, buffer, BUFFER_SIZE - 1, &bytesRead, NULL);
        CloseHandle(input);

        if (!ok)
            snprintf(result, RESULT_SIZE, "Error: cannot read input.txt.\n");
        else if (bytesRead == BUFFER_SIZE - 1)
            snprintf(result, RESULT_SIZE, "Error: input file is too large.\n");
        else
        {
            buffer[bytesRead] = '\0';

            if (memchr(buffer, '\0', bytesRead) != NULL ||
                sscanf(buffer, "%lf %lf %lf %c", &a, &b, &c, &extra) != 3 ||
                !isfinite(a) || !isfinite(b) || !isfinite(c))
            {
                snprintf(result, RESULT_SIZE,"Error: input must contain exactly 3 numbers.\n");
            }
            else
            {
                solve(a, b, c, result);
            }
        }
    }

    HANDLE output = CreateFileA(OUTPUT_FILE, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (output == INVALID_HANDLE_VALUE)
    {
        printf("Error: cannot create result.txt.\n");
        return 1;
    }

    DWORD length = (DWORD)strlen(result);
    BOOL ok = WriteFile(output, result, length, &bytesWritten, NULL);
    CloseHandle(output);

    if (!ok || bytesWritten != length)
    {
        printf("Error: cannot write result.txt.\n");
        return 1;
    }

    printf("Result saved to result.txt\n");
    return 0;
}
