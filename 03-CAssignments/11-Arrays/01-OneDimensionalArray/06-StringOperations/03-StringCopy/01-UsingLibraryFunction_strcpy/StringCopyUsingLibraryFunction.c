//C Arrays assignment : 1D Array : String operations
//Program to copy a string using library function strcpy

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char ampChArray_Original[MAX_STRING_LENGTH], ampChArray_Copy[MAX_STRING_LENGTH];   //a character array is a string

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray_Original, MAX_STRING_LENGTH);

    strcpy(ampChArray_Copy, ampChArray_Original);   //string copy library function

    printf("\n");
    printf("Original string is : %s\n", ampChArray_Original);
    printf("Copied string is : %s\n\n", ampChArray_Copy);

    return(0);
}
