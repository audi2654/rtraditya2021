//C Pointers assignment : Array Pointer Representation
//Program to represent a 2D array using malloc & seperate pointer 

#include <stdio.h>
#include <stdlib.h> 	

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int i, j;
	int **ptr_for_iArray = NULL;	//pointer to pointer for 2D arrays

	//code
	//every row of a 2D array is an integer array itself comprising og NUM_COLUMNS elements
	//there are 5 rows & 3 columns in a 2D int array, each of this 5 rowa is a 1D array of 3 integers
	//hence, each of these 5 rows themselves being arrays of 3 elements, will be the base addr of their rows

	//MEMORY ALLOCATION
	printf("\n\n");
	ptr_for_iArray = (int **)malloc(NUM_ROWS * sizeof(int *)); //ptr_for_iArray is the name & base addr of 1D array
	//containing 5 int pointers to 5 integer arrays of 3 elements each, so it is an array containing of data type (int *)

	if(ptr_for_iArray == NULL)
	{
		printf("Memory allocation for 1D array of base addr of %d rows FAILED, exiting now!\n\n", NUM_ROWS);
		exit(0);
	}
	else
	{
		printf("Memory allocation for 1D array of base addr of %d rows SUCCEEDED!\n\n", NUM_ROWS);
	}

	//allocating memory to each row
	for(i = 0; i < NUM_ROWS; i++)
	{
		ptr_for_iArray[i] = (int*)malloc(NUM_COLUMNS * sizeof(int)); 	//ptr_for_iArray[i] is base addr of ith row
		if(ptr_for_iArray == NULL)
		{
			printf("Memory allocation for columns of row %d FAILED, exiting now!\n\n", i);
			exit(0);
		}
		else
		{
			printf("Memory allocation for columns of row %d SUCCEEDED!\n\n", i);

		}
	}

	//assigning values
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			*(*(ptr_for_iArray + i) + j) = (i + 1) * (j + 1);	//same as ptr_for_iArray[i][j] = (i + 1) * (j + 1);
		}
	}

	//displaying values
	printf("\n\n");
	printf("2D integer array elements along with addresses : \n\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("ptr_for_iArray[%d][%d] = %d \t at addr &ptr_for_iArray[%d][%d] : %p\n", i, j, ptr_for_iArray[i][j], i, j, &ptr_for_iArray[i][j]);
		}
		printf("\n\n");
	}

	//freeing allocated memory
	for( i = (NUM_ROWS - 1); i >= 0; i--)
	{
		if(*(ptr_for_iArray + 1))	//same as if(ptr_for_iArray[i])
		{
			free(*(ptr_for_iArray + i)); //free(ptr_for_iArray[i])
			*(ptr_for_iArray + i) = NULL; //ptr_for_iArray[i] = NULL;
			printf("Memory allocated for row %d FREED!\n", i);
		}
	}

	//freeing memory for pointers of ptr_for_iArray which is the array of 5 integer ptrs i.e it is an array of 5 int addr (TYPE int*)
	printf("\n\n");
	if(ptr_for_iArray)
	{
		free(ptr_for_iArray);
		ptr_for_iArray = NULL;
			printf("Memory allocated for ptr_for_iArray FREED!\n", i);

	}
	return(0);	
}
