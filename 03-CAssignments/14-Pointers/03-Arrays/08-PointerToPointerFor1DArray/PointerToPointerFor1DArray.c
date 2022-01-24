//C Pointers assignment : Ptr to Ptr for 1D Array
//Program to create an array using pointer to pointer

#include <stdio.h>
#include <stdlib.h> 	

int main(int argc, char* argv[], char* envp[])
{
	//func declaration
	void ampAlloc(int **ptr, unsigned int numOfElements);

	//var decl.
	int *ptr_for_iArray = NULL;
	unsigned int numElements;
	int i;

	//code
	printf("\n\n");
	printf("How many elements wanted in integer array ? : ");
	scanf("%u", &numElements);

	printf("\n\n");
	ampAlloc(&ptr_for_iArray, numElements);

	printf("Enter %u elements to fill up int array :\n", numElements);
	for(i = 0; i < numElements; i++)
	{
		scanf("%d", &ptr_for_iArray[i]);
	}

	printf("\n\n");
	printf("Entered %u elements by you in int array are :\n", numElements);
	for(i = 0; i < numElements; i++)
	{
		printf("%i\n", ptr_for_iArray[i]);
	}

	printf("\n\n");
	if(ptr_for_iArray)
	{
		free(ptr_for_iArray);
		ptr_for_iArray = NULL;
		printf("Memory allocated to ptr_for_iArray FREED\n\n");
	}

	return(0);
}

//function definition
void ampAlloc(int **ptr, unsigned int numOfElements)
{
	//code
	*ptr = (int *)malloc(numOfElements * sizeof(int));
	if(*ptr == NULL)
	{
		printf("Could not allocate memory, bye\n\n");
		exit(0);
	}
	printf("ampAlloc() successfully allocated %lu bytes memory for int array\n\n", (numOfElements * sizeof(int)));
}
