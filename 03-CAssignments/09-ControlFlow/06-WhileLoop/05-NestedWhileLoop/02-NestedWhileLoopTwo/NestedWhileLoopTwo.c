//C Control Flow assignment : While Loop
//Program to show working of Nested 'while' Loop - 2

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j, k;

    //code
    printf("\n\n");
    
    i = 1;
    while(i <= 4)
    {
        printf("i = %d\n", i);
        printf("------\n");
        
        j = 1;
        while (j <= 4)
        {
            printf("\tj = %d\n", j);
            printf("\t------\n");

            k = 1;
            while (k <= 4)
            {
                printf("\t\tk = %d\n", k);
                k++;
            }
            j++;
            printf("\n");
        }
        i++;
        printf("\n");
    }

    printf("Total Number of iterations in program : %di * %dj * %ik = %d\n\n", i, j, k, (--i * --j * --k));
    return 0;
}
