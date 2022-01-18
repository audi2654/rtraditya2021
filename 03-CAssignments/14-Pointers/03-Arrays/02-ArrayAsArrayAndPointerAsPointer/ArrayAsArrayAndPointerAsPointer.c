//C Pointer Arrays assignment : Arrays & Pointers
//Program to show use of pointer on an array

//name of an array is its own base address

#include <stdio.h>

int main(void)
{
	//var decl.
	int amp_iArray[] = {1,2,3,4,5,6,7};		//normal integer array
	int *ptr_for_iArray = NULL;		//normal integer pointer

	//code

	//using the name of array as an array
	printf("\n\n");
	printf("Using the name of array as an array\n");
	printf("Integer array elements & their addresses are :\n");
	printf("amp_iArray[0] = %d \t at address &amp_iArray[0] : %p\n", (amp_iArray[0]), (&amp_iArray[0]));
	printf("amp_iArray[1] = %d \t at address &amp_iArray[1] : %p\n", (amp_iArray[1]), (&amp_iArray[1]));
	printf("amp_iArray[2] = %d \t at address &amp_iArray[2] : %p\n", (amp_iArray[2]), (&amp_iArray[2]));
	printf("amp_iArray[3] = %d \t at address &amp_iArray[3] : %p\n", (amp_iArray[3]), (&amp_iArray[3]));
	printf("amp_iArray[4] = %d \t at address &amp_iArray[4] : %p\n", *(amp_iArray + 4), (amp_iArray + 4));
	printf("amp_iArray[5] = %d \t at address &amp_iArray[5] : %p\n", *(amp_iArray + 5), (amp_iArray + 5));
	printf("amp_iArray[6] = %d \t at address &amp_iArray[6] : %p\n", *(amp_iArray + 6), (amp_iArray + 6));

	//using the pointer as an array & accessing the int array
	//assigning base address of int array to int ptr
	ptr_for_iArray = amp_iArray; 		//same as ptr_for_iArray = &amp_iArray[0]
	
	printf("\n\n");
	printf("Using the pointer as an array & accessing the int array\n");
	printf("Integer array elements & their addresses are :\n");
	printf("*(ptr_for_iArray + 0) = %d \t at address (ptr_for_iArray + 0) : %p\n", *(ptr_for_iArray + 0), (ptr_for_iArray + 0));
	printf("*(ptr_for_iArray + 1) = %d \t at address (ptr_for_iArray + 1) : %p\n", *(ptr_for_iArray + 1), (ptr_for_iArray + 1));
	printf("*(ptr_for_iArray + 2) = %d \t at address (ptr_for_iArray + 2) : %p\n", *(ptr_for_iArray + 2), (ptr_for_iArray + 2));
	printf("*(ptr_for_iArray + 3) = %d \t at address (ptr_for_iArray + 3) : %p\n", *(ptr_for_iArray + 3), (ptr_for_iArray + 3));
	printf("*(ptr_for_iArray + 4) = %d \t at address (ptr_for_iArray + 4) : %p\n", *(ptr_for_iArray + 4), (ptr_for_iArray + 4));
	printf("*(ptr_for_iArray + 5) = %d \t at address (ptr_for_iArray + 5) : %p\n", *(ptr_for_iArray + 5), (ptr_for_iArray + 5));
	printf("*(ptr_for_iArray + 6) = %d \t at address (ptr_for_iArray + 6) : %p\n", *(ptr_for_iArray + 6), (ptr_for_iArray + 6));

	return 0;
}
