#define _CRT_SECURE_NO_WARNINGS


#include <windows.h>
#include <stdio.h>
#include <math.h>
CRITICAL_SECTION cs;

DWORD WINAPI thread_for_counter(LPVOID param)
{
    int *count = (int *)param;

    for (int i = 0; i < 10000; i++)
    {
        EnterCriticalSection(&cs);

        (*count)++;

        LeaveCriticalSection(&cs);
    }

    return 0;
}


int main()
{
   
    HANDLE threads[3];
    int counter = 0;
    InitializeCriticalSection(&cs);
    threads[0] = CreateThread(NULL,0,thread_for_counter,&counter,0,NULL);
    threads[1] = CreateThread(NULL,0,thread_for_counter,&counter,0,NULL);
    threads[2] = CreateThread(NULL,0,thread_for_counter,&counter,0,NULL);
    if (threads[0] == NULL)
{
    printf("Ошибка создания потока: %lu\n", GetLastError());
    return 1;
}

    WaitForMultipleObjects(3, threads, TRUE, INFINITE);
    for (int i = 0; i < 3; i++)
    {
        CloseHandle(threads[i]);
    }
    
    printf("финальное число счетчика: %d", counter);
    DeleteCriticalSection(&cs);
}