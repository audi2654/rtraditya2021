//C Arrays assignment : 1D Array : String operations
//Program to reverse a string using library function strrev

#include <stdio.h>
#include <string.h>  //for strrev()

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char ampChArray_Original[MAX_STRING_LENGTH], ampChArray_Reverse[MAX_STRING_LENGTH];   //a character array is a string

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray_Original, MAX_STRING_LENGTH);

    printf("\n");
    printf("Original string is : %s\n", ampChArray_Original);

    strcpy(ampChArray_Reverse,strrev(ampChArray_Original));   //string reverse library function

    printf("Reversed string is : %s\n", ampChArray_Reverse);

    printf("Re-Reversed string is : %s\n\n", strrev(ampChArray_Reverse));

    return(0);
}
