//C Control Flow assignment : If Statement-1
//Program to show working of if statement

#include <stdio.h>

int main(void)
{
    //var decl.
    int a, b, p;

    //code
    a = 9;
    b = 30;
    p = 30;

    printf("\n\n");

    printf("a = %d\nb = %d\np = %d\n\n", a, b, p);

    if (a < b)
    {
        printf("a is less than b\n");
    }

    if (b != p)
    {
        printf("b is not equal to p\n");       //doesn't print because b is equal to p 
    }

    printf("Both comparison done!");

    printf("\n\n");

    return 0;
}
