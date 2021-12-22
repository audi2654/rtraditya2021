//C Arrays assignment : 1D Array : String operations
//Program to show length of a string using library function strlen

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int ampStrLen(char[]);

    //var decl.
    char ampChArray[MAX_STRING_LENGTH];   //a character array is a string
    int ampStringLength = 0;

    //code
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    printf("\n");
    printf("Entered string is : %s\n\n", ampChArray);

    //string length
    ampStringLength = ampStrLen(ampChArray);
    printf("Length of String = %d character\n\n", ampStringLength);

    return(0);
}

//func definition
int ampStrLen(char str[])
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    //determining exact length of string, by detecting the first occurence of null terminating character '\0'
    for(j = 0; j < MAX_STRING_LENGTH; j++)
    {
        if(str[j] == '\0')
            break;
        else
            string_length++;
    }
    return(string_length);
}
