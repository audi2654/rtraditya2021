//C Arrays assignment : 1D Array : String operations
//Program to show length of a string using library function strlen

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char ampChArray[MAX_STRING_LENGTH];   //a character array is a string
    int ampStringLength = 0;

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("Entered string is : %s\n\n", ampChArray);

    //string length
    ampStringLength = strlen(ampChArray);
    printf("Length of String = %d character\n\n", ampStringLength);

    return(0);
}
