//C Control Flow assignment : Do While Loop
//Program to show working of Nested 'do while' Loop - 1

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j;

    //code
    printf("\n\n");
    
    i = 1;
    
    do
    {
        printf("i = %d\n", i);
        printf("------\n");

        j = 1;
        do
        {
            printf("\tj = %d\n", j);
            j++;
        } while (j <= 5);
        i++;
        printf("\n\n");
    } while(i <= 10);

    printf("Total Number of iterations in program : %di * %dj = %d\n\n", i, j, (--i * --j));
    return 0;
}
