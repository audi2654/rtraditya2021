//C Pointers assignment : Constants
//Program to show non-constant variable pointer to a integer constant type

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int ampNum = 5;
	const int* ptr = NULL;	
	//read as from right to left : "ptr is a (non-constant) pointer(*) variable to integer constant"

	//code
	ptr = &ampNum;

	printf("\n\n");
	printf("Current value of ampNum = %d\n", ampNum);
	printf("Current value of ptr i.e addr of ampNum = %p\n", ptr);

	//modifying the value of var individually, its value is independent, so no error
	ampNum++;
	printf("After ampNum++, value of ampNum = %d\n", ampNum);

	//the following line gives error
	//with respect to pointer, the ptr thinks that the value to which it points is constant
	//hence we cannot alter the value at address stored in 'a pointer to constant integer' using the pointer var itself
	// (*ptr)++;	 //with respect to ptr, the value at dereferenced addr should be const
	// ++*ptr;	//is also not possible
	//although just *ptr++; without brackets is possible due to right to left associativity
	
	//the following line does NOT gives error
	//we get no error becaue we are changing the addr of pointer, not its value or addr which is stored in ptr
	//here pointer variable is not constant, ptr thinks that the variable or value at addr to which it points is constant
	ptr++;

	printf("\n\n");
	printf("After ptr++, value of 'ptr' = %p\n", ptr);
	printf("Value at this new addr of 'ptr' = %d\n\n", *ptr);

	return(0);
}

//CONCLUSION
//as 'ptr' is a 'variable pointer to constant integer' - we can change the value of pointer 'ptr'

//we can change the value of var (ampNum) individually, independently whose addr is contained in 'ptr'
//but we cannot change the value of var (ampNum) through or using the 'ptr' i.e 'variable pointer to constant integer'
//hence (*ptr)++; this doesn't work

//in short, we can't change the value at addr of ptr, we can't change the value of 'ampNum' with respect to 'ptr
//cuz 'ptr' thinks that it is pointing to a const value, so (*ptr++) is not allowed

//but we can change the addr of 'ptr' itself so ptr++ or ++ptr is allowed
