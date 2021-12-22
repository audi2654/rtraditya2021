//C Arrays assignment : 1D Array : String operations
//Program to count all words & spaces in a string

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int MyStrLen(char[]);

    //var decl.
    char ampChArray[MAX_STRING_LENGTH];     //a char array is a string
    int iStringLength;
    int i;
    int word_count = 0, space_count = 0;

    //code
    //string input
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    //string output
    printf("\n\n");

    iStringLength = MyStrLen(ampChArray);
    
    for(i = 0; i < iStringLength; i++)
    {
        switch(ampChArray[i])
        {
            case 32:    //32 is ASCII for space character
            case ' ':
                space_count++;
                break;

            default:
                break;
        }
    }

    word_count = space_count + 1;

    printf("String entered is : ");
    printf("%s\n\n", ampChArray);

    printf("Number of spaces in input string = %d\n", space_count);
    printf("Number of words in input string = %d\n", word_count);

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
