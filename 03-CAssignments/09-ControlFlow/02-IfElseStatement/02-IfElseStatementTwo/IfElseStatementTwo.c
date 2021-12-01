//C Control Flow assignment : If-Else Statement-2
//Program to show working of if else statement

#include <stdio.h>

int main(void)
{
    //var decl.
    int age;

    //code
    printf("\n\n");

    printf("Enter age : ");
    scanf("%d", &age);

    if (age >= 18)
    {
        printf("Entering IF-block : You are eligible for voting\n");
    }
    else
    {
        printf("Entering ELSE-block : You are NOT eligible for voting\n");
    }

    printf("Byeeeee\n\n");

    return 0;
}
