//C Control Flow assignment : While Loop
//Program to show working of Nested 'while' Loop - 1

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j;

    //code
    printf("\n\n");
    
    i = 1;
    while(i <= 10)
    {
        printf("i = %d\n", i);
        printf("------\n");

        j = 1;
        while (j <= 5)
        {
            printf("\tj = %d\n", j);
            j++;
        }
        i++;
        printf("\n\n");
    }

    printf("Total Number of iterations in program : %di * %dj = %d\n\n", i, j, (--i * --j));
    return 0;
}
