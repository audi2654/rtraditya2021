//C Pointer Arrays assignment : Arrays & Pointers
//Program to display addresses of array

//name of an array is its own base address

#include <stdio.h>

int main(void)
{
	//var decl.
	float amp_fArray[10];
	float *ptr_fArray = NULL;
	int i;

	//code
	for(i = 0; i < 10; i++)
		amp_fArray[i] = (float)(i + 1) * 2.5;

	//assigning base addr of array to ptr
	ptr_fArray = amp_fArray;

	printf("\n\n");
	printf("Elements of the float array : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_fArray[%d] = %f\n", i, *(ptr_fArray + i));

	printf("\n\n");
	printf("Elements of the float array & addresses : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_fArray[%d] = %f \t address = %p\n", i, *(ptr_fArray + i), (ptr_fArray + i));
	
	return 0;
}
