//C Functions assignment : User Defined Functions : Methods of Definition - 2
//Program to show different ways of writing definition of a user defined function

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototype/declaration/signature
    int MyAddition(void);

    //local var decl. for main()
    int amp_result;

    //code
    printf("\n\n");

    amp_result = MyAddition();  //function call

    printf("Sum of a & b is %d\n", amp_result);

    printf("\n\nCalling function again directly through printf\n");
    printf("Sum of a & b is %d\n", MyAddition());     //another way to call function & catch the return value

    return(0);
}

//User Defined Function : Method of Definition - 2
//VALID (int) RETURN VALUE, NO PARAMETERS

int MyAddition(void)   //function definition
{
    //local var decl. for MyAddition()
    int a, b, amp_sum;

    //code

    printf("Enter the int value for a & b (like 28 35) : ");
    scanf("%d %d", &a, &b);

    amp_sum = a + b;

    //return(amp_sum);
    //return(a+b);
    //return amp_sum;
    return a+b;
}
