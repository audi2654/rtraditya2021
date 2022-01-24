//C Pointers assignment : Functions
//Program to show working of function pointers

#include <stdio.h>

int main(int argc, char* argv[], char *envp[])
{
    //func decl.
    int ampAddIntegers(int, int);
    int ampSubtractIntegers(int, int);
    float ampAddFloats(float, float);

    //var decl.
    typedef int (*AddIntsFuncPtr)(int, int);
    AddIntsFuncPtr ptrAddIntegers = NULL;
    AddIntsFuncPtr ptrSubtractIntegers = NULL;

    typedef float (*AddFloatsFuncPtr)(float, float);
    AddFloatsFuncPtr ptrAddFloats = NULL;

    int iAnswer = 0;
    float fAnswer = 0.0f;

    //code
    ptrAddIntegers = ampAddIntegers;
    iAnswer = ptrAddIntegers(999, 99);
    printf("\n\n");
    printf("Sum of integers = %d\n\n", iAnswer);

    ptrSubtractIntegers = ampSubtractIntegers;
    iAnswer = ptrSubtractIntegers(999, 99);
    printf("\n\n");
    printf("Subtraction of integers = %d\n\n", iAnswer);

    ptrAddFloats = ampAddFloats;
    fAnswer = ptrAddFloats(999.99f, 99.99f);
    printf("\n\n");
    printf("Sum of float numbers = %f\n\n", fAnswer);

    return(0);
}

//func definition
int ampAddIntegers(int a, int b)
{
    //var decl.
    int c;

    //code
    c = a + b;
    return(c);
}

int ampSubtractIntegers(int a, int b)
{
    //var decl.
    int c;

    //code
    if(a > b)
        c = a - b;
    else
        c = b - a;

    return(c);
}

float ampAddFloats(float num1, float num2)
{
    //var decl.
    float ans;

    //code
    ans = num1 + num2;
    return(ans);
}
