//C Operators Assignment
//Program to show 5 arithmetic operators in C

#include <stdio.h>

int main(void)
{
    //variable decl.
    int a;
    int b;
    int amp_result;

    //code
    printf("\n\n");
    printf("Enter a number : ");
    scanf("%d", &a);

    printf("\n");
    printf("Enter another number : ");
    scanf("%d", &b);

    printf("\n");

    //5 arithmetic operators are : +,-,*,/ & %

    amp_result = a + b;
    printf("Addition : %d + %i = %d\n", a, b, amp_result);

    amp_result = a - b;
    printf("Subtraction : %d - %i = %d\n", a, b, amp_result);

    amp_result = a * b;
    printf("Multiplication : %d * %i = %d\n", a, b, amp_result);

    amp_result = a / b;
    printf("Division : %d / %i = %d (Quotient from Division)\n", a, b, amp_result);

    amp_result = a % b;
    printf("Modulus : %d + %i = %d (Remainder from Division)\n", a, b, amp_result);

    printf("\n\n");

    return(0);
}
