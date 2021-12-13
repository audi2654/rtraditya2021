//C Functions assignment : User Defined Functions : Methods of Definition - 1
//Program to show different ways of writing definition of a user defined function

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototype/declaration/signature
    void MyAddition(void);

    //code
    MyAddition();   //function call

    return(0);
}

//User Defined Function : Method of Definition - 1
//NO RETURN VALUE, NO PARAMETERS

void MyAddition(void)   //function definition
{
    //local var decl. of MyAddition
    int a, b, amp_sum;

    //code
    printf("\n\n");

    printf("Enter int value for a & b with space in between (like 12 14) : ");
    scanf("%d %d", &a, &b);

    amp_sum = a + b;

    printf("Sum of a & b is %d", amp_sum);

    printf("\n\n"); 
}
