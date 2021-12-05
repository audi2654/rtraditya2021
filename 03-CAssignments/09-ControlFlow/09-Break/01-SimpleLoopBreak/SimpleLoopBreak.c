//C Control Flow assignment : Break Statement-1
//Program to show working of 'break' using simple loop

#include <stdio.h>
#include <conio.h>

int main(void)
{
    //var decl.
    int amp_i;
    char amp_ch;

    //code
    printf("\n\n");

    printf("Printinf EVEN nums from 1 to 100 for every user input. Exiting the loop when user press 'Q' or 'q'\n");
    printf("Press 'Q' or 'q' to exit loop\n");

    for(amp_i = 1; amp_i <= 100; amp_i++)
    {
        printf("\t%d\n", amp_i);
        amp_ch = getch();
        if(amp_ch == 'Q' || amp_ch == 'q')
        {
            break;
        }
    }

    printf("\n\n");
    printf("Exiting loop\n");

    return 0;
}
