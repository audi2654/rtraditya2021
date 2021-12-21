//C Arrays assignment : 2D Array
//Program to piece meal initialize & access a 2D character array by loops character by character

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    
    //a String is an array of characters stored in contiguous memory, so char[] is char array & hence a String
    //an array of char arrays is an array of Strings
    //hence char[] is 1 char array & a 1 single String
    //so char[][] is an array of multiple char arrays & an array of multiple Strings

    //below written is an String array that can have max 10 strings (10rows) & each of the 10 strings(rows)
    //can have upto 15 characters (15columns) max
    char ampStrArray[5][10];    //5 Rows(Strings) each with 10 Columns(Characters) max
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
    //Row 1 / String 1
    ampStrArray[0][0] = 'M';
    ampStrArray[0][1] = 'y';
    ampStrArray[0][2] = '\0';   //null terminating character

    //Row 2 / String 2
    ampStrArray[1][0] = 'N';
    ampStrArray[1][1] = 'a';
    ampStrArray[1][2] = 'm';
    ampStrArray[1][3] = 'e';
    ampStrArray[1][4] = '\0';

    //Row 3 / String 3
    ampStrArray[2][0] = 'I';
    ampStrArray[2][1] = 's';
    ampStrArray[2][2] = '\0';

    //Row 4 / String 4
    ampStrArray[3][0] = 'A';
    ampStrArray[3][1] = 'd';
    ampStrArray[3][2] = 'i';
    ampStrArray[3][3] = 't';
    ampStrArray[3][4] = 'y';
    ampStrArray[3][5] = 'a';
    ampStrArray[3][6] = '\0';

    //Row 5 / String 5
    ampStrArray[4][0] = 'P';
    ampStrArray[4][1] = 'a';
    ampStrArray[4][2] = 'n';
    ampStrArray[4][3] = 'c';
    ampStrArray[4][4] = 'h';
    ampStrArray[4][5] = 'a';
    ampStrArray[4][6] = 'l';
    ampStrArray[4][7] = '\0';

    printf("\n\n");
    printf("Strings in the 2D array : ");

    //storing in lengths of all the strings
    for(i = 0; i < strArray_num_rows; i++)
    {
        printf("%s ", ampStrArray[i]);
    }

    printf("\n\n");
    return(0);
}
