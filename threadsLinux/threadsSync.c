#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;


void counteraddition(void* args){
    
    int numThread = *(int*) args;
    
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&mutex);
        counter ++;    
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_lock(&mutex);
    int result = counter;
    pthread_mutex_unlock(&mutex);
    
    printf("У потока номер [%d]: %d\n", numThread, result);
}



int main(){
    pthread_t thread1, thread2;
    int a = 1;
    int b = 2;
    pthread_create(&thread1,NULL,counteraddition,&a);
    pthread_create(&thread2,NULL,counteraddition,&b);


    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    pthread_mutex_destroy(&mutex);

}