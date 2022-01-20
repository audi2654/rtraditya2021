//C Pointers assignment : Functions - String Operations
//Program to reverse strings using pointers

#include <stdio.h>

#define MAX_STRING_LEN 512

int main(int argc, char* argv[], char *envp[])
{
    //func signature
    void ampStrRev(char*, char *);
    int ampStrLen(char *);

    //var decl
    char *ampChArray_Original = NULL;    //char array can be represented by a char pointer to mark the base addr (char*)
    char *ampChArray_Reversed = NULL;
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

    //string reverse
    iStringLength_Original = ampStrLen(ampChArray_Original);
    ampChArray_Reversed = (char*)malloc(iStringLength_Original * sizeof(char));
    if(ampChArray_Reversed == NULL)
    {
        printf("Memory allocation to REVERSED string FAILED, exiting now\n");
        exit(0);
    }

    //string copy
    ampStrRev(ampChArray_Reversed, ampChArray_Original);

    //string output
    printf("\n\n");
    printf("Original String entered by you is : ");
    printf("%s\n", ampChArray_Original);

    printf("\n\n");
    printf("Reversed String is : ");
    printf("%s\n", ampChArray_Reversed);

    printf("\n\n");

    //release memory
    if(ampChArray_Reversed)
    {
        free(ampChArray_Reversed);
        ampChArray_Reversed = NULL;
        printf("Allocated memory to ampChArray_Reversed FREED\n\n");
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
void ampStrRev(char* str_destination, char *str_source)
{
    //func prototype
    int ampStrLen(char*);

    //var decl.
    int iStringLength = 0;
    int i, j, len;

    //code
    iStringLength = ampStrLen(str_source);

    len = iStringLength - 1;

    for(i = 0, j = len; i < iStringLength, j >= 0; i++, j--)
    {
        *(str_destination + i) = *(str_source + j);
    }
    *(str_destination + i) = '\0';
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
