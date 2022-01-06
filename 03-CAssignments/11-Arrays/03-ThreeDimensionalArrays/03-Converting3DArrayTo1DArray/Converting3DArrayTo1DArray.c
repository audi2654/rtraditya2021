//C Arrays assignment : 3D Array
//Program to convert a 3D array to 1D array

#include <stdio.h>

#define AMP_NUM_ROWS 5
#define AMP_NUM_COLUMNS 3
#define AMP_DEPTH 2


int main(int argc, char* argv[], char* envp[])
{
    //var decl.

    //inline initialization
    int amp_iArray[5][3][2] = { { { 0, 1 }, { -1, -2 }, { 'a', 'b' } },
                               { { 2, 3 }, { -3, -4 }, { 'c', 'd' } },
                               { { 4, 5 }, { -5, -6 }, { 'e', 'f' } },
                               { { 6, 7 }, { -7, -8 }, { 'g', 'h' } },
                               { { 8, 9 }, { -9, -10 }, { 'i', 'j' } } };

    int i, j, k;

    int amp_iArray1D[AMP_NUM_COLUMNS * AMP_NUM_ROWS * AMP_DEPTH];    //5 * 3 * 2 elements = 30 total elements

    //code
    printf("\n\n");

    //nested loops display
    printf("Elements in the 3D array : \n");
    for(i = 0; i < AMP_NUM_ROWS; i++)
    {
        printf("ROW-%d\n", (i + 1));
        for(j = 0; j < AMP_NUM_COLUMNS; j++)
        {
            printf("COLUMN-%d\n", (j + 1));
            for(k = 0; k < AMP_DEPTH; k++)
            {
                printf("amp_iArray[%d][%d][%d] = %d\n", i, j, k, amp_iArray[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    //converting 3D to 1D array
    for(i = 0; i < AMP_NUM_ROWS; i++)
    {
        for(j = 0; j < AMP_NUM_COLUMNS; j++)
        {
            for(k = 0; k < AMP_DEPTH; k++)
            {
                amp_iArray1D[(i * AMP_NUM_COLUMNS * AMP_DEPTH) + (j * AMP_DEPTH) + k] = amp_iArray[i][j][k];
            }
        }
    }

    //displaying 1D array
    printf("\n\n");
    printf("Elements in the 1D array : \n");
    for(i = 0; i < (AMP_NUM_ROWS * AMP_NUM_COLUMNS * AMP_DEPTH); i++)
    {
        printf("amp_iArray1D[%d] = %d\n", i, amp_iArray1D[i]);
    }

    //printing 3D array as it is
    printf("\n\n");
    printf("Displaying 3D array as it is: \n");
    printf("{\n");
    for(i = 0; i < AMP_NUM_ROWS; i++)
    {
        printf("{ ");
        for(j = 0; j < AMP_NUM_COLUMNS; j++)
        {
            
            for(k = 0; k < AMP_DEPTH; k++)
            {
                
                printf("{ %d, ", amp_iArray[i][j][k++]);
                printf("%d }", amp_iArray[i][j][k]);

                if(j == 2)
                    printf(" ");
                else
                    printf(", ");
            }
        }
        printf("}");

        if(i == 4)
            printf(" ");
        else
            printf(",");

        printf("\n");
    }
    printf("}\n");
    
    return(0);
}
