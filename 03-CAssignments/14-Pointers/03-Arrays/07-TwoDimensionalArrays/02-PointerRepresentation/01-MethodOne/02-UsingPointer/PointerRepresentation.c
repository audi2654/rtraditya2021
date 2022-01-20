//C Pointers assignment : Array Pointer Representation
//Program to represent a 2D array using seperate pointer

#include <stdio.h>
#include <stdlib.h> 	

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int amp_iArray[NUM_ROWS][NUM_COLUMNS];
	int i, j;

	int *ptr_for_iArray_Row = NULL;

	//code
	//every row of a 2D array is an integer array itself comprising og NUM_COLUMNS elements
	//there are 5 rows & 3 columns in a 2D int array, each of this 5 rowa is a 1D array of 3 integers
	//hence, each of these 5 rows themselves being arrays of 3 elements, will be the base addr of their rows 

	for(i = 0; i < NUM_ROWS; i++)
	{
		ptr_for_iArray_Row = amp_iArray[i];		//amp_iArray[i] is base addr of ith row
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			*(ptr_for_iArray_Row + j) = (i + 1) * (j + 1);	//ptr_for_iArray_Row i.e amp_iArray[i] can be treated as 1D array using pointers
		}
	}

	printf("\n\n");
	printf("2D integer array elements along with addresses : \n\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		ptr_for_iArray_Row = amp_iArray[i];
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("*(ptr_for_iArray_Row + %d) = %d \t at addr (ptr_for_iArray_Row + j) : %p\n", j, *(ptr_for_iArray_Row + j), (ptr_for_iArray_Row + j));
		}
		printf("\n\n");
	}

	return(0);	
}
