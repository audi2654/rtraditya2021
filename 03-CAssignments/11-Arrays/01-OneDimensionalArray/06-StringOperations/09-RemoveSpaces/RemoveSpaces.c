//C Arrays assignment : 1D Array : String operations
//Program to remove all spaces in a string

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int MyStrLen(char[]);
    void MyStrCpy(char[], char[]);

    //var decl.
    char ampChArray[MAX_STRING_LENGTH], ampChArray_SpaceRemoved[MAX_STRING_LENGTH];     //a char array is a string
    int iStringLength;
    int i, j;

    //code
    //string input
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    iStringLength = MyStrLen(ampChArray);
    j = 0;
    
    for(i = 0; i < iStringLength; i++)
    {
        if(ampChArray[i] == ' ')
            continue;
        else
        {
            ampChArray_SpaceRemoved[j] = ampChArray[i];
            j++;
        }
    }

    ampChArray_SpaceRemoved[j] = '\0';

    //string output
    printf("\n\n");
    printf("String entered is : ");
    printf("%s\n\n", ampChArray);

    printf("String after removal of spaces is : %s\n\n", ampChArray_SpaceRemoved);

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
