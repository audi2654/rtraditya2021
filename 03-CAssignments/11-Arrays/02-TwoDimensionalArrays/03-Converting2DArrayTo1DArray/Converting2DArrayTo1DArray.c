//C Arrays assignment : 2D Array
//Program to convert a 2D array to 1D array

#include <stdio.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int amp_iArray_2D[NUM_ROWS][NUM_COLUMNS];   //total number of elements = num rows * num columns
    int amp_iArray_1D[NUM_ROWS * NUM_COLUMNS];

    int i, j;
    int num;

    //code
    printf("\n\n");
    printf("Enter elements to fill 2D array : \n");
    for(i = 0; i < NUM_ROWS; i++)
    {
        printf("For ROW-%d : \n", (i + 1));
        for(j = 0; j < NUM_COLUMNS; j++)
        {
            printf("Enter element number %d : ", (j + 1));
            scanf("%d", &num);
            amp_iArray_2D[i][j] = num;
        }
        printf("\n\n");
    }

    //display of 2D array
    printf("\n\n");
    printf("Two dimensional array is : \n");
    for(i = 0; i < NUM_ROWS; i++)
    {
        printf("ROW-%d\n", (i + 1));
        for(j = 0; j < NUM_COLUMNS; j++)
        {
            printf("amp_iArray_2D[%d][%d] = %d\n", i, j, amp_iArray_2D[i][j]);
        }
        printf("\n\n");
    }
    
    //converting 2D int array to 1D array
    for(i = 0; i < NUM_ROWS; i++)
    {
        for(j = 0; j < NUM_COLUMNS; j++)
        {
            amp_iArray_1D[(i * NUM_COLUMNS) + j] = amp_iArray_2D[i][j];
        }
    }

    //printing 1D array
    printf("\n\n");
    printf("One dimensional array is : \n");
    for(i = 0; i < (NUM_ROWS * NUM_COLUMNS); i++)
    {
        printf("amp_iArray_1D[%d] = %d\n", i, amp_iArray_1D[i]);
    }

    printf("\n\n");

    return(0);
}
