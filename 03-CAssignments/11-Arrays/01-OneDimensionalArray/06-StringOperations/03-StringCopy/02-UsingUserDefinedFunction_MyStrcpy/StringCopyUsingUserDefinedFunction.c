//C Arrays assignment : 1D Array : String operations
//Program to copy a string using user defined function MyStrCpy

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    void MyStrCpy(char[], char[]);

    //var decl.
    char ampChArray_Original[MAX_STRING_LENGTH], ampChArray_Copy[MAX_STRING_LENGTH];   //a character array is a string

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray_Original, MAX_STRING_LENGTH);

    MyStrCpy(ampChArray_Copy, ampChArray_Original);   //string copy user defined function

    printf("\n");
    printf("Original string is : %s\n", ampChArray_Original);
    printf("Copied string is : %s\n\n", ampChArray_Copy);

    return(0);
}

//func definition
void MyStrCpy(char str_destination[], char str_source[])
{
    //func prototype
    int MyStrLen(char[]);

    //var decl.
    int iStringLength = 0;
    int j;

    //code
    iStringLength = MyStrLen(str_source);

    for(j = 0; j < iStringLength; j++)
    {
        str_destination[j] = str_source[j];
    }
    str_destination[j] = '\0';
}

int MyStrLen(char str[])
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    //determining exact length of the string by detecting first '\0' character
    for(j = 0; j < MAX_STRING_LENGTH; j++)
    {
        if(str[j] == '\0')
            break;
        else
            string_length++ ;
    }
    return(string_length);
}
