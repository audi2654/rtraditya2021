//C Pointers assignment : Array Pointer Representation
//Program to represent a 2D array using array name as pointer

#include <stdio.h>
#include <stdlib.h> 	

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int amp_iArray[NUM_ROWS][NUM_COLUMNS];
	int i, j;

	//code
	//every row of a 2D array is an integer array itself comprising og NUM_COLUMNS elements
	//there are 5 rows & 3 columns in a 2D int array, each of this 5 rowa is a 1D array of 3 integers
	//hence, each of these 5 rows themselves being arrays of 3 elements, will be the base addr of their rows 

	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			*(amp_iArray[i] + j) = (i + 1) * (j + 1);	//amp_iArray[i] can be treated as 1D array using pointers
		}
	}

	printf("\n\n");
	printf("2D integer array elements along with addresses : \n\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("*(amp_iArray[%d] + %d) = %d \t at addr (amp_iArray[i] + j) : %p\n", i, j, *(amp_iArray[i] + j), (amp_iArray[i] + j));
		}
		printf("\n\n");
	}

	return(0);	
}
