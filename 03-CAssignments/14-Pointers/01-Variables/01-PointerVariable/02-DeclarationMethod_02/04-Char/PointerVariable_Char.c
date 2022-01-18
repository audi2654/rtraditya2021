//C Pointers assignment : Declaration Method - 1
//Program to declare pointer variables of type CHAR

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char ampChar;
    char* ptr = NULL;   //declaration method - 2 : ptr is a variable of type char*, char pointer
    //declaration method - 1 : *ptr, star ptr is a variable of type char
    //both are exactly same, just different ways of reading the same pointer var

    //code
    ampChar = 'A';

    printf("\n\n");
    printf("Before ptr = &ampChar\n\n");
    printf("Value of ampChar                                 = %c\n", ampChar);
    printf("Address of ampChar                               = %p\n", &ampChar);
    printf("Value at address of ampChar                      = %c\n", *(&ampChar));

    //Assigning address of var 'ampChar' to pointer var 'ptr'
    //ptr now contains addr of ampChar, hence ptr can be treated as same as &ampChar
    ptr = &ampChar;

    printf("\n\n");
    printf("After ptr = &ampChar\n\n");
    printf("Value of ampChar                                 = %c\n", ampChar);
    printf("Address of ampChar                               = %p\n", ptr);
    printf("Value at address of ampChar                      = %c\n\n", *(ptr));

    return(0);
}
