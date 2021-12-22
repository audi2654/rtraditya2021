//C Arrays assignment : 1D Array : String operations
//Program to show how to input & output a string

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char ampChArray[MAX_STRING_LENGTH];   //a character array is a string

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("Entered string is : %s\n\n", ampChArray);

    return(0);
}
