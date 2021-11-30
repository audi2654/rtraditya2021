//C Bitwise Operators assign.
//Program to show working of Bitwise OR(|) operator

#include <stdio.h>

int main(void)
{
    //function prototypes
    void PrintBinaryFormOfNumber(unsigned int);

    //var decl.
    unsigned int a;
    unsigned int b;
    unsigned int result;

    //code
    printf("\n\n");

    printf("Enter 1st int : ");
    scanf("%u", &a);
    printf("Enter 2nd int : ");
    scanf("%u", &b);

    printf("\n\n");

    result = a | b;     //Bitwise ORing
    printf("Bitwise ORing of a = %d (decimal) and b = %d (decimal) gives Result = %d (decimal)\n\n", a, b, result);

    PrintBinaryFormOfNumber(a);
    PrintBinaryFormOfNumber(b);
    PrintBinaryFormOfNumber(result);

    return(0);
}

void PrintBinaryFormOfNumber(unsigned int decimal_number)
{
    //var decl.
    unsigned int quotient, remainder;
    unsigned int num = 0;
    unsigned int binary_array[8];
    int i;

    //code
    for (i = 0; i < 8; i++)             //initializing the array elements
    {
        binary_array[i] = 0;
    }

    printf("Decimal int = %d, Binary form = ", decimal_number);
    
    num = decimal_number;
    i = 7;
    while (num != 0)
    {
        quotient = num / 2;
        remainder = num % 2;
        binary_array[i] = remainder;
        num = quotient;
        i--;
    }

    for (i = 0; i < 8; i++)
    {
        printf("%u", binary_array[i]);
    }
    printf("\n\n");
}
