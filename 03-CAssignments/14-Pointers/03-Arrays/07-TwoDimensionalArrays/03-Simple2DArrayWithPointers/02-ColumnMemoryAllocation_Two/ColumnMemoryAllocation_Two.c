//C Pointers assignment : 2D Arrays	- B
//Program to show column memory allocation for 2D arrays using pointers

#include <stdio.h>
#include <stdlib.h> 	

#define NUM_ROWS 5
#define NUM_COLUMNS_ONE 3
#define NUM_COLUMNS_TWO 8

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int *amp_iArray[NUM_ROWS];	//a 2D array which will have 5 rows & number of columns decided later
	int i, j;

	//code
	//1 - allocating memory to an array of 5 rows with 3 int per row
	printf("\n\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		amp_iArray[i] = (int *)malloc(NUM_COLUMNS_ONE * sizeof(int));
		if(amp_iArray == NULL)
		{
			printf("memory allocation for row %d of 2D int array FAILED, exiting now\n\n", i);
			exit(0);
		}
		else
		{
			printf("memory allocation for row %d of 2D int array SUCCESSFUL\n\n", i);
		}
	}

	//assigning values to 2D array
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS_ONE; j++)
		{
			amp_iArray[i][j] = (i + 1) * (j + 1);
		}
	}

	//displaying 2D array
	printf("\n\n");
	printf("Displaying 2D array:\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS_ONE; j++)
		{
			printf("amp_iArray[%d][%i] = %u\n", i, j, amp_iArray[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");

	//freeing memory assigned to 2D array in reverse
	for(i = (NUM_ROWS - 1); i >= 0; i--)
	{
		free(amp_iArray[i]);
		amp_iArray[i] = NULL;
		printf("memory allocated for row %d of 2D int array SUCCESSFULLY FREED\n\n", i);
	}




	//2 - allocating memory to an array of 5 rows with 8 int per row
	printf("\n\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		amp_iArray[i] = (int *)malloc(NUM_COLUMNS_TWO * sizeof(int));
		if(amp_iArray == NULL)
		{
			printf("memory allocation for row %d of 2D int array FAILED, exiting now\n\n", i);
			exit(0);
		}
		else
		{
			printf("memory allocation for row %d of 2D int array SUCCESSFUL\n\n", i);
		}
	}

	//assigning values to 2D array
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS_TWO; j++)
		{
			amp_iArray[i][j] = (i + 1) * (j + 1);
		}
	}

	//displaying 2D array
	printf("\n\n");
	printf("Displaying 2D array:\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS_TWO; j++)
		{
			printf("amp_iArray[%d][%i] = %u\n", i, j, amp_iArray[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");

	//freeing memory assigned to 2D array in reverse
	for(i = (NUM_ROWS - 1); i >= 0; i--)
	{
		free(amp_iArray[i]);
		amp_iArray[i] = NULL;
		printf("memory allocated for row %d of 2D int array SUCCESSFULLY FREED\n\n", i);
	}

	return(0);
}
