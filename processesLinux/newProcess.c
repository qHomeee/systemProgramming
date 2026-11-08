#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
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
            snprintf(result, RESULT_SIZE,
                     "D = %.10g\n количество корней: 2\nx1 = %.10g\nx2 = %.10g\n",
                     d, x1, x2);
        else
            snprintf(result, RESULT_SIZE, "Error: roots are too large.\n");
    }
}


int  main(int argc, char*argv[]){

    
    char result[RESULT_SIZE];
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    printf("Полученные числа: %d %d %d\n", a, b, c);
    solve(a, b, c,  result);
    int output = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output == -1)
    {
        printf("Error: cannot create result.txt.\n");
        return 1;
    }

    size_t length = strlen(result);
    size_t written = 0;
    while (written < length) 
    {
        ssize_t n = write(output, result + written, length - written);
        if (n == -1 && errno == EINTR)
            continue;
        if (n <= 0)
        {
            printf("Error: cannot write result.txt.\n");
            close(output);
            return 1;
        }
        written += (size_t)n;
    }
    if (close(output) == -1)
    {
        printf("Error: cannot close result.txt.\n");
        return 1;
    }

    printf("Result saved to result.txt\n");
    return 0;
}