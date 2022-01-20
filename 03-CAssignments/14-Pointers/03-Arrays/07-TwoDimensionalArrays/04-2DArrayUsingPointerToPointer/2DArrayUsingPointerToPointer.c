//C Pointers assignment : 2D Array
//Program to create an array using pointer to pointer

#include <stdio.h>
#include <stdlib.h> 	

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int **ptr_for_iArray = NULL;	//a pointer to pointer to int, can also hold base addr of a 2D array which
	//can have n number of rows & n number of columns
	int i, j;
	int num_rows, num_columns;

	//code
	//accept no. of rows
	printf("\n\n");
	printf("Enter number of rows : ");
	scanf("%d", &num_rows);

	//accept no. of columns
	printf("\n\n");
	printf("Enter number of columns : ");
	scanf("%d", &num_columns);

	//allocating memory to 2D int array
	printf("\n\n");
	ptr_for_iArray = (int**)malloc(num_rows * sizeof(int *));
	if(ptr_for_iArray == NULL)
	{
		printf("memory allocation for %d rows of 2D int array FAILED, exiting now\n\n", num_rows);
		exit(0);
	}
	else
	{
		printf("memory allocation for %d rows of 2D int array SUCCESSFUL\n\n", num_rows);
	}
	
	//allocating memory to each row which is a 1D int array consisting of columns which contain the actual integers
	for(i = 0; i < num_rows; i++)
	{
		ptr_for_iArray[i] = (int *)malloc(num_columns * sizeof(int));	//allocating memory to row 'i'
		if(ptr_for_iArray[i] == NULL)
		{
			printf("memory allocation for columns of row %d of 2D int array FAILED, exiting now\n\n", i);
			exit(0);
		}
		else
		{
			printf("memory allocation for columns of row %d of 2D int array SUCCESSFUL\n\n", i);
		}
	}

	//assigning values to 2D array
	for(i = 0; i < num_rows; i++)
	{
		for(j = 0; j < num_columns; j++)
		{
			ptr_for_iArray[i][j] = (i + 1) * (j + 1);	//same as *(*(ptr_for_iArray + i) + j) = (i + 1) * (j + 1);
		}
	}

	//displaying values
	for(i = 0; i < num_rows; i++)
	{
		printf("Base addr of row %d : ptr_for_iArray[%d] = %p \t at addr : %p\n", i , i, ptr_for_iArray[i], &ptr_for_iArray[i]);
	}

	//displaying 2D array
	printf("\n\n");
	printf("Displaying 2D array:\n");
	for(i = 0; i < num_rows; i++)
	{
		for(j = 0; j < num_columns; j++)
		{
			printf("ptr_for_iArray[%d][%i] = %d \t at addr : %p\n", i, j, ptr_for_iArray[i][j], &ptr_for_iArray[i][j]);
			//same as *(*(ptr_for_iArray + i) + j) for value and (*(ptr_for_iArray + i) + j) for addr
		}
		printf("\n");
	}
	printf("\n\n");

	//freeing memory assigned to 2D array in reverse
	for(i = (num_rows - 1); i >= 0; i--)
	{
		if(ptr_for_iArray[i])
		{
		free(ptr_for_iArray[i]);
		ptr_for_iArray[i] = NULL;
		printf("memory allocated for row %d of 2D int array SUCCESSFULLY FREED\n\n", i);
		}
	}

	//freeing memory assigned to 1D array in reverse
	if(ptr_for_iArray)
	{
	free(ptr_for_iArray);
	ptr_for_iArray = NULL;
	printf("memory allocated for ptr_for_iArray SUCCESSFULLY FREED\n\n", i);
	}

	return(0);
}
