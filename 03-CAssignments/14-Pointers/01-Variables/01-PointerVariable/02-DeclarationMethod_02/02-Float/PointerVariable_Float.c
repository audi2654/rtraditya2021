//C Pointers assignment : Declaration Method - 2
//Program to declare pointer variables of type FLOAT

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    float ampNum;
    float* ptr = NULL;   //declaration method - 2 : ptr is a variable of type float*, float pointer
    //declaration method - 1 : *ptr, star ptr is a variable of type FLOAT
    //both are exactly same, just different ways of reading the same pointer var

    //code
    ampNum = 98.9888f;

    printf("\n\n");
    printf("Before ptr = &ampNum\n\n");
    printf("Value of ampNum                                 = %f\n", ampNum);
    printf("Address of ampNum                               = %p\n", &ampNum);
    printf("Value at address of ampNum                      = %f\n", *(&ampNum));

    //Assigning address of var 'ampNum' to pointer var 'ptr'
    //ptr now contains addr of ampNum, hence ptr can be treated as same as &ampNum
    ptr = &ampNum;

    printf("\n\n");
    printf("After ptr = &ampNum\n\n");
    printf("Value of ampNum                                 = %f\n", ampNum);
    printf("Address of ampNum                               = %p\n", ptr);
    printf("Value at address of ampNum                      = %f\n\n", *(ptr));

    return(0);
}
