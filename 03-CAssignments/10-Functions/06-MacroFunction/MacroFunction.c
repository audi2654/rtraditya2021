//C Functions assignment : Macro Function
//Program to show use of macro in function

#include <stdio.h>

#define MAX_NUMBER(a, b) ((a > b) ? a : b)

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int iNum1;
    int iNum2;
    int iResult;

    float fNum1;
    float fNum2;
    float fResult;

    //code
    //Comparing integer values
    printf("\n\n");
    printf("Enter int iNum1 : ");
    scanf("%d", &iNum1);

    printf("\n");
    printf("Enter int iNum2 : ");
    scanf("%d", &iNum2);

    iResult = MAX_NUMBER(iNum1, iNum2);
    printf("\n");
    printf("Result of macro function MAX_NUMBER() = %d", iResult);

    //Comparing integer values
    printf("\n\n");
    printf("Enter float fNum1 : ");
    scanf("%f", &fNum1);

    printf("\n");
    printf("Enter float fNum2 : ");
    scanf("%f", &fNum2);

    fResult = MAX_NUMBER(fNum1, fNum2);
    printf("\n");
    printf("Result of macro function MAX_NUMBER() = %f", fResult);

    printf("\n\n");
    return(0);
}
