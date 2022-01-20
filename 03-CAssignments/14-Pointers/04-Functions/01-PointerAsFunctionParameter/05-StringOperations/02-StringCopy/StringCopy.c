//C Pointers assignment : Functions - String Operations
//Program to copy strings using pointers

#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 512

int main(int argc, char* argv[], char *envp[])
{
    //func signature
    void ampStrCopy(char*, char *);
    int ampStrLen(char *);

    //var decl
    char *ampChArray_Original = NULL;    //char array can be represented by a char pointer to mark the base addr (char*)
    char *ampChArray_Copy = NULL;   //a char array is a string
    int iStringLength_Original = 0;

    //code
    printf("\n\n");
    ampChArray_Original = (char *)malloc(MAX_STRING_LEN * sizeof(char));
    if(ampChArray_Original == NULL)
    {
        printf("Memory allocation to ORIGINAL string FAILED, exiting now\n");
        exit(0);
    }

    //string input
    printf("Enter a string : ");
    gets_s(ampChArray_Original, MAX_STRING_LEN);

    iStringLength_Original = ampStrLen(ampChArray_Original);
    
    ampChArray_Copy = (char*)malloc(iStringLength_Original * sizeof(char));
    if(ampChArray_Copy == NULL)
    {
        printf("Memory allocation to COPIED string FAILED, exiting now\n");
        exit(0);
    }

    //string copy
    ampStrCopy(ampChArray_Copy, ampChArray_Original);

    //string output
    printf("\n\n");
    printf("Original String entered by you is : ");
    printf("%s\n", ampChArray_Original);

    printf("\n\n");
    printf("Copied String is : ");
    printf("%s\n", ampChArray_Copy);

    printf("\n\n");

    //release memory
    if(ampChArray_Copy)
    {
        free(ampChArray_Copy);
        ampChArray_Copy = NULL;
        printf("Allocated memory to ampChArray_Copy FREED\n\n");
    }

    if(ampChArray_Original)
    {
        free(ampChArray_Original);
        ampChArray_Original = NULL;
        printf("Allocated memory to ampChArray_Original FREED\n\n");
    }

    return(0);
}

//func definition
void ampStrCopy(char* str_destination, char *str_source)
{
    //func prototype
    int ampStrLen(char*);

    //var decl.
    int iStringLength = 0;
    int j;

    //code
    iStringLength = ampStrLen(str_source);
    for(j = 0; j < iStringLength; j++)
        *(str_destination + j) = *(str_source + j);

    *(str_destination + j) = '\0';
}

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
