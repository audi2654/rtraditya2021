//C Pointers assignment : Functions - String Operations
//Program to determine string length using pointers

#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 512

int main(int argc, char* argv[], char *envp[])
{
    //func signature
    int ampStrLen(char *);

    //var decl
    char *ampChArray = NULL;    //char array can be represented by a char pointer to mark the base addr (char*)
    int iStringLength = 0;

    //code
    printf("\n\n");
    ampChArray = (char *)malloc(MAX_STRING_LEN * sizeof(char));
    if(ampChArray == NULL)
    {
        printf("Memory allocation to char array FAILED, exiting now\n");
        exit(0);
    }

    //string input
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LEN);

    //string output
    printf("\n\n");
    printf("String entered by you is : ");
    printf("%s\n", ampChArray);

    //string length
    printf("\n\n");
    iStringLength = ampStrLen(ampChArray);
    printf("Length of string is : %d characters\n\n", iStringLength);

    if(ampChArray)
    {
        free(ampChArray);
        ampChArray = NULL;
        printf("Allocated memory to ampChArray FREED\n\n");
    }

    return(0);
}

//func definition
int ampStrLen(char *str)
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    //determining exact lenght of string by detecting the first occurrence of null terminating char (\0)
    for(j = 0; j < MAX_STRING_LEN; j++)
    {
        if(*(str + j) == '\0')
            break;
        else
            string_length++;
    }
    return(string_length);
}
