//C Pointers assignment : Declaration Method - 2
//Program to declare pointer variables of type INT

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int ampNum;
    int* ptr = NULL;   
    //declaration method - 1 : *ptr, star ptr is a variable of type integer
    //declaration method - 2 : ptr is a variable of type int*, integer pointer
    //both are exactly same, just different ways of reading the same pointer var

    //code
    ampNum = 20;

    printf("\n\n");
    printf("Before ptr = &ampNum\n\n");
    printf("Value of ampNum                                 = %d\n", ampNum);
    printf("Address of ampNum                               = %p\n", &ampNum);
    printf("Value at address of ampNum                      = %d\n", *(&ampNum));

    //Assigning address of var 'ampNum' to pointer var 'ptr'
    //ptr now contains addr of ampNum, hence ptr can be treated as same as &ampNum
    ptr = &ampNum;

    printf("\n\n");
    printf("After ptr = &ampNum\n\n");
    printf("Value of ampNum                                 = %d\n", ampNum);
    printf("Address of ampNum                               = %p\n", ptr);
    printf("Value at address of ampNum                      = %d\n", *(ptr));

    return(0);
}
