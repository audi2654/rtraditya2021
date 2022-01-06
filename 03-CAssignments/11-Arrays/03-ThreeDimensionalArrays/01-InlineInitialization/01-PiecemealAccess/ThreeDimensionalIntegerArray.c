//C Arrays assignment : 3D Array
//Program to inline initialize a 3D array by piecemeal access method

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.

    //inline initialization
    int amp_iArray[5][3][2] = { { { 9, 18 }, { 27, 36 }, { 45, 54 } },
                               { { 8, 16 }, { 24, 32 }, { 40, 48 } },
                               { { 7, 14 }, { 21, 28 }, { 35, 42 } },
                               { { 6, 12 }, { 18, 24 }, { 30, 36 } },
                               { { 5, 10 }, { 12, 20 }, { 25, 30 } } };

    int int_size;
    int iArray_size;
    int iArray_num_elements, iArray_width, iArray_height, iArray_depth;

    //code
    printf("\n\n");

    int_size = sizeof(int);

    iArray_size = sizeof(amp_iArray);
    printf("Size of 3D int array is : %d\n\n", iArray_size);

    iArray_width = iArray_size / sizeof(amp_iArray[0]);
    printf("Number of rows(width) in 3D int array is : %d\n\n", iArray_width);

    iArray_height = sizeof(amp_iArray[0]) / sizeof(amp_iArray[0][0]);
    printf("Number of columns(height) in 3D int array is : %d\n\n", iArray_height);

    iArray_depth = sizeof(amp_iArray[0][0]) / int_size;
    printf("Depth in 3D int array is : %d\n\n", iArray_depth);

    iArray_num_elements = iArray_width * iArray_height * iArray_depth;
    printf("Number of elements in 3D int array is : %d\n\n", iArray_num_elements);

    printf("\n\n");
    printf("Elements in int 3D array : \n");

    //piece meal display
    //row 1
    printf("ROW-1\n");
    printf("COLUMN-1\n");
    printf("amp_iArray[0][0][0] = %d\n", amp_iArray[0][0][0]);
    printf("amp_iArray[0][0][1] = %d\n", amp_iArray[0][0][1]);
    printf("\n");
    
    printf("COLUMN-2\n");
    printf("amp_iArray[0][1][0] = %d\n", amp_iArray[0][1][0]);
    printf("amp_iArray[0][1][1] = %d\n", amp_iArray[0][1][1]);
    printf("\n");

    printf("COLUMN-3\n");
    printf("amp_iArray[0][2][0] = %d\n", amp_iArray[0][2][0]);
    printf("amp_iArray[0][2][1] = %d\n", amp_iArray[0][2][1]);
    printf("\n\n");

    //row 2
    printf("ROW-2\n");
    printf("COLUMN-1\n");
    printf("amp_iArray[1][0][0] = %d\n", amp_iArray[1][0][0]);
    printf("amp_iArray[1][0][1] = %d\n", amp_iArray[1][0][1]);
    printf("\n");
    
    printf("COLUMN-2\n");
    printf("amp_iArray[1][1][0] = %d\n", amp_iArray[1][1][0]);
    printf("amp_iArray[1][1][1] = %d\n", amp_iArray[1][1][1]);
    printf("\n");

    printf("COLUMN-3\n");
    printf("amp_iArray[1][2][0] = %d\n", amp_iArray[1][2][0]);
    printf("amp_iArray[1][2][1] = %d\n", amp_iArray[1][2][1]);
    printf("\n\n");

    //row 3
    printf("ROW-3\n");
    printf("COLUMN-1\n");
    printf("amp_iArray[2][0][0] = %d\n", amp_iArray[2][0][0]);
    printf("amp_iArray[2][0][1] = %d\n", amp_iArray[2][0][1]);
    printf("\n");
    
    printf("COLUMN-2\n");
    printf("amp_iArray[2][1][0] = %d\n", amp_iArray[2][1][0]);
    printf("amp_iArray[2][1][1] = %d\n", amp_iArray[2][1][1]);
    printf("\n");

    printf("COLUMN-3\n");
    printf("amp_iArray[2][2][0] = %d\n", amp_iArray[2][2][0]);
    printf("amp_iArray[2][2][1] = %d\n", amp_iArray[2][2][1]);
    printf("\n\n");

    //row 4
    printf("ROW-4\n");
    printf("COLUMN-1\n");
    printf("amp_iArray[3][0][0] = %d\n", amp_iArray[3][0][0]);
    printf("amp_iArray[3][0][1] = %d\n", amp_iArray[3][0][1]);
    printf("\n");
    
    printf("COLUMN-2\n");
    printf("amp_iArray[3][1][0] = %d\n", amp_iArray[3][1][0]);
    printf("amp_iArray[3][1][1] = %d\n", amp_iArray[3][1][1]);
    printf("\n");

    printf("COLUMN-3\n");
    printf("amp_iArray[3][2][0] = %d\n", amp_iArray[3][2][0]);
    printf("amp_iArray[3][2][1] = %d\n", amp_iArray[3][2][1]);
    printf("\n\n");

    //row 5
    printf("ROW-5\n");
    printf("COLUMN-1\n");
    printf("amp_iArray[4][0][0] = %d\n", amp_iArray[4][0][0]);
    printf("amp_iArray[4][0][1] = %d\n", amp_iArray[4][0][1]);
    printf("\n");
    
    printf("COLUMN-2\n");
    printf("amp_iArray[4][1][0] = %d\n", amp_iArray[4][1][0]);
    printf("amp_iArray[4][1][1] = %d\n", amp_iArray[4][1][1]);
    printf("\n");

    printf("COLUMN-3\n");
    printf("amp_iArray[4][2][0] = %d\n", amp_iArray[4][2][0]);
    printf("amp_iArray[4][2][1] = %d\n", amp_iArray[4][2][1]);
    printf("\n\n");

    return(0);
}
