//C Control Flow assignment : Continue Statement-1
//Program to show working of 'continue' using simple loop

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i;

    //code
    printf("\n\n");

    printf("Printing even numbers from 1 to 100\n");

    for(amp_i = 0; amp_i <= 100; amp_i++)
    {
        if(amp_i % 2 != 0)
        {
            continue;
        }
        else
        {
            printf("\t%d\n", amp_i);
        }
    }
    printf("\n\n");

    return(0);
}
