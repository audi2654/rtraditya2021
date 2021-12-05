//C Control Flow assignment : While Loop
//Program to show working of Decrementing 'while' loop with Single Iterating Variable

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i;

    //code
    printf("\n\n");

    printf("Printing digits from 10 to 1\n");
    amp_i = 10;
    while (amp_i >= 1)
    {
        printf("\t%d\n", amp_i);
        amp_i--;
    }

    printf("\n\n");

    return(0);
}
