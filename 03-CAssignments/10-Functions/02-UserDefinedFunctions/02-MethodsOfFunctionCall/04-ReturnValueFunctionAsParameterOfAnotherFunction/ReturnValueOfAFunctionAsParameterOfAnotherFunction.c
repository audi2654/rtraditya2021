//C Functions assignment : User Defined Functions : Methods of Calling - 4
//Program to show how to use the return value of a user defined function as parameter of another user defined function

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function decl.
    int ampAddition(int, int);

    //var decl.
    int r;
    int num1, num2;
    int num3, num4;

    //code
    num1 = 10;
    num2 = 20;
    num3 = 30;
    num4 = 40;

    r = ampAddition(ampAddition(num1, num2), ampAddition(num3, num4));
    //using here the return value of ampAddition() as parameter to another call to ampAddition()

    printf("\n");

    printf("%d + %d + %d + %d = %d\n", num1, num2, num3, num4, r);

    return(0);
}

//function definition
int ampAddition(int a, int b)
{
    //var decl.
    int sum;

    //code
    sum = a + b;
    return(sum);
}
