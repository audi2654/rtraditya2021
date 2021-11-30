//C Control Flow assignment : If Statement-4
//Program to show working of if statement & why 'else' was needed

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
    printf("You are NOT eligible for voting\n");    //this will print when above 'if' condition gets FALSE,
    //but this will also get printed even when 'if' condition gets TRUE 
    //& to avoid such unwanted executions, 'else' is needed in such situations

    printf("\n");

    return 0;
}
