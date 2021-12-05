//C Control Flow assignment : For Loop
//Program to show working of Nested 'for' Loop - 1

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j;

    //code
    printf("\n\n");
    
    for(i = 1; i <= 10; i++)
    {
        printf("i = %d\n", i);
        printf("------\n");
        for ( j = 1; j <= 5; j++)
        {
            printf("\tj = %d\n", j);
        }
        printf("\n\n");
    }

    printf("Total Number of iterations in program : %di * %dj = %d\n\n", i, j, (--i * --j));
    return 0;
}
