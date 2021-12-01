//C Control Flow assignment : If Statement-3
//Program to show working of if statement

#include <stdio.h>

int main(void)
{
    //var decl.
    int num;

    //code
    printf("\n\n");

    printf("Enter num : ");
    scanf("%d", &num);

    if (num < 0)
    {
        printf("num = %d is less than 0 (NEGATIVE)\n", num);
    }

    if (num == 0)
    {
        printf("Entered number is 0\n");
    }

    if ((num > 0) && (num <= 100))
    {
        printf("num = %d is between 0 & 100\n", num);
    }

    if ((num > 100) && (num <= 200))
    {
        printf("num = %d is between 100 & 200\n", num);
    }

    if ((num > 200) && (num <= 300))
    {
        printf("num = %d is between 200 & 300\n", num);
    }

    if ((num > 300) && (num <= 400))
    {
        printf("num = %d is between 300 & 400\n", num);
    }

    if ((num > 400) && (num <= 500))
    {
        printf("num = %d is between 400 & 500\n", num);
    }

    if (num > 500)
    {
        printf("num = %d is greater than 500\n", num);
    }
    
    printf("\n");

    return 0;
}
