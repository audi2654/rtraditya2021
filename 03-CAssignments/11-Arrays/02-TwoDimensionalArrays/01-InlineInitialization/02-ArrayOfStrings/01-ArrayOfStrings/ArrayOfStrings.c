//C Arrays assignment : 2D Array
//Program to inline initialize & access a 2D character array by piecemeal method string by string

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

    int char_size;
    int strArray_size;
    int strArray_num_elements, strArray_num_rows, strArray_num_columns;
    int strActual_num_chars = 0;
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

    for(i = 0; i < strArray_num_rows; i++)
    {
        strActual_num_chars = strActual_num_chars + ampStrLen(ampStrArray[i]);
    }
    printf("Actual Number of Elements (Characters) in 2D char array (string array) is = %d\n", strActual_num_chars);

    printf("\n\n");

    printf("Strings in the 2D array : ");

    //since char[][] is an array of strings, referencing only by the row number will give the whole row or the string
    //first[] will give the row or the string
    //second[] is the particular character in that string

    printf("%s ", ampStrArray[0]);
    printf("%s ", ampStrArray[1]);
    printf("%s ", ampStrArray[2]);
    printf("%s ", ampStrArray[3]);
    printf("%s ", ampStrArray[4]);
    printf("%s ", ampStrArray[5]);
    printf("%s ", ampStrArray[6]);
    printf("%s ", ampStrArray[7]);
    printf("%s ", ampStrArray[8]);
    printf("%s \n\n", ampStrArray[9]);

    //using for loop
    for (i = 0; i < strArray_num_rows; i++)
    {
       for (int j = 0; j < strArray_num_columns; j++)
       {
            printf("%c", ampStrArray[i][j]);
            if(ampStrArray[i][j] == '\0')
                break;
       }
        printf("\n ");
    }

    printf("\n\n");

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
