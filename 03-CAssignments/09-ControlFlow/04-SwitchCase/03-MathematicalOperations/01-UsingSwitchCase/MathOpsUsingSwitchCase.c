//C Control Flow assignment : Switch Case-3A
//Math Operations program to show working of switch statement & how it is similar to if elseif else ladder

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

    switch (amp_option)
    {
    //Using FALL THROUGH condition for each option to reduce no. of comparisons
    case 'A':
    case 'a':
        amp_result = a + b;
        printf("Addition of a = %d & b = %d is Result = %d\n", a, b, amp_result);
        break;

    case 'S':
    case 's':
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
        break;
    
    case 'M':
    case 'm':
        amp_result = a * b;
        printf("Multiplication of a = %d & b = %d is Result = %d\n", a, b, amp_result);
        break;

    case 'D':
    case 'd':
        printf("--DIVISION OPTIONS--\n");
        printf("'Q' or 'q' or '/' for Quotient upon Division\n");
        printf("'R' or 'r' or '%%' for Remainder upon Division\n");

        printf("Enter Division option in char : ");
        amp_option_division = getch();

        printf("\n\n");

        switch (amp_option_division)
        {
        case 'Q':
        case 'q':
        case '/':
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
            break;

        case 'R':
        case 'r':
        case '%':
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
            break;
        
        default:
            printf("Invalid option char \'%c\' entered for Division\n", amp_option_division);
            break;
        }   //ending switch of Division options
        
        break;

    default:
        printf("Invalid option char '%c' entered for Math Operations\n", amp_option);
        break;
    }

    printf("\nSwitch case block complete\n\n");

    return 0;
}
