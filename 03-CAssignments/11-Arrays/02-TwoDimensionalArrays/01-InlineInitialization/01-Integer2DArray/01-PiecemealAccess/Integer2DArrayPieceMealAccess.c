//C Arrays assignment : 2D Array
//Program to access a 2D integer array by piecemeal method

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int ampArray[5][3] = { {1, 2, 3},
                           {2, 4, 6},
                           {3, 6, 9},
                           {4, 8, 12},
                           {5, 10, 15} };   //inline initialization

    int intSize;
    int ampArraySize;
    int ampArrayNumElements, ampArrayNumRows, ampArrayNumColumns;

    //code
    printf("\n\n");

    //Remember similar to 1D arrays, 2D or any dimensional arrays are stored in a contiguous memory

    intSize = sizeof(int);

    ampArraySize = sizeof(ampArray);    //ampArray has 5 rows & 3 columns so in total 15 elements of type int
    //hence total size of 2D ampArray can be 5R * 3C * 4bytes of int = 60 bytes in contiguous memory 
    printf("Size of 2D integer array = %d\n\n", ampArraySize);

    ampArrayNumRows = ampArraySize / sizeof(ampArray[0]);   
    //ampArray has 5 rows & each rows internally is an array of 3 elements
    //so 1st row actually has 3 elements of type int in it, 
    //hence total size of a single row = 1 row * (3 columns(elements) * 4 bytes of int) = 12 bytes for single row in contiguous memory
    //sizeof(ampArray[0] = 12 bytes)

    //dividing the size of whole array by size of single row will give no of rows in that whole contiguous 60 bytes array
    printf("Number of ROWS in 2D array = %d\n\n", ampArrayNumRows);

    ampArrayNumColumns = sizeof(ampArray[0]) / intSize;
    //dividing the size of single row by the size of datatype of array will give no of columns in that single row of 12 bytes
    printf("Number of COLUMNS in 2D array = %d\n\n", ampArrayNumColumns);

    ampArrayNumElements = ampArrayNumRows * ampArrayNumColumns; //most correct way to calculate actual no. of elements in any type of array
    printf("Number of ELEMENTS in 2D array = %d\n\n", ampArrayNumElements);

    printf("\n\n");

    printf("Elements in 2D array : \n\n");

    //piece meal accessing of 2d array

    //Row 1
    printf("ROW 1\n");
    printf("ampArray[0][0] = %d\n", ampArray[0][0]); //Row 0 Column 0 element
    printf("ampArray[0][1] = %d\n", ampArray[0][1]); //Row 0 Column 1 element
    printf("ampArray[0][2] = %d\n", ampArray[0][2]); //Row 0 Column 2 element
    printf("\n\n");

    //Row 2
    printf("ROW 2\n");
    printf("ampArray[1][0] = %d\n", ampArray[1][0]); //R1C0 element
    printf("ampArray[1][1] = %d\n", ampArray[1][1]); //R1C1 element
    printf("ampArray[1][2] = %d\n", ampArray[1][2]); //R1C2 element
    printf("\n\n");

    //Row 3
    printf("ROW 3\n");
    printf("ampArray[2][0] = %d\n", ampArray[2][0]); //2R0C element
    printf("ampArray[2][1] = %d\n", ampArray[2][1]); //2R1C element
    printf("ampArray[2][2] = %d\n", ampArray[2][2]); //2R2C element
    printf("\n\n");

    //Row 4
    printf("ROW 4\n");
    printf("ampArray[3][0] = %d\n", ampArray[3][0]); //30 element
    printf("ampArray[3][1] = %d\n", ampArray[3][1]); //31 element
    printf("ampArray[3][2] = %d\n", ampArray[3][2]); //32 element
    printf("\n\n");

    //Row 5
    printf("ROW 5\n");
    printf("ampArray[4][0] = %d\n", ampArray[4][0]); //40 - Row 5th Column 1st element
    printf("ampArray[4][1] = %d\n", ampArray[4][1]); //41 - Row 5th Column 2nd element
    printf("ampArray[4][2] = %d\n", ampArray[4][2]); //42 - Row 5th Column 3rd element
    printf("\n\n");

    return(0);
}
