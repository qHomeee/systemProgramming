#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <malloc.h>

void handler(int sig){
    signal(sig, SIG_DFL);
    char*msg = calloc(256,sizeof(char));
    if(sig == SIGINT){
     msg = "не мешай работать\n";
    
    }
    if(sig == SIGQUIT){
     msg = "Тебе не прервать меня\n";
    }
    printf("%s",msg);
}





int main(){
    signal(SIGINT,handler);
    signal(SIGQUIT,handler);
    printf("ПИД процесса: %d\n",getpid());

   
    while(1){
     printf("Я работаю\n");
         sleep(1);
    }
       
    
    
}