//C Pointer Arrays assignment : Arrays & Pointers
//Program to display addresses of array

//name of an array is its own base address

#include <stdio.h>

int main(void)
{
	//var decl.
	double amp_dArray[10];
	int i;

	//code
	for(i = 0; i < 10; i++)
		amp_dArray[i] = (double)(i + 1) * 0.00005;

	printf("\n\n");
	printf("Elements of the double array : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_dArray[%d] = %lf\n", i, amp_dArray[i]);

	printf("\n\n");
	printf("Elements of the double array & addresses : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_dArray[%d] = %lf \t address = %p\n", i, amp_dArray[i], &amp_dArray[i]);
	
	return 0;
}
