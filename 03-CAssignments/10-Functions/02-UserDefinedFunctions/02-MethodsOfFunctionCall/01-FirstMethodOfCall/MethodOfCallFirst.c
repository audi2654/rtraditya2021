//C Functions assignment : User Defined Functions : Methods of Calling - 1
//Program to show different ways of calling a user defined function

//User Defined Function : Method of Calling - 1
//Calling all functions in main() directly

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototypes/declarations/signatures
    void ampAddition(void);
    int ampSubtraction(void);
    void ampMultiplication(int, int);
    int ampDivision(int, int);

    //var decl.
    int result_subtraction;
    int a_multiplication, b_multiplication;
    int a_division, b_division, result_division;

    //code
    
    //ADDITION
    ampAddition();  //function call

    //SUBTRACTION
    result_subtraction = ampSubtraction();  //function call
    printf("\n\n");
    printf("Subtraction yields result = %d\n", result_subtraction);

    //MULTIPLICATION
    printf("\n\n");
    printf("Enter int value for 'a' for multiplication : ");
    scanf("%d", &a_multiplication);

    printf("\n");
    printf("Enter int value for 'b' for multiplication : ");
    scanf("%d", &b_multiplication);

    ampMultiplication(a_multiplication, b_multiplication); //function call

    //DIVISION
    printf("\n\n");
    printf("Enter int value for 'a' for division : ");
    scanf("%d", &a_division);

    printf("\n");
    printf("Enter int value for 'b' for division : ");
    scanf("%d", &b_division);

    result_division = ampDivision(a_division, b_division);  //function call
    printf("\n\n");
    printf("Division of %d & %d gives = %d (quotient)\n", a_division, b_division, result_division);

    printf("\n");

    return(0);
}

//definition of ampAddition()
void ampAddition(void)
{
    //local var decl. for ampAddition()
    int a, b, amp_sum;

    //code
    printf("\n\n");
    printf("Enter int value for 'a' for addition : ");
    scanf("%d", &a);

    printf("\n");
    printf("Enter int value for 'b' for addition : ");
    scanf("%d", &b);

    amp_sum = a + b;

    printf("\n\n");
    printf("Sum of %d & %d = %d\n", a, b, amp_sum);
}

//definition of ampSubtraction()
int ampSubtraction(void)
{
    //local var decl. for ampSubtraction()
    int a, b, amp_subtraction;

    //code
    printf("\n\n");
    printf("Enter int value for 'a' for subtraction : ");
    scanf("%d", &a);

    printf("\n");
    printf("Enter int value for 'b' for subtraction : ");
    scanf("%d", &b);

    amp_subtraction = a - b;
    return(amp_subtraction);
}

//definition of ampMultiplication()
void ampMultiplication(int a, int b)
{
    //local var decl. for ampMultiplication()
    int amp_multiplication;

    //code
    amp_multiplication = a * b;

    printf("\n\n");
    printf("Multiplication of %d & %d = %d\n", a, b, amp_multiplication);
}

//definition of ampDivision()
int ampDivision(int a, int b)
{
    //local var decl. for ampDivision()
    int division_quotient;

    //code
    if(a > b)
        division_quotient = a / b;
    else
        division_quotient = b / a;

    return(division_quotient);
}
