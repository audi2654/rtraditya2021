//C Control Flow assignment : For Loop
//Program to show working of Incrementing 'for' loop with Two Iterating Variables

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j;

    //code
    printf("\n\n");

    printf("Printing digits from 1 to 10 & from 10 to 100\n");

    for (i = 1, j = 10; i <= 10, j <= 100; i++, j = j + 10)
    {
        printf("\t %d \t %d\n", i, j);
    }

    printf("\n\n");

    return(0);
}
