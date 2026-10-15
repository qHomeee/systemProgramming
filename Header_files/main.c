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
    char * s1 = "hello ";
    char * s2 = "world";
    char* s = concat_strings(s1, s2);
    printf("\n");
    printf("%s", s);
    char* to_string = calloc(2,sizeof(char));
    to_str(to_string,5);
    printf("\n%s",to_string);
    char* yen = calloc(4,sizeof(char));
    yen = "203";
    
    int des =to_int(yen);
    printf("\n%d",des);

}



