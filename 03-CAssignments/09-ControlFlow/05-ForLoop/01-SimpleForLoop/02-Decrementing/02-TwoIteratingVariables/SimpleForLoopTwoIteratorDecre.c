//C Control Flow assignment : For Loop
//Program to show working of Decrementing 'for' loop with Two Iterating Variables

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j;

    //code
    printf("\n\n");

    printf("Printing digits from 10 to 1 & from 100 to 10\n");

    for (i = 10, j = 100; i >= 1, j >= 10; i--, j -= 10)
    {
        printf("\t %i \t %i\n", i, j);
    }

    printf("\n\n");

    return(0);
}
