//C Goto assignment : goto statement
//Program to show how goto statement works

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv, char** envp)
{
    //var decl.
    char ch, ch_i;
    unsigned int ascii_ch = 0;

    //code
    printf("\n\n");
    printf("Enter the first character of First Name : ");
    ch = getch();
    printf("%c", ch);

    ch = toupper(ch);

    for(ch_i = 'A'; ch_i <= 'Z'; ch_i++)
    {
        if(ch == ch_i)
        {
            ascii_ch = (unsigned int)ch;
            goto result_output; //program flow jumps directly to label 'result_output'
        }
    }

    printf("\n\n");
    printf("Goto statement not executed, so printing Hello World\n"); //will not execute if goto executes

    result_output:  //label itself doesn't alter the flow of program, following code will execute regardless
    //of whether goto statement is executed or not
    printf("\n\n");

    if(ascii_ch == 0)
    {
        printf("No english alphabet found, try between A-Z", ch);
    }
    else
    {
        printf("Character '%c' found, it has ASCII value %u\n", ch, ascii_ch);
    }

    printf("\n\n");
    return(0);
}
