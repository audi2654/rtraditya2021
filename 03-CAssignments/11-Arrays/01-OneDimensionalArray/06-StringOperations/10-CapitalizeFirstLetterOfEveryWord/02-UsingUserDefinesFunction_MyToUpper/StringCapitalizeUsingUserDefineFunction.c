//C Arrays assignment : 1D Array : String operations
//Program to capitalize letters of a string using user defined function

#include <stdio.h>

#define MAX_STRING_LENGTH 512

#define SPACE ' '
#define FULLSTOP '.'
#define COMMA ','
#define EXCLAMATION '!'
#define QUESTION_MARK '?'

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int MyStrLen(char[]);
    char MyToUpper(char);

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
        if(i == 0)  //First letter of any sentence must be capital letter
            ampChArray_CapitalizedFirstLetterOfEveryWord[j] = MyToUpper(ampChArray[i]);

        else if(ampChArray[i] == SPACE) //First letter of Every Word in sentence must be capital, words are separated by space
        {
            ampChArray_CapitalizedFirstLetterOfEveryWord[j] = ampChArray[i];
            ampChArray_CapitalizedFirstLetterOfEveryWord[j + 1] = toupper(ampChArray[i + 1]);

            //since already 2 chars at indices i & i+1 have been considered in this else if block, we are extra
            //incrementing i & j by 1
            j++;
            i++;
        }
        else if((ampChArray[i] == FULLSTOP || ampChArray[i] == COMMA || ampChArray[i] == EXCLAMATION || ampChArray[i] == QUESTION_MARK) && (ampChArray[i] != SPACE))
        //First letter of every word after punctuation mark in sentence must be capital. Words are sepearated by punctuations 
        {
            ampChArray_CapitalizedFirstLetterOfEveryWord[j] = ampChArray[i];
            ampChArray_CapitalizedFirstLetterOfEveryWord[j + 1] = SPACE;
            ampChArray_CapitalizedFirstLetterOfEveryWord[j + 2] = MyToUpper(ampChArray[i + 1]);

            //since already 2 chars at indices i & i+1 have been considered in this else if block, we are extra
            //incrementing i by 1

            //since already 3 chars at indices j & j+1 & j+2 have been considered in this else if block, we are extra
            //incrementing j by 2
            j = j + 2;
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

char MyToUpper(char ch)
{
    //var decl.
    int num;
    int c;

    //code

    //ascii value of 'a' (97) - ascii value of 'A' (65) = 32
    //this subtraction will give the exact diffrence between the upper and lower case letters
    //if this difference is subtracted from ascii value if a lower case, the resultant value will be ascii of its 
    //upper case counterpart

    //ascii value a to z = 97 to 122
    //ascii value A to Z = 65 to 90

    num = 'a' - 'A';

    if((int)ch >= 97 && (int)ch <= 122)
    {
        c = (int)ch - num;
        return((char)c);
    }
    else
        return(ch);
}
