//C Bitwise Operators assign.
//Program to show working of Bitwise Right Shift(>>) operator

#include <stdio.h>

int main(void)
{
    //function prototypes
    void PrintBinaryFormOfNumber(unsigned int);

    //var decl.
    unsigned int a;
    unsigned int num_bits;
    unsigned int result;

    //code
    printf("\n\n");

    printf("Enter an int : ");
    scanf("%u", &a);

    printf("\n");
    printf("By how many bits do you want a = %d to shift right ? : ", a);
    scanf("%u", &num_bits);

    printf("\n\n");

    result = a >> num_bits;     //Bitwise Right Shift using >>
    printf("Bitwise Right Shifting of a = %d (decimal) by %d bits gives Result = %d (decimal)\n\n", a, num_bits, result);

    PrintBinaryFormOfNumber(a);
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
