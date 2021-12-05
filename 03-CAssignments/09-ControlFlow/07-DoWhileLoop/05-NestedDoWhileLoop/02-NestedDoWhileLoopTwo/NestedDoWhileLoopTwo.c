//C Control Flow assignment : Do While Loop
//Program to show working of Nested 'do while' Loop - 2

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j, k;

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
            printf("\t------\n");

            k = 1;
            do
            {
                printf("\t\tk = %d\n", k);
                k++;
            } while (k <= 3);
            printf("\n");
            j++;
        } while (j <= 3);
        i++;
        printf("\n");
    }while(i <= 3);
     

    printf("Total Number of iterations in program : %di * %dj * %ik = %d\n\n", i, j, k, (--i * --j * --k));
    return 0;
}
