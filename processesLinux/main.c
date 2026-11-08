#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "result.txt"
#define BUFFER_SIZE 256
#define RESULT_SIZE 512

int main(void)
{
    char buffer[BUFFER_SIZE];
    char result[RESULT_SIZE];
    double a, b, c;
    char extra;

    int input = open(INPUT_FILE, O_RDONLY);

    if (input == -1)
    {
        snprintf(result, RESULT_SIZE, "Error: cannot open input.txt.\n");
    }
    else
    {
        ssize_t bytesRead;
        do
        {
            bytesRead = read(input, buffer, BUFFER_SIZE - 1);
        } while (bytesRead == -1 && errno == EINTR);
        close(input);

        if (bytesRead == -1)
            snprintf(result, RESULT_SIZE, "Error: cannot read input.txt.\n");
        else if (bytesRead == BUFFER_SIZE - 1)
            snprintf(result, RESULT_SIZE, "Error: input file is too large.\n");
        else
        {
            buffer[bytesRead] = '\0';

            if (memchr(buffer, '\0', (size_t)bytesRead) != NULL ||
                sscanf(buffer, "%lf %lf %lf %c", &a, &b, &c, &extra) != 3 ||
                !isfinite(a) || !isfinite(b) || !isfinite(c))
            {
                snprintf(result, RESULT_SIZE,
                         "Error: input must contain exactly 3 numbers.\n");
            }
            else
            {
                char sa[20], sb[20], sc[20];
                printf("Значения: a=%d, b=%d, c=%d\n", a, b, c);
                snprintf(sa, sizeof(sa), "%.17g", a);
                snprintf(sb, sizeof(sb), "%.17g", b);
                snprintf(sc, sizeof(sc), "%.17g", c);
                printf("Аргументы: %s %s %s\n", sa, sb, sc);
                pid_t pid = fork();

                if (pid == 0)
                {
                    char *args[] = {"./newProcess", sa, sb, sc, NULL};

                    execv("./newProcess", args);
                    perror("execv");
                    _exit(1);
                }
            }
        }

        return 1;
    }
}
