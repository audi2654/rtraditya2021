//C Pointers assignment : Malloc & free
//Program to show working of malloc() & free()

#include <stdio.h>
#include <stdlib.h> 	//contains prototypes for malloc() & free()

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int *ptr_iArray = NULL;	//pointers should be initialized with NULL address to prevent any garbage value
	//getting into it, also it gets easy to check if memory allocation is successful or failed later after malloc()

	unsigned int amp_intArrayLength = 0;
	int i;

	//code
	printf("\n\n");
	printf("Enter number of elements in int array : ");
	scanf("%d", &amp_intArrayLength);

	//allocating as much memory required to the int array
	//memory required for int array = sizeof(int) * number of elements in array

	//to dynamically (runtime) allocate the total memory required, function malloc() is used
	//malloc() allocates the required amount of memory & returns the initial/starting/base address
	//of the allocated memory, which must be captured in the pointer variable
	//using this base addr, the whole int array can be accesed, modified & used

	ptr_iArray = (int *)malloc(sizeof(int) * amp_intArrayLength);
	if(ptr_iArray == NULL)	//if ptr_iArray is still NULL after malloc() call, it means malloc() failed to allocate
	//memory & no address has been returned by malloc() in ptr_iArray
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FAILED, EXITING NOW\n");
		exit(0);
	}
	else	//if ptr_iArray is NOT NULL, it means memory allocation by malloc() was successful
	//and ptr_iArray now has a valid base addr for int array
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION SUCCESSFUL\n");
		printf("Memory addr from %p to %p has been allocated for int array\n\n", ptr_iArray, (ptr_iArray + (amp_intArrayLength - 1)));
	}

	printf("\n\n");
	printf("Enter %d elements for int array : \n", amp_intArrayLength);
	for(i = 0; i < amp_intArrayLength; i++)
		scanf("%d", (ptr_iArray + i));

	printf("\n\n");
	printf("Entered int array consisting of %d elements is :\n", amp_intArrayLength);
	for(i = 0; i < amp_intArrayLength; i++)
	{
		printf("ptr_iArray[%d] = %d \t at addr &ptr_iArray[%d] : %p\n", i , ptr_iArray[i], i, &ptr_iArray[i]);
	}

	//printing by other way
	printf("\n\n");
	for(i = 0; i < amp_intArrayLength; i++)
	{
		printf("(ptr_iArray + %d) = %d \t at addr (ptr_iArray + %d) : %p\n", i , *(ptr_iArray + i), i, (ptr_iArray + i));
	}

	//checking if memory is still allicated by checking validity of base addr ptr_iArray
	//if addr is valid, then addr exits & is not null, means memory is still allocated
	//in that case once memory is used, it must be released/freed using free() function
	//once freed the base addr must be reiniatilized to null to keep away garbage values

	if(ptr_iArray)
	{
		free(ptr_iArray);
		ptr_iArray = NULL;

		printf("\n\n");
		printf("Memory allocated has been FREED successfully\n\n");
	}

	return(0);
}
