//C Arrays assignment : 2D Array
//Program to inline initialize & access a 2D character array by loops character by character

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char *argv[], char *envp[])
{
    //func prototype
    int ampStrLen(char[]);

    //var decl.
    
    //a String is an array of characters stored in contiguous memory, so char[] is char array & hence a String
    //an array of char arrays is an array of Strings
    //hence char[] is 1 char array & a 1 single String
    //so char[][] is an array of multiple char arrays & an array of multiple Strings

    //below written is an String array that can have max 10 strings (10rows) & each of the 10 strings(rows)
    //can have upto 15 characters (15columns) max
    char ampStrArray[10][15] = { "Hello", "Welcome", "To", "Real", "Time", "Rendering", "Batch", "2021-21", "Of", "ASTROMEDICOMP" }; //inline initialization of 2D char arrays or string arrays

    int iStrLengths[10];    //1D integer array to store length of each string at corresponding indices in 'ampStrArray[]' 
    //e.g iStrLength[0] will be the length of string at 0th index, & likewise

    int strArray_size;
    int strArray_num_rows;
    int i, j;

    //code
    strArray_size = sizeof(ampStrArray);
    strArray_num_rows = strArray_size / sizeof(ampStrArray[0]);

    //storing in lengths of all the strings
    for(i = 0; i < strArray_num_rows; i++)
    {
        iStrLengths[i] = ampStrLen(ampStrArray[i]);
    }

    printf("\n\n");
    printf("The Entire String array : \n");
    for(i = 0; i < strArray_num_rows; i++)
    {
        printf("%s ", ampStrArray[i]);
    }

    printf("\n\n");
    printf("Strings in the 2D array : ");

    //since char[][] is an array of strings, referencing only by the row number will give the whole row or the string
    //first[] will give the row or the string
    //second[] is the particular character in that string

    for(i = 0; i < strArray_num_rows; i++)
    {
        printf("String num %d => %s\n", (i + 1), ampStrArray[i]);
        for(j = 0; j < iStrLengths[i]; j++)
        {
            printf("Character %d = %c\n", (j + 1), ampStrArray[i][j]);
        }
        printf("\n");
    }

    int total = 0;
    for(i = 0; i < 10; i++)
    {
        total = total + iStrLengths[i];
    }
    printf("Total number of characters in all strings or whole 2D array = %d\n", total);

    return(0);
}

//func definition
int ampStrLen(char str[])
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    //determining exact length of the string by detecting 1st occurence of null-terminating charcter (\0)
    for(j = 0; j < MAX_STRING_LENGTH; j++)
    {
        if(str[j] == '\0')
            break;
        else
            string_length++;
    }

    return(string_length);
}
