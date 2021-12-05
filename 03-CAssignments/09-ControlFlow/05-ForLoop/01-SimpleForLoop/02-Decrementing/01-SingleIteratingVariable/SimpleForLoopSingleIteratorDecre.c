//C Control Flow assignment : For Loop
//Program to show working of Decrementing 'for' loop with Single Iterating Variable

#include <stdio.h>

int main(void)
{
    //var decl.
    int i;

    //code
    printf("\n\n");

    printf("Printing digits from 10 to 1\n");

    for (i = 10; i >= 1; i--)
    {
        printf("\t%d\n", i);
    }

    printf("\n\n");

    return(0);
}
