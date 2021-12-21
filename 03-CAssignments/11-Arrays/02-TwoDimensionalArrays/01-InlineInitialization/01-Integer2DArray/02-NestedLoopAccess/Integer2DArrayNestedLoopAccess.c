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
    int i, j;

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

    //accessing of 2d array using nested for loop

    //using nested for loop
    /*for(i = 0; i < ampArrayNumRows; i++)
    {
        for(j = 0; j < ampArrayNumColumns; j++)
        {
            printf("ampArray[%d][%d] = %d\n", i, j, ampArray[i][j]);
        }
        printf("\n\n");
    }*/

    //using nested while loop
    /*i = 0;
    j = 0;
    while(i < ampArrayNumRows)
    {
        while(j < ampArrayNumColumns)
        {
            printf("ampArray[%d][%d] = %d\n", i, j, ampArray[i][j]);
            j++;
        }
        j = 0;
        i++;
        printf("\n\n");
    }*/
    
    //using nested do while loop
    i = 0;
    j = 0;

    do
    {
        do
        {
            printf("ampArray[%d][%d] = %d\n", i, j, ampArray[i][j]);
            j++;
        } while (j < ampArrayNumColumns);

        j = 0;
        i++;
        printf("\n\n");
    } while (i < ampArrayNumRows);

    return(0);
}
