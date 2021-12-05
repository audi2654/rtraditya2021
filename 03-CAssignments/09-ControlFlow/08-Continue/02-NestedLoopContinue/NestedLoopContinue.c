//C Control Flow assignment : Continue Statement-2
//Program to show working of 'continue' using nested loop

#include <stdio.h>

int main(void)
{
    //var decl.
    int amp_i, amp_j;

    //code
    printf("\n\n");

    printf("Outer loop prints ODD nums between 1 to 10\n");
    printf("Inner loop prints EVEN nums between 1 to 10 for every ODD num printed by Outer loop\n");

    for(amp_i = 1; amp_i <=10; amp_i++)
    {
        if(amp_i % 2 != 0)  //if i is ODD
        {
            printf("i = %d\n", amp_i);
            printf("-------\n");
            for(amp_j = 1; amp_j <= 10; amp_j++)
            {
                if (amp_j % 2 == 0)  //if j is EVEN
                {
                    printf("\tj = %d\n", amp_j);
                }
                else  //if j is ODD
                {
                    continue;
                }
            }
            printf("\n\n");
        }
        else  //if i is EVEN
        {
            continue;
        }
    }
    
    printf("\n\n");

    return 0;
}
