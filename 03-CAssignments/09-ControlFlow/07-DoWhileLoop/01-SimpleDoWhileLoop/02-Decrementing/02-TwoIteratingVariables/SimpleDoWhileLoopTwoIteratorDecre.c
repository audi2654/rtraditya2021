//C Control Flow assignment : Do While Loop
//Program to show working of Decrementing 'do while' loop with Two Iterating Variables

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i, amp_j;

    //code
    printf("\n\n");

    printf("Printing digits from 10 to 1 & from 100 to 10 using Do-While\n");

    amp_i = 10;
    amp_j = 100;

    do
    {
        printf("\t %i \t %i\n", amp_i, amp_j);
        amp_i--;
        amp_j -= 10;
    }
    while (amp_i >= 1, amp_j >= 10);

    printf("\n\n");

    return(0);
}
