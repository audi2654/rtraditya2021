//C Arrays assignment : 1D Array : String operations
//Program to capitalize letters of a string using library function toupper()

#include <stdio.h>
#include <ctype.h>  //for toupper()

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int MyStrLen(char[]);

    //var decl.
    char ampChArray[MAX_STRING_LENGTH], ampChArray_CapitalizedFirstLetterOfEveryWord[MAX_STRING_LENGTH];   //a character array is a string
    int iStringLength;
    int i, j;

    //code
    //string input
    printf("\n\n");
    printf("Enter string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    iStringLength = MyStrLen(ampChArray);
    j = 0;

    for(i = 0; i < iStringLength; i++)
    {
        if(i == 0)
            ampChArray_CapitalizedFirstLetterOfEveryWord[j] = toupper(ampChArray[i]);

        else if(ampChArray[i] == ' ')
        {
            ampChArray_CapitalizedFirstLetterOfEveryWord[j] = ampChArray[i];
            ampChArray_CapitalizedFirstLetterOfEveryWord[j + 1] = toupper(ampChArray[i + 1]);

            //since already 2 chars at indices i & i+1 have been considered in this else if block, we are extra
            //incrementing i & j by 1
            j++;
            i++;
        }
        else
            ampChArray_CapitalizedFirstLetterOfEveryWord[j] = ampChArray[i];

        j++;
    }

    ampChArray_CapitalizedFirstLetterOfEveryWord[j] = '\0';

    //string output
    printf("\n\n");
    printf("String entered is : %s\n", ampChArray);
    printf("String with CAPITAL First Letter is : %s\n", ampChArray_CapitalizedFirstLetterOfEveryWord);

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
