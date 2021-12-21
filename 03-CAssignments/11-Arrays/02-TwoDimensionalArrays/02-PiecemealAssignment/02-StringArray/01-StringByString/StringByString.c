//C Arrays assignment : 2D Array
//Program to piece meal initialize & access a 2D character array by loops string by string

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char *argv[], char *envp[])
{
    //func prototype
    void ampStrCpy(char[], char[]);

    //var decl.
    
    //a String is an array of characters stored in contiguous memory, so char[] is char array & hence a String
    //an array of char arrays is an array of Strings
    //hence char[] is 1 char array & a 1 single String
    //so char[][] is an array of multiple char arrays & an array of multiple Strings

    //below written is an String array that can have max 10 strings (10rows) & each of the 10 strings(rows)
    //can have upto 15 characters (15columns) max
    char ampStrArray[5][10];    //5 strings each with 10 characters max
    int char_size;
    int strArray_size;
    int strArray_num_elements, strArray_num_rows, strArray_num_columns;
    int i;

    //code
    printf("\n\n");

    char_size = sizeof(char);

    strArray_size = sizeof(ampStrArray);
    printf("Size of 2D char array = %d\n", strArray_size);

    strArray_num_rows = strArray_size / sizeof(ampStrArray[0]);
    printf("Number of ROWS in 2D char array = %d\n", strArray_num_rows);

    strArray_num_columns = sizeof(ampStrArray) / char_size;
    printf("Number of COLUMNS in 2D char array = %d\n", strArray_num_columns);

    strArray_num_elements = strArray_num_rows * strArray_num_columns;
    printf("Max Number of ELEMENTS in 2D char array = %d\n", strArray_num_elements);

    //piece meal assignment
    ampStrCpy(ampStrArray[0], "My");
    ampStrCpy(ampStrArray[1], "Name");
    ampStrCpy(ampStrArray[2], "Is");
    ampStrCpy(ampStrArray[3], "Aditya");
    ampStrCpy(ampStrArray[4], "Panchal");

    printf("\n\n");
    printf("Strings in the 2D array : ");

    for(i = 0; i < strArray_num_rows; i++)
    {
        printf("%s ", ampStrArray[i]);
    }
   
    printf("\n\n");

    return(0);
}

//func definition
void ampStrCpy(char str_destination[], char str_source[])
{
    //func prototype
    int ampStrLen(char []);

    //var decl.
    int ampStringLength = 0;
    int j;

    //code
    ampStringLength = ampStrLen(str_source);
    for(j = 0; j < ampStringLength; j++)
    {
        str_destination[j] = str_source[j];
    }
    str_destination[j] = '\0';
}

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
