//C Control Flow assignment : Switch Case-3B
//Math Operations program using if elseif else ladder

#include <stdio.h>  //for printf()
#include <conio.h>  //MS DOS Windows compiler specific header file for getch(), won't work on Linux

int main(void)
{
    //var decl.
    int a, b;
    int amp_result;
    char amp_option, amp_option_division;

    //code
    printf("\n\n");

    printf("Enter numbers\n");
    printf("Enter value for a : ");
    scanf("%d", &a);

    printf("Enter value for b : ");
    scanf("%d", &b);

    printf("\n----MATH OPERATIONS OPTIONS----\n");
    printf("'A' or 'a' for Addition\n");
    printf("'S' or 's' for Subtration\n");
    printf("'M' or 'm' for Multiplication\n");
    printf("'D' or 'd' for Division\n");


    printf("Enter option in character : ");
    amp_option = getch();

    printf("\n\n");

    if (amp_option == 'A' || amp_option == 'a')
    {
        amp_result = a + b;
        printf("Addition of a = %d & b = %d is Result = %d\n", a, b, amp_result);
    }
    else if(amp_option == 'S' || amp_option == 's')
    {
        if (a >= b)
        {
            amp_result = a - b;
            printf("Subtraction of b = %d from a = %d is Result = %d\n", b, a, amp_result);
        }
        else
        {
            amp_result = b - a;
            printf("Subtraction of a = %d from b = %d is Result = %d\n", a, b, amp_result);
        }
    }
    else if (amp_option == 'M' || amp_option == 'm')
    {
        amp_result = a * b;
        printf("Multiplication of a = %d & b = %d is Result = %d\n", a, b, amp_result);
    }
    else if (amp_option == 'D' || amp_option == 'd')
    {
        printf("--DIVISION OPTIONS--\n");
        printf("'Q' or 'q' or '/' for Quotient upon Division\n");
        printf("'R' or 'r' or '%%' for Remainder upon Division\n");

        printf("Enter Division option in char : ");
        amp_option_division = getch();

        printf("\n\n");

        if(amp_option_division == 'Q' || amp_option_division == 'q' || amp_option_division == '/')
        {
            if (a >= b)
            {
                amp_result = a / b;
                printf("Division of a = %d by b = %d gives Quotient = %d\n", a, b, amp_result);
            }
            else
            {
                amp_result = b / a;
                printf("Division of b = %d by a = %d gives Quotient = %d\n", b, a, amp_result);
            }
        }
        else if(amp_option_division == 'R' || amp_option_division == 'r' || amp_option_division == '%')
        {
            if (a >= b)
            {
                amp_result = a % b;
                printf("Division of a = %d by b = %d gives Remainder = %d\n", a, b, amp_result);
            }
            else
            {
                amp_result = b % a;
                printf("Division of b = %d by a = %d gives Remainder = %d\n", b, a, amp_result);
            }
        }
        else
        {
            printf("Invalid option char \'%c\' entered for Division\n", amp_option_division);
        }
    }
    else
    {
        printf("Invalid option char '%c' entered for Math Operations\n", amp_option);
    }

    printf("\nIfElseIf Ladder complete\n\n");

    return 0;
}
