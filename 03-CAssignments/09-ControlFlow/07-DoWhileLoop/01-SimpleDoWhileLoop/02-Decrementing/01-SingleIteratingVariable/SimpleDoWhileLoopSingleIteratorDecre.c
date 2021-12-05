//C Control Flow assignment : Do While Loop
//Program to show working of Decrementing 'do while' loop with Single Iterating Variable

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i;

    //code
    printf("\n\n");

    printf("Printing digits from 10 to 1 using Do-While\n");
    amp_i = 10;
    do
    {
        printf("\t%d\n", amp_i);
        amp_i--;
    }
    while (amp_i >= 1);

    printf("\n\n");

    return(0);
}
