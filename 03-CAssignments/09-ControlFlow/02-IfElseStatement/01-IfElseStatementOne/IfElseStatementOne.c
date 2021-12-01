//C Control Flow assignment : If-Else Statement-1
//Program to show working of if else statement

#include <stdio.h>

int main(void)
{
    //var decl.
    int a, b, p;

    //code
    a = 9;
    b = 30;
    p = 30;

    //First if-else pair
    printf("\n\n");

    printf("a = %d\nb = %d\np = %d\n\n", a, b, p);

    if (a < b)
    {
        printf("Entering 1st IF-block : a is less than b\n");
    }
    else
    {
        printf("Entering 1st ELSE-block : a is NOT less than b\n");
    }
    printf("1st if-else pair done!");


    //Second if-else pair
    printf("\n\n");

    if (b != p)
    {
        printf("Entering 2nd IF-block : b is NOT equal to p\n");
    }
    else
    {
        printf("Entering 2nd ELSE-block : b is equal to p\n");
    }

    printf("2nd if-else pair done!\n\n");

    return 0;
}
