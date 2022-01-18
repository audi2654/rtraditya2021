//C Pointer Arrays assignment : Arrays & Pointers
//Program to display addresses of array

//name of an array is its own base address

#include <stdio.h>

int main(void)
{
	//var decl.
	int amp_iArray[10];
	int i;

	//code
	for(i = 0; i < 10; i++)
		amp_iArray[i] = (i + 1) * 3;

	printf("\n\n");
	printf("Elements of the integer array : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_iArray[%d] = %d\n", i, amp_iArray[i]);

	printf("\n\n");
	printf("Elements of the integer array & addresses : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_iArray[%d] = %d \t address = %p\n", i, amp_iArray[i], &amp_iArray[i]);
	
	return 0;
}
