//C Functions assignment : Entry Point Function - 5
//Program to show working of a simple entry point function & different ways to write it

#include <stdio.h>  //'stdio.h' header file contains declaration of 'printf()'

int main(int argc, char *argv[], char *envp[])     //Entry Point Function with Valid Return Type & 3 Parameters
{   
    //var decl.
    int i;

    //code
    printf("\n\n");
    printf("Hello World\n");    //Library Function from stdio.h

    printf("Number of Command Line Arguments = %d\n\n", argc);  //By default name of the file itself is considered as 1 cmd line arg

    printf("Command Line Arguments passed to this program are\n");
    for (i = 0; i < argc; i++)
    {
        printf("Command Line Arg Number %d = %s\n", (i+1), argv[i]);
    }
    printf("\n\n");

    printf("First 20 Environmental Variables passed to this program are\n");
    for (i = 0; i < 20; i++)
    {
        printf("Environmental Variable Number %d = %s\n", (i+1), envp[i]);
    }
    printf("\n\n");
    
    return 0;
}
