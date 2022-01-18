//C Pointers assignment : Declaration Method - 1
//Program to declare pointer variables of type DOUBLE

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    double ampNum;
    double *ptr = NULL;   //declaration method - 1 : *ptr, star 'ptr' is a variable of type DOUBLE

    //code
    ampNum = 99.99997777f;

    printf("\n\n");
    printf("Before ptr = &ampNum\n\n");
    printf("Value of ampNum                                 = %lf\n", ampNum);
    printf("Address of ampNum                               = %p\n", &ampNum);
    printf("Value at address of ampNum                      = %lf\n", *(&ampNum));

    //Assigning address of var 'ampNum' to pointer var 'ptr'
    //ptr now contains addr of ampNum, hence ptr can be treated as same as &ampNum
    ptr = &ampNum;

    printf("\n\n");
    printf("After ptr = &ampNum\n\n");
    printf("Value of ampNum                                 = %lf\n", ampNum);
    printf("Address of ampNum                               = %p\n", ptr);
    printf("Value at address of ampNum                      = %lf\n\n", *(ptr));

    return(0);
}
