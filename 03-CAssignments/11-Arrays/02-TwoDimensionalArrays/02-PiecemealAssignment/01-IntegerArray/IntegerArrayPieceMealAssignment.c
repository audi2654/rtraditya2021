//C Arrays assignment : 2D Array
//Program to piece meal initialize & access a 2D integer array by loops

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int ampArray[3][5]; //3 Rows & 5 Columns 
    int int_size;
    int ampArraySize;
    int ampArray_num_elements, ampArray_num_rows, ampArray_num_columns;
    int i, j;

    //code
    printf("\n\n");

    int_size = sizeof(int);

    ampArraySize = sizeof(ampArray);
    printf("Size of 2D int array = %d\n", ampArraySize);

    ampArray_num_rows = ampArraySize / sizeof(ampArray[0]);
    printf("Number of ROWS in 2D int array = %d\n", ampArray_num_rows);

    ampArray_num_columns = sizeof(ampArray[0]) / int_size;
    printf("Number of COLUMNS in 2D int array = %d\n", ampArray_num_columns);

    ampArray_num_elements = ampArray_num_rows * ampArray_num_columns;
    printf("Number of ELEMENTS in 2D int array = %d\n", ampArray_num_elements);

    printf("\n\n");

    printf("Elements in 2D array : \n");

    //Piece Meal Assignment
    //Row 1
    ampArray[0][0] = 22;
    ampArray[0][1] = 43;
    ampArray[0][2] = 64;
    ampArray[0][3] = 85;
    ampArray[0][4] = 106;

    //Row 1
    ampArray[1][0] = 23;
    ampArray[1][1] = 44;
    ampArray[1][2] = 65;
    ampArray[1][3] = 86;
    ampArray[1][4] = 107;

    //Row 2
    ampArray[2][0] = 24;
    ampArray[2][1] = 45;
    ampArray[2][2] = 66;
    ampArray[2][3] = 87;
    ampArray[2][4] = 108;

    //Displaying elements
    for(i = 0; i < ampArray_num_rows; i++)
    {
        printf("ROW %d\n", (i+1));
        for(j = 0; j < ampArray_num_columns; j++)
        {
            printf("ampArray[%d][%d] = %d\n", i, j, ampArray[i][j]);
        }
        printf("\n\n");
    }

    return(0);
}
