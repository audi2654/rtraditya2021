//C Control Flow assignment : Do While Loop
//Program to print Checkerboard using nested 'do while' loop

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j, amp_c;

    //code
    printf("\n\n");
    
    i = 0;
    do
    {
        j = 0;
        do
        {
            amp_c = ((i & 0x8) == 0) ^ ((j & 0x8) == 0);

            if (amp_c == 0)
                printf("  ");

            if (amp_c == 1)
                printf("* ");
            
            if (j == 63 && amp_c == 1)  //adding boundary on right side
                printf("|");

            if (j == 63 && amp_c == 0)  //adding boundary on right side
                printf("|");

            j++;
        }while (j < 64);    //column
        printf("\n");
        i++;
    }while(i < 64);    //row

    printf("\nTotal Number of iterations in program : %di * %dj = %d\n\n", i, j, (i * j));
    
    return 0;
}
