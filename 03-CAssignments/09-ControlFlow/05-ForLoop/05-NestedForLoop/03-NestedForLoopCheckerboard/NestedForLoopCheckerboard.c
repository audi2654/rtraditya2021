//C Control Flow assignment : For Loop
//Program to print Checkerboard using nested 'for' loop

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j, amp_c;

    //code
    printf("\n\n");
    
    for(i = 0; i < 64; i++)    //row
    {
        for ( j = 0; j < 64; j++)    //column
        {
            amp_c = ((i & 0x8) == 0) ^ ((j & 0x8) == 0);

            if (amp_c == 0)
                printf("  ");

            if (amp_c == 1)
                printf("* ");
        }
        printf("\n");
    }

    printf("\nTotal Number of iterations in program : %di * %dj = %d\n\n", i, j, (i * j));
    
    return 0;
}
