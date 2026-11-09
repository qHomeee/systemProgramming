#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define INPUT_FILE "input.txt"
#define BUFFER_SIZE 256
#define RESULT_SIZE 512
#define PATH "newprocess.exe"

int main(void)
{
    // для передачи в другой процесс
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char buffer[BUFFER_SIZE];
    char result[RESULT_SIZE];
    double a, b, c;
    char extra;
    char CMDARGS[256];


    DWORD bytesRead = 0;

    HANDLE input = CreateFileA(INPUT_FILE, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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
                snprintf(result, RESULT_SIZE, "Error: input must contain exactly 3 numbers.\n");
            }
            else
            {
                char sa[20], sb[20], sc[20];
                printf("Значения: a=%d, b=%d, c=%d\n", a, b, c);
                snprintf(sa, sizeof(sa), "%.17g", a);
                snprintf(sb, sizeof(sb), "%.17g", b);
                snprintf(sc, sizeof(sc), "%.17g", c);
                 snprintf(CMDARGS, sizeof(CMDARGS),
             "%s %s %s %s",PATH, sa, sb, sc);
                if (!CreateProcessA(PATH,
                                    CMDARGS,
                                    NULL,
                                    NULL,
                                    TRUE,
                                    0,
                                    NULL,
                                    NULL,
                                    &si,
                                    &pi))
                {
                    printf("процесс не создался, код ошибки: %d.\n", GetLastError());
                }
                WaitForSingleObject(pi.hProcess, INFINITE);
                DWORD childexitcode;
                GetExitCodeProcess(pi.hProcess, &childexitcode);
                printf("дочерний процесс завершил работу с кодом: %d\n", childexitcode);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                system("pause");
                return 0;
            }
        }
    }
}