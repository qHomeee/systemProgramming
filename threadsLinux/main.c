#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int n;
    int result;
} ThreadData;



int factorial_fun(void* args)
{
    ThreadData* d = (ThreadData*)args;

    d->result = 1;

    for (int i = 1; i <= d->n; i++)
    {
        d->result *= i;
    }

    return NULL;
}


void* fibonaciFun(void* args)
{
    ThreadData* data = (ThreadData*)args;

    int prev1 = 0;
    int prev2 = 1;

    if (data->n == 0) {
        data->result = 0;
        return NULL;
    }

    for (int i = 2; i <= data->n; i++)
    {
        int current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }

    data->result = prev2;
    return NULL;
}

int main()
{
    ThreadData d = {3,0};
    ThreadData t = {3,0};
    pthread_t threadfuc;
    pthread_t threadfib;
    pthread_create(&threadfuc,NULL,factorial_fun,&d);
    pthread_create(&threadfib,NULL,fibonaciFun,&t);


    pthread_join(threadfuc, NULL);
    pthread_join(threadfib, NULL);
    printf("фибоначи: %d\n факториал: %d\n",t.result,d.result);
    

    return 0;
}