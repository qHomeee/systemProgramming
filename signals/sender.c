#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int main(){
    int pid;
    printf("Введите пид процесса: \n");
    scanf("%d",&pid);
    kill(pid,SIGINT);
}