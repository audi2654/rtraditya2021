//C Arrays assignment : 1D Array : String operations
//Program to reverse a string using user defined function MyStrRev

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    void MyStrRev(char[], char[]);

    //var decl.
    char ampChArray_Original[MAX_STRING_LENGTH], ampChArray_Reversed[MAX_STRING_LENGTH];   //a character array is a string

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray_Original, MAX_STRING_LENGTH);

    MyStrRev(ampChArray_Reversed, ampChArray_Original);   //string reversed user defined function

    printf("\n");
    printf("Original string is : %s\n", ampChArray_Original);
    printf("Reversed string is : %s\n\n", ampChArray_Reversed);

    return(0);
}

//func definition
void MyStrRev(char str_destination[], char str_source[])
{
    //func prototype
    int MyStrLen(char[]);

    //var decl.
    int iStringLength = 0;
    int i, j, len;

    //code
    iStringLength = MyStrLen(str_source);

    //array indices begin from 0 hence last index will always be (length-1)
    len = iStringLength - 1;

    //we need to put the character at last index of str_source to the first index of str_destination & likewise
    for(i = 0, j = len; i < iStringLength, j >= 0; i++, j--)
    {
        str_destination[i] = str_source[j];
    }
    str_destination[i] = '\0';
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
