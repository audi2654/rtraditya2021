//C Compound Operator assignment
//Program to show working of compound operators

#include <stdio.h>

int main(void)
{
    //var decl.
    int a;
    int b;
    int x;

    //code
    printf("\n\n");

    printf("Enter a number : ");
    scanf("%d", &a);

    printf("\n");
    printf("Enter another number : ");
    scanf("%d", &b);

    printf("\n");

    //Compound operators also called as Shorthands are usually used when one RHS variable is used repeatedly multiple times

    x = a;  //'x' used as temp var to store the original value of 'a', so as to not loose it
    a += b; //concise form of 'a = a + b'
    printf("Addition : %d + %i = %d\n", x, b, a);

    //continuing with the altered value of 'a' for each of the following operation
    x = a;
    a -= b; //concise form of 'a = a - b'
    printf("Subtraction : %d - %i = %d\n", x, b, a);

    x = a;
    a *= b; //concise form of 'a = a * b'
    printf("Multiplication : %d * %i = %d\n", x, b, a);

    x = a;
    a /= b; //concise form of 'a = a / b'
    printf("Division (Quotient) : %d / %i = %d\n", x, b, a);

    x = a;
    a %= b; //concise form of 'a = a % b'
    printf("Division (Remainder) : %d %% %i = %d\n", x, b, a);

	printf("\n\n");

    return(0);
}
