//C Functions assignment : Entry Point Function - 6B
//Program to show working of cmd line args given to entry point function

#include <stdio.h>  //for printf()
#include <stdlib.h> //for exit()

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int i;

    //code
    if(argc != 4)   //Program name + First Name + Middle Name + Surname = 4 Cmd Line Args are required
    {
        printf("\n\n");
        printf("Invalid usage! Exiting now\n");
        printf("Usage: CmdLineArgsAppOne.exe <first_name> <middle_name> <surname>\n\n");
        exit(0);
    }

    //This program prints your full name as given in cmd line args

    printf("\n\n");

    for(i = 1; i < argc; i++) //here loop for argc starts for from i = 1 because, i = 0 will result in 'argv[i]' = 'argv[0]'
    //which is the name of the program itself
    {
        printf("%s ", argv[i]);
    }

    printf("\n\n");

    return(0);
}
