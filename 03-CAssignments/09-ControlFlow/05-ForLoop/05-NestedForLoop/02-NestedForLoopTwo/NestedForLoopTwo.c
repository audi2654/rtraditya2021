//C Control Flow assignment : For Loop
//Program to show working of Nested 'for' Loop - 2

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j, k;

    //code
    printf("\n\n");
    
    for(i = 1; i <= 3; i++)
    {
        printf("i = %d\n", i);
        printf("------\n");
        for ( j = 1; j <= 3; j++)
        {
            printf("\tj = %d\n", j);
            printf("\t------\n");
            for ( k = 1; k <= 3; k++)
            {
                printf("\t\tk = %d\n", k);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("Total Number of iterations in program : %di * %dj * %ik = %d\n\n", i, j, k, (--i * --j * --k));
    return 0;
}
