//C Control Flow assignment : For Loop
//Program to show working of User Controlled Infinite 'for' Loop

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

    if (amp_option == 'Y' || amp_option == 'y')
    {
        for(;;) //Infinite Loop
        {
            printf("In loop...\n");
            amp_ch = getch();
            if(amp_ch == 'Q' || amp_ch == 'q')
                break;  //Breaking & exiting infinite loop
        }
    }

    printf("\nExiting user controlled infinite loop\n\n");

    return(0);
}
