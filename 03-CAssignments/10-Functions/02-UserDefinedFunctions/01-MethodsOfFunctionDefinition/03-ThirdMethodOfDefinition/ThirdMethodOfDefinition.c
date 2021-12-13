//C Functions assignment : User Defined Functions : Methods of Definition - 3
//Program to show different ways of writing definition of a user defined function

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototype/declaration/signature
    void MyAddition(int, int);

    //local var decl. for main()
    int a, b;

    //code
    printf("\n\n");

    printf("Enter the int value for a & b (like 28 35) : ");
    scanf("%d %d", &a, &b);

    MyAddition(a, b);  //function call

    return(0);
}

//User Defined Function : Method of Definition - 3
//NO RETURN VALUE, 2 VALID PARAMETERS (int, int)

void MyAddition(int x, int y)   //function definition
{
    //local var decl. for MyAddition()
    int amp_sum;

    //code
    amp_sum = x + y;
    printf("\n");
    printf("Sum of %d & %d is %d\n", x, y, amp_sum);
}
