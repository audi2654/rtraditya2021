//C Arrays assignment : Array Sizes
//Program to calculate sizes of 1D, 2D, 3D arrays

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int amp_iArray1D[5];
    int amp_iArray2D[5][3];
    int amp_iArray3D[100][100][5];

    int num_rows_2D;
    int num_columns_2D;

    int num_rows_3D;
    int num_columns_3D;
    int depth_3D;

    //code
    //1D array
    printf("\n\n");
    printf("Size of 1D int array amp_iArray1D = %lu\n", sizeof(amp_iArray1D));
    printf("Number of elements in 1D int array amp_iArray1D = %lu\n", (sizeof(amp_iArray1D) / sizeof(int)));

    //2D array
    printf("\n\n");
    printf("Size of 2D int array amp_iArray2D = %lu\n", sizeof(amp_iArray2D));

    printf("Number of ROWS in 2D int array amp_iArray2D = %lu\n", (sizeof(amp_iArray2D) / sizeof(amp_iArray2D[0])));
    num_rows_2D = (sizeof(amp_iArray2D) / sizeof(amp_iArray2D[0]));

    printf("Number of COLUMNS (elements in each row) in 2D int array amp_iArray2D = %lu\n", (sizeof(amp_iArray2D[0]) / sizeof(amp_iArray2D[0][0])));
    num_columns_2D = (sizeof(amp_iArray2D[0]) / sizeof(amp_iArray2D[0][0]));

    printf("Number of elements in 2D int array amp_iArray2D = %d\n", (num_rows_2D * num_columns_2D));

    //3D array
    printf("\n\n");
    printf("Size of 3D int array amp_iArray3D = %lu\n", sizeof(amp_iArray3D));

    printf("Number of ROWS in 3D int array amp_iArray3D = %lu\n", (sizeof(amp_iArray3D) / sizeof(amp_iArray3D[0])));
    num_rows_3D = (sizeof(amp_iArray3D) / sizeof(amp_iArray3D[0]));

    printf("Number of COLUMNS (elements in each row) in 3D int array amp_iArray3D = %lu\n", (sizeof(amp_iArray3D[0]) / sizeof(amp_iArray3D[0][0])));
    num_columns_3D = (sizeof(amp_iArray3D[0]) / sizeof(amp_iArray3D[0][0]));

    printf("Number of elements (DEPTH) in each column in each row in 3D int array amp_iArray3D = %lu\n", (sizeof(amp_iArray3D[0][0]) / sizeof(amp_iArray3D[0][0][0])));
    depth_3D = (sizeof(amp_iArray3D[0][0]) / sizeof(amp_iArray3D[0][0][0]));

    printf("Number of elements in 3D int array amp_iArray2D = %d\n\n", (num_rows_3D * num_columns_3D * depth_3D));

    return(0);
}
