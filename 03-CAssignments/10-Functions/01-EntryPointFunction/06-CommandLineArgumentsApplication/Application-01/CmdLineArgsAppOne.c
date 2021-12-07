//C Functions assignment : Entry Point Function - 6A
//Program to show working of cmd line args given to entry point function

#include <stdio.h>  //for printf()
#include <ctype.h>  //for atoi()
#include <stdlib.h> //for exit()

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int i;
    int amp_num = 0;
    int amp_sum = 0;

    //code
    if(argc == 1)
    {
        printf("\n\n");
        printf("No numbers given for Addition! Exiting now\n");
        printf("Usage: CmdLineArgsAppOne.exe <first_number> <second_number>\n\n");
        exit(0);
    }

    //This program add all cmd line args given in integer form only & outputs the sum
    //Due to use of atoi(), all cmd line agrs of types other than 'int' are ignored

    printf("\n\n");

    for(i = 1; i < argc; i++) //here loop starts from i = 1 because, i = 0 will result in 'argv[i]' = 'argv[0]'
    //which is the name of the program itself
    {
        amp_num = atoi(argv[i]);
        amp_sum = amp_sum + amp_num;
    }
    printf("Sum of all int cmd line args is : %d\n\n", amp_sum);

    return(0);
}
