//C Control Flow assignment : Do While Loop
//Program to show working of Incrementing 'do while' loop with Two Iterating Variables

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i, amp_j;

    //code
    printf("\n\n");

    printf("Printing digits from 1 to 10 & from 10 to 100 using Do-While\n");

    amp_i = 1;
    amp_j = 10;

    do
    {
        printf("\t %d \t %d\n", amp_i, amp_j);
        amp_i++;
        amp_j = amp_j + 10;
    }
    while (amp_i <= 10, amp_j <= 100);

    printf("\n\n");

    return(0);
}
