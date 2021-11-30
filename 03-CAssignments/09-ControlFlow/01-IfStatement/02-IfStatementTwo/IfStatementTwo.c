//C Control Flow assignment : If Statement-2
//Program to show working of if statement

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
        printf("You are eligible for voting\n");
    }

    printf("\n");

    return 0;
}
