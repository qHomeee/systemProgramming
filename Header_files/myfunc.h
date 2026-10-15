#ifndef MYFUNC_H
#define MYFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int addition(int a, int b)
{
     return a+b;
     
}

int minus(int a,int b )
{
     return a -b;

}

int plural(int a, int b){
    return a*b;
}



double division(double a, double b)
{
    return a/b;
}


char* concat_strings(char* first_str, char* second_str)
{
    int first_len = strlen(first_str);
    int second_len = strlen(second_str);
    
    char* result = calloc(first_len+second_len+1, sizeof(char));
    strcpy(result,first_str);
    strcat(result,second_str);
    return result;
}



char * to_str(char* dest,int a)
{
    sprintf(dest,"%d",a);
    return dest;
}




int to_int(char*string)
{
     int dest =  atoi(string); 
    return dest;   
}


#endif