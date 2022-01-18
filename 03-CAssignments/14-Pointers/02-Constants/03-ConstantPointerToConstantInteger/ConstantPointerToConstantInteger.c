//C Pointers assignment : Constants
//Program to show a constant pointer variable to a integer constant type

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	//var decl.
	int ampNum = 5;
	const int* const ptr = &ampNum;	
	//read as from right to left : "ptr is a constant pointer(*) variable to a constant integer type"

	//code
	//ptr = &ampNum; //this doesn't work because ptr is const so it value can be assigned/initialized only once while defining

	printf("\n\n");
	printf("Current value of ampNum = %d\n", ampNum);
	printf("Current value of ptr i.e addr of ampNum = %p\n", ptr);

	//modifying the value of var individually, its value is independent, so no error
	ampNum++;
	printf("After ampNum++, value of ampNum = %d\n", ampNum);

	//the following line GIVES ERROR
	//with respect to pointer, the ptr thinks that the value to which it points is constant
	//hence we cannot alter the value at address stored in 'a pointer to constant integer' using the pointer var itself
	// (*ptr)++;	 //with respect to ptr, the value at dereferenced addr should be const
	// ++*ptr;	//is also NOT POSSIBLE
	//just *ptr++; without brackets is NOT POSSIBLE due to right to left associativity, ptr is also const pointer variable
	
	//the following line GIVES ERROR
	//we get error becaue we are changing the addr of pointer i.e its value or addr which is stored in ptr
	//here pointer variable is constant, the variable or value at addr to which ptr points is also constant
	//ptr++;

	printf("\n\n");
	printf("After ptr++, value of 'ptr' = %p\n", ptr);
	printf("Value at this new addr of 'ptr' = %d\n\n", *ptr);

	return(0);
}

//CONCLUSION
//as 'ptr' is a 'constant pointer variable to a constant integer type' - 
//we cannot change the value of pointer 'ptr' itself & also the value at address to which it points

//we also can't change the value of var (ampNum) individually, independently whose addr is contained in 'ptr'
//we also can't change the value of var (ampNum) through or using the 'ptr' i.e 'const variable pointer to non-constant integer',
//hence (*ptr)++; this work

//in short, we can't change the value at addr of ptr, we can't change the value of 'ampNum' with respect to 'ptr
//cuz 'ptr' thinks that it is pointing to a non-const value, so (*ptr++) is allowed

//also we cannot change the addr of 'ptr' itself so ptr++ or ++ptr is not allowed
