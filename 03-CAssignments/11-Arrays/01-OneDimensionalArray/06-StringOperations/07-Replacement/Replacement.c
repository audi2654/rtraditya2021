//C Arrays assignment : 1D Array : String operations
//Program to replace all vowels in a string with *

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int MyStrLen(char[]);
    void MyStrCpy(char[], char[]);

    //var decl.
    char ampChArray_Original[MAX_STRING_LENGTH], ampChArray_Replaced[MAX_STRING_LENGTH];     //a char array is a string
    int iStringLength;
    int i;

    //code
    //string input
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray_Original, MAX_STRING_LENGTH);

    //string output
    printf("\n\n");

    MyStrCpy(ampChArray_Replaced, ampChArray_Original);

    iStringLength = MyStrLen(ampChArray_Replaced);
    
    for(i = 0; i < iStringLength; i++)
    {
        switch(ampChArray_Replaced[i])
        {
            case 'A':
            case 'a':
            case 'E':
            case 'e':
            case 'I':
            case 'i':
            case 'O':
            case 'o':
            case 'U':
            case 'u':
                ampChArray_Replaced[i] = '*';
                break;

            default:
                break;
        }
    }

    printf("String entered is : ");
    printf("%s\n", ampChArray_Original);

    printf("String after replacement of vowel with '*' is : ");
    printf("%s\n", ampChArray_Replaced);

    return(0);
}

//func definition
int MyStrLen(char str[])
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    for(j = 0; j < MAX_STRING_LENGTH; j++)
    {
        if(str[j] == '\0')
            break;
        else
            string_length++;
    }

    return(string_length);
}

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
