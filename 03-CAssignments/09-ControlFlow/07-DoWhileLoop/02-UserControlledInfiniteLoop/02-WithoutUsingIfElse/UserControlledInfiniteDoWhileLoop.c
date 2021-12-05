//C Control Flow assignment : Do While Loop
//Program to show working of User Controlled Infinite 'while' Loop without using IfElse

#include <stdio.h>

int main(void)
{
    //var decl.
    char amp_option, amp_ch = '\0';

    //code
    printf("\n\n");

    printf("Once the infinite loop starts, press 'Q' or 'q' to quit the loop\n\n");
    printf("Enter 'Y' or 'y' to start infinite loop : ");
    amp_option = getch();

    do
    {
        do
        {
            printf("In loop...\n");
            amp_ch = getch();
            if(amp_ch == 'Q' || amp_ch == 'q')
                break;  //Breaking & exiting infinite loop
        }
        while(1); //Infinite Loop

        printf("\nExiting user controlled infinite loop\n\n");

        printf("\nPress 'Y' or 'y' to begin the infinite loop again or Any other key to Quit : ");
        amp_option = getch();
    }
    while (amp_option == 'Y' || amp_option == 'y');

    return(0);
}
