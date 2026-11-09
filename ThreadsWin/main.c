#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>

DWORD WINAPI TreadFactr(LPVOID param){
    int f = 0;
    int n = *(int*)param;
  for (int i = 0; i <= n; i++)
  {

    if (i == 0)

    {

      f = 1;

    }

    else

    {

      f *= i;

    }

    printf("factorial %d raven %d \n", i, f);

  }

  ExitThread(0);

}
DWORD WINAPI TreadFib(LPVOID param)

{
    int n = *(int*)param;
  int f = 0;

  int f1 = 1;

  int f2 = 1;

  for (int i = 0; i <= n; i++)

  {

    if (i > 1)

    {

      f = f1;

      f1 = f2;

      f2 += f;

    }

    printf("\n%d element Fibonachi raven %d \n", i, f2);

  }

  ExitThread(0);

}



int main()
{
    HANDLE Threads[2];
    int n = 10;
    int b = 30;
    Threads[0] = CreateThread(NULL, 0, TreadFactr, &n, 0, 0);
    Threads[1] = CreateThread(NULL, 0, TreadFib, &b, 0, 0);
    WaitForMultipleObjects(2, Threads, TRUE, INFINITE);
    CloseHandle(Threads[0]);
    CloseHandle(Threads[1]);

}