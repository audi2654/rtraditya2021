//C Arrays assignment : 1D Array : String operations
//Program for concatenation of a string using library function strcat

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char ampChArray_One[MAX_STRING_LENGTH], ampChArray_Two[MAX_STRING_LENGTH];   //a character array is a string

    //code
    printf("\n\n");
    printf("Enter first string : ");
    gets_s(ampChArray_One, MAX_STRING_LENGTH);

    printf("\n");
    printf("Enter second string : ");
    gets_s(ampChArray_Two, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("Before Concatenation\n");
    printf("First string is : %s\n", ampChArray_One);
    printf("Second string is : %s\n", ampChArray_Two);

    strcat(ampChArray_One, ampChArray_Two);     //string concatenation library function

    printf("\n");
    printf("After Concatenation\n");
    printf("First string is : %s\n", ampChArray_One);       //concatenates with string 2
    printf("Second string is : %s\n", ampChArray_Two);      //remains as it is

    return(0);
}
