//C Control Flow assignment : While Loop
//Program to print Checkerboard using nested 'while' loop

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j, amp_c;

    //code
    printf("\n\n");
    
    i = 0;
    while(i < 64)    //row
    {
        j = 0;
        while (j < 64)    //column
        {
            amp_c = ((i & 0x8) == 0) ^ ((j & 0x8) == 0);

            if (amp_c == 0)
                printf("  ");

            if (amp_c == 1)
                printf("* ");
            
            j++;
        }
        printf("\n");
        i++;
    }

    printf("\nTotal Number of iterations in program : %di * %dj = %d\n\n", i, j, (i * j));
    
    return 0;
}
