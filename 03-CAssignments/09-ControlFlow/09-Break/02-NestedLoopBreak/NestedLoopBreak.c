//C Control Flow assignment : Break Statement-2
//Program to show working of 'break' using simple loop

#include <stdio.h>
#include <conio.h>

int main(void)
{
    //var decl.
    int amp_i, amp_j;

    //code
    printf("\n\n");

    for(amp_i = 1; amp_i <= 20; amp_i++)
    {
        for(amp_j = 1; amp_j <= 20; amp_j++)
        {
            if(amp_j > amp_i)
            {
                break;
            }
            else
            {
                printf("* ");
            }
        }
        printf("\n");
    }
    printf("\n\n");

    return(0);
}
