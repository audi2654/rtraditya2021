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
	//name of an array itself is its base addr
	//hence amp_iArray is base addr of 2D int array amp_iArray[][]

	//amp_iArray[5][3] means array has 5 rows & 3 columns, each of these 5 rows is a 1D int array of 3 integers
	
	//amp_iArray[0] is the 0th row, hence base addr of array at row 0
	//amp_iArray[1] is the 1st row, hence base addr of array at row 1
	//amp_iArray[4] is the 4th row, hence base addr of array at row 4

	//(amp_iArray[0] + 0) will be addr of 0th int from base of 0th row -> (amp_iArray[0][0])
	//(amp_iArray[0] + 1) will be addr of 1st int from base of 0th row -> (amp_iArray[0][1])
	//(amp_iArray[0] + 2) will be addr of 2nd int from base of 0th row -> (amp_iArray[0][2])
	//(amp_iArray[2] + 0) will be addr of 0th int from base of 2nd row -> (amp_iArray[2][0])
	//(amp_iArray[4] + 1) will be addr of 1st int from base of 4th row -> (amp_iArray[4][1])
	//and likewise

	//amp_iArray[0], amp_iArray[1]...amp_iArray[4] are 1D int arrays and hence can be treated as 1D int arrays using pointers
	
	//amp_iArray is the name & base addr of whole 2D array, so we can write as below
	//(*(amp_iArray + 0) + 0) = (amp_iArray[0] + 0) = addr of 0th int from base addr of 0th row -> (amp_iArray[0] + 0) = (amp_iArray[0][0])
	//(*(amp_iArray + 0) + 1) = (amp_iArray[0] + 1) = addr of 1st int from base addr of 0th row -> (amp_iArray[0] + 1) = (amp_iArray[0][1])
	//(*(amp_iArray + 0) + 2) = (amp_iArray[0] + 2) = addr of 2nd int from base addr of 0th row -> (amp_iArray[0] + 2) = (amp_iArray[0][2])
	//(*(amp_iArray + 2) + 0) = (amp_iArray[2] + 0) = addr of 0th int from base addr of 2nd row -> (amp_iArray[2] + 0) = (amp_iArray[2][0])
	//(*(amp_iArray + 4) + 1) = (amp_iArray[4] + 1) = addr of 1st int from base addr of 4th row -> (amp_iArray[4] + 1) = (amp_iArray[4][1])
	//and likewise

	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			*(*(amp_iArray + i) + j) = (i + 1) * (j + 1);	//amp_iArray[i] can be treated as 1D array using pointers
		}
	}

	printf("\n\n");
	printf("2D integer array elements along with addresses : \n\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("(*(amp_iArray + %d) + %d) = %d \t at addr (*(amp_iArray + %d) + %d) : %p\n", i, j, *(*(amp_iArray + i) + j), i, j, (*(amp_iArray + i) + j));
		}
		printf("\n\n");
	}

	return(0);	
}
