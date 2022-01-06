//C Arrays assignment : 3D Array
//Program to inline initialize a 3D array by nested loop access method

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.

    //inline initialization
    int amp_iArray[5][3][2] = { { { 0, 1 }, { -1, -2 }, { 'a', 'b' } },
                               { { 2, 3 }, { -3, -4 }, { 'c', 'd' } },
                               { { 4, 5 }, { -5, -6 }, { 'e', 'f' } },
                               { { 6, 7 }, { -7, -8 }, { 'g', 'h' } },
                               { { 8, 9 }, { -9, -10 }, { 'i', 'j' } } };

    int int_size;
    int iArray_size;
    int iArray_num_elements, iArray_width, iArray_height, iArray_depth;
    int i, j, k;

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

    //nested loops display
    for(i = 0; i < iArray_width; i++)
    {
        printf("ROW-%d\n", (i + 1));
        for(j = 0; j < iArray_height; j++)
        {
            printf("COLUMN-%d\n", (j + 1));
            for(k = 0; k < iArray_depth; k++)
            {
                printf("amp_iArray[%d][%d][%d] = %d\n", i, j, k, amp_iArray[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    return(0);
}
