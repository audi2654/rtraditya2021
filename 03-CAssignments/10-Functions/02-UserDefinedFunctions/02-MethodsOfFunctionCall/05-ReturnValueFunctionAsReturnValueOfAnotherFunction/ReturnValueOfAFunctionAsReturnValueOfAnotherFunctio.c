//C Functions assignment : User Defined Functions : Methods of Calling - 5
//Program to show how to use the return value of a user defined function as return value of another user defined function

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function decl.
    int ampAddition(int, int);

    //var decl.
    int r;
    int num1, num2;

    //code
    num1 = 10;
    num2 = 20;

    printf("\n\n");

    printf("%d + %d = %d", num1, num2, ampAddition(num1, num2));
    //using here the return value of ampAddition() as parameter to another call to ampAddition()

    printf("\n\n");

    return(0);
}

//function definition
int ampAddition(int a, int b)
{
    //func prototype
    int Add(int, int);

    //code
    return(Add(a, b));
    //using return value of function Add() as return value of function ampAddition()
}

int Add(int x, int y)
{
    //code
    return(x + y);
}
