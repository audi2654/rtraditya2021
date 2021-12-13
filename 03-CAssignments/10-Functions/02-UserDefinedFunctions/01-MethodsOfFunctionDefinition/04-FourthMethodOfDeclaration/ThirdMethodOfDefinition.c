//C Functions assignment : User Defined Functions : Methods of Definition - 4
//Program to show different ways of writing definition of a user defined function

#include <stdio.h>
int main(int argc, char *argv[], char *envp[])
{
    //function prototype/declaration/signature
    int MyAddition(int, int);

    //local var decl. for main()
    int a, b, amp_result;

    //code
    printf("\n\n");

    printf("Enter the int value for a & b (like 28 35) : ");
    scanf("%d %d", &a, &b);

    amp_result = MyAddition(a, b);  //function call

    printf("\n\n");

    printf("Sum of %d & %d is %d\n", a, b, amp_result);

    return 0;
}

//User Defined Function : Method of Definition - 4
//VALID RETURN VALUE (int), 2 VALID PARAMETERS (int, int)

int MyAddition(int m, int n)   //function definition
{
    //local var decl. for MyAddition()
    int amp_sum;

    //code
    amp_sum = m + n;
    
    return(amp_sum);
}
