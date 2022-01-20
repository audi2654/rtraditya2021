//C Pointers assignment : Malloc & free
//Program to show working of user defined arrays using malloc() & free()

#include <stdio.h>
#include <stdlib.h> 	//contains prototypes for malloc() & free()

#define INT_SIZE sizeof(int)
#define FLOAT_SIZE sizeof(float)
#define DOUBLE_SIZE sizeof(double)
#define CHAR_SIZE sizeof(char)

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int *ptr_iArray = NULL;	//pointers should be initialized with NULL address to prevent any garbage value
	//getting into it, also it gets easy to check if memory allocation is successful or failed later after malloc()
	unsigned int amp_intArrayLength = 0;
	
	float* ptr_fArray = NULL;
	unsigned int amp_floatArrayLength = 0;

	double *ptr_dArray = NULL;
	unsigned int amp_doubleArrayLength = 0;

	char* ptr_cArray = NULL;
	unsigned int amp_charArrayLength = 0;

	int i;

	//code
	//integer array
	printf("\n\n");
	printf("Enter number of elements in int array : ");
	scanf("%u", &amp_intArrayLength);

	ptr_iArray = (int *)malloc(INT_SIZE * amp_intArrayLength);
	if(ptr_iArray == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FAILED, EXITING NOW\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR INT ARRAY SUCCESSFUL\n");
	}

	printf("\n\n");
	printf("Enter %d elements for int array : \n", amp_intArrayLength);
	for(i = 0; i < amp_intArrayLength; i++)
		scanf("%d", (ptr_iArray + i));

	//float array
	printf("\n\n");
	printf("Enter number of elements in float array : ");
	scanf("%d", &amp_floatArrayLength);

	ptr_fArray = (float *)malloc(FLOAT_SIZE * amp_floatArrayLength);
	if(ptr_fArray == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FAILED, EXITING NOW\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR FLOAT ARRAY SUCCESSFUL\n");
	}

	printf("\n\n");
	printf("Enter %d elements for float array : \n", amp_floatArrayLength);
	for(i = 0; i < amp_floatArrayLength; i++)
		scanf("%f", (ptr_fArray + i));


	//double array
	printf("\n\n");
	printf("Enter number of elements in double array : ");
	scanf("%i", &amp_doubleArrayLength);

	ptr_dArray = (double *)malloc(DOUBLE_SIZE * amp_doubleArrayLength);
	if(ptr_dArray == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FAILED, EXITING NOW\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR DOUBLE ARRAY SUCCESSFUL\n");
	}

	printf("\n\n");
	printf("Enter %d elements for double array : \n", amp_doubleArrayLength);
	for(i = 0; i < amp_doubleArrayLength; i++)
		scanf("%lf", (ptr_dArray + i));


	//char array
	printf("\n\n");
	printf("Enter number of elements in char array : ");
	scanf("%i", &amp_charArrayLength);

	ptr_cArray = (char *)malloc(DOUBLE_SIZE * amp_charArrayLength);
	if(ptr_cArray == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FAILED, EXITING NOW\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR CHAR ARRAY SUCCESSFUL\n");
	}

	printf("\n\n");
	printf("Enter %d elements for char array : \n", amp_charArrayLength);
	for(i = 0; i < amp_charArrayLength; i++)
	{
		*(ptr_cArray + i) = getch();
		printf("%c\n", *(ptr_cArray + i));
	}

	//displaying all arrays

	//integer array
	printf("\n\n");
	printf("Entered int array consisting of %d elements is :\n", amp_intArrayLength);
	for(i = 0; i < amp_intArrayLength; i++)
	{
		printf("%d \t at addr %p\n", *(ptr_iArray + i), (ptr_iArray + i));
	}

	//float array
	printf("\n\n");
	printf("Entered float array consisting of %d elements is :\n", amp_floatArrayLength);
	for(i = 0; i < amp_floatArrayLength; i++)
	{
		printf("%f \t at addr %p\n", *(ptr_fArray + i), (ptr_fArray + i));
	}

	//double array
	printf("\n\n");
	printf("Entered double array consisting of %d elements is :\n", amp_doubleArrayLength);
	for(i = 0; i < amp_doubleArrayLength; i++)
	{
		printf("%lf \t at addr %p\n", *(ptr_dArray + i), (ptr_dArray + i));
	}

	//char array
	printf("\n\n");
	printf("Entered char array consisting of %d elements is :\n", amp_charArrayLength);
	for(i = 0; i < amp_charArrayLength; i++)
	{
		printf("%c \t at addr %p\n", *(ptr_cArray + i), (ptr_cArray + i));
	}

	//freeing memory occupied by arrays (in reverse order of allocation)
	if(ptr_cArray)
	{
		free(ptr_cArray);
		ptr_cArray = NULL;

		printf("\n\n");
		printf("Memory allocated for char has been FREED successfully\n\n");
	}

	if(ptr_dArray)
	{
		free(ptr_dArray);
		ptr_dArray = NULL;

		printf("\n\n");
		printf("Memory allocated for double has been FREED successfully\n\n");
	}

	if(ptr_fArray)
	{
		free(ptr_fArray);
		ptr_fArray = NULL;

		printf("\n\n");
		printf("Memory allocated for float has been FREED successfully\n\n");
	}

	if(ptr_iArray)
	{
		free(ptr_iArray);
		ptr_iArray = NULL;

		printf("\n\n");
		printf("Memory allocated for int has been FREED successfully\n\n");
	}

	return(0);
}
