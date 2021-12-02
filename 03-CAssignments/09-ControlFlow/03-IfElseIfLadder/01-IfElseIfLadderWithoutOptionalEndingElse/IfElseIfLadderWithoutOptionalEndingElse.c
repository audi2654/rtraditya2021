//C Control Flow assignment : If-Else Ladder-1
//Program to show working of if else ladder without optional ELSE

#include <stdio.h>

int main(void)
{
    //var decl.
    int num;

    //code
    printf("\n\n");

    printf("Enter num : ");
    scanf("%d", &num);

    //If-Else Ladder begins from here
    if (num < 0)
        printf("num = %d is less than 0 (NEGATIVE)\n", num);
    
    else if (num == 0)
        printf("num = %d is equal to 0\n", num);

    else if ((num > 0) && (num <= 100))
        printf("num = %d is between 0 & 100\n", num);

    else if ((num > 100) && (num <= 200))
        printf("num = %d is between 100 & 200\n", num);

    else if ((num > 200) && (num <= 300))
        printf("num = %d is between 200 & 300\n", num);

    else if ((num > 300) && (num <= 400))
        printf("num = %d is between 300 & 400\n", num);

    else if ((num > 400) && (num <= 500))
        printf("num = %d is between 400 & 500\n", num);

    else if (num > 500)
        printf("num = %d is greater than 500\n", num);
        
    //note : no terminating ELSE used in this ladder

    printf("\n\n");

    return 0;
}
