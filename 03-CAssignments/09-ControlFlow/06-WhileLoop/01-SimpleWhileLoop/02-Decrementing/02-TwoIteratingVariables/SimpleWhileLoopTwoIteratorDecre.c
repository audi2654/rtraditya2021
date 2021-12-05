//C Control Flow assignment : While Loop
//Program to show working of Decrementing 'while' loop with Two Iterating Variables

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i, amp_j;

    //code
    printf("\n\n");

    printf("Printing digits from 10 to 1 & from 100 to 10\n");

    amp_i = 10;
    amp_j = 100;

    while (amp_i >= 1, amp_j >= 10)
    {
        printf("\t %i \t %i\n", amp_i, amp_j);
        amp_i--;
        amp_j -= 10;
    }

    printf("\n\n");

    return(0);
}
