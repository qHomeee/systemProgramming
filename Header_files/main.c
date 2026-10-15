#define _CRT_SECURE_NO_WARNINGS
#include "myfunc.h"






int main()
{
    FILE * f = fopen("dsd.txt", "w");

    char* str = calloc(20,sizeof(char));
    str = "12321312312";
    fprintf(f, "%s",str);
    fclose(f);

    int a = addition(2,3);
    printf("%d", a);

}



