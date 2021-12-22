//C Arrays assignment : 1D Array : String operations
//Program to count vowels in a string

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    int MyStrLen(char []);

    //var decl.
    char ampChArray[MAX_STRING_LENGTH];     //a char array is a string
    int iStringLength;
    int countA = 0, countE = 0, countI = 0, countO = 0, countU = 0;
    int i;

    //code
    //string input
    printf("\n\n");
    printf("Enter a string : ");
    gets_s(ampChArray, MAX_STRING_LENGTH);

    //string output
    printf("\n\n");
    printf("String entered is : ");
    printf("%s\n", ampChArray);

    iStringLength = MyStrLen(ampChArray);

    for(i = 0; i < iStringLength; i++)
    {
        switch(ampChArray[i])
        {
            case 'A':
            case 'a':
                countA++;
                break;

            case 'E':
            case 'e':
                countE++;
                break;

            case 'I':
            case 'i':
                countI++;
                break;

            case 'O':
            case 'o':
                countO++;
                break;

            case 'U':
            case 'u':
                countU++;
                break;

            default:
                break;
        }
    }

    printf("\n\n");
    printf("In the string entered, the vowels & their number of occurences are as follows : \n");
    printf("Count of 'A' = %d times\n", countA);
    printf("Count of 'E' = %d times\n", countE);
    printf("Count of 'I' = %d times\n", countI);
    printf("Count of 'O' = %d times\n", countO);
    printf("Count of 'U' = %d times\n", countU);

    return(0);
}

//func definition
int MyStrLen(char str[])
{
    //var decl.
    int j;
    int string_length;

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
