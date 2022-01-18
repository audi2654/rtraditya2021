//C Pointer Arrays assignment : Arrays & Pointers
//Program to display addresses of array

//name of an array is its own base address

#include <stdio.h>

int main(void)
{
	//var decl.
	char amp_cArray[10];
	char *ptr_cArray = NULL;
	int i;

	//code
	for(i = 0; i < 10; i++)
		amp_cArray[i] = (char)(i + 65);

	//assigning base addr of array to ptr
	ptr_cArray = amp_cArray;

	printf("\n\n");
	printf("Elements of the char array : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_cArray[%d] = %c\n", i, *(ptr_cArray + i));

	printf("\n\n");
	printf("Elements of the char array & addresses : \n\n");
	for(i = 0; i < 10; i++)
		printf("amp_cArray[%d] = %c \t address = %p\n", i, *(ptr_cArray + i), (ptr_cArray + i));
	
	return 0;
}
