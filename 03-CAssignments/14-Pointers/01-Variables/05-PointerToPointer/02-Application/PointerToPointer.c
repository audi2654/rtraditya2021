//C Pointers assignment : Pointer to pointer
//Program to show working of pointer to pointer variable
#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int ampNum;
	int *ptr = NULL;
	int **pptr = NULL;	//declaration method 1 - **pptr is a variable of type int

	//code
	ampNum = 99;

	printf("\n\n");
	printf("Before ptr = &ampNum\n");
	printf("Value of ampNum					= %d\n", ampNum);
	printf("Address of ampNum				= %p\n", &ampNum);
	printf("Value at address of ampNum			= %d\n", *(&ampNum));

	//assigning addr of var ampNum to pointer var ptr
	//ptr now contains addr of ampNum hence, ptr is same as &ampNum
	ptr = &ampNum;

	printf("\n\n");
	printf("After ptr = &ampNum\n");
	printf("Value of ampNum					= %d\n", ampNum);
	printf("Address of ptr					= %p\n", &ptr);
	printf("Value at address of ampNum (*ptr)		= %d\n", *ptr);

	//assigning addr of var ampNum to pointer to pointer var pptr
	//pptr now contains addr of ptr which in turn has address of ampNum
	//hence pptr is same as &ptr & ptr is same as &ampNum
	//pptr = &ptr = &(&ampNum)

	//if ptr = &ampNum and *ptr = *(&ampNum) = value at addr of ampNum
	//then pptr = &ptr and *pptr = *(&ptr) = ptr = value at addr of ptr i.e ptr i.e addr of num
	//then **pptr = **(&ptr) = *(*(&ptr)) = *ptr = *(&ampNum) = ampNum = 10
	//hence, ampNum = *(&ampNum) = *ptr = *(*pptr) = **pptr
	pptr = &ptr;

	printf("\n\n");
	printf("After pptr = &ampNum\n");

	printf("Value of ampNum	(ptr)				= %d\n", ampNum);
	printf("Address of ampNum (ptr)				= %p\n", ptr);
	printf("Address of ptr (pptr)				= %p\n", pptr);
	printf("Value at address of ptr (*pptr)			= %p\n", *pptr);
	printf("Value at address of ampNum (*ptr) (**pptr)	= %d\n", **pptr);

	return(0);
}
