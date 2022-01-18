//C Pointers assignment : Brackets & Pointer Operations
//Program to show how brackets around pointers & pointer operations work

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
	int ampNum;
	int *ptr = NULL;
	int ans;

	//code
	ampNum = 5;
	ptr = &ampNum;

	printf("\n\n");
    printf("ampNum          = %d\n", ampNum);           //value of ampNum
    printf("&ampNum         = %p\n", &ampNum);          //address of ampNum
    printf("*(&ampNum)      = %d\n", *(&ampNum));       //value at address of ampNum  
    printf("ptr             = %p\n", ptr);              //value of ptr
    printf("*ptr            = %d\n", *ptr);             //value at ptr, ptr=&ampNum hence value at addr of ampNum

	printf("\n\n");

	//add 10 to ptr which is the address of ampNum (remember ptr=&ampNum)
	//10 will be added to the address of ampNum & not the value of ampNum, hence resultant new addr is displayed
	printf("Answer of (ptr+10) = %p\n", (ptr+10));

	//add 10 to ptr which is the address of ampNum (remember ptr=&ampNum) & displaying value at that address 
	//10 will be added to the address of ampNum & not the value of ampNum, hence resultant new addr is displayed
	//& value at that new addr may be some garbage
	printf("Answer of *(ptr+10) = %d\n", *(ptr+10));	//dereferencing the pointer to display value at (addr of ampNum+10) addr

	//add 10 to *ptr which is the value at address of ampNum (remember ptr=&ampNum) & displaying new value without changing address
	//10 will be added to the value at address of ampNum i.e 5+10 &, hence resultant new value is displayed on same addr
	printf("Answer of (*ptr+10) = %d\n", (*ptr+10));	//dereferencing the pointer first & then adding 10


	//Associativity of '*' (value at address operator) and '++' and '--' operators is from RIGHT to LEFT
	//LEFT <------ RIGHT

	//RIGHT to LEFT	: PREINCREMENT *ptr i.e value at addr 'ptr' is preincremented as (++*ptr)
	++*ptr; //*ptr is preincremented, i.e *ptr=5 now becomes 6
	printf("Answer of ++*ptr = %d\n", *ptr); //brackets not necessary to preincrement / predecrement

	//RIGHT to LEFT	: POSTINCREMENT *ptr i.e value at addr 'ptr' is postincremented as (*ptr++)
	*ptr++; //due to right to left associativity, here ptr (i.e &ampNum) means stored address is first incremented 
	//& then that addr is derefenrenced, since here some other addr is getting dereferenced, a garbage value might be displayed
	//INCORRRECT way to POSTINCREMENT a pointer
	printf("Answer of *ptr++ = %d\n", *ptr); //brackets are necessary to postincrement / postdecrement

	ptr = &ampNum;
	
	//RIGHT to LEFT	: POSTINCREMENT *ptr i.e value at addr 'ptr' is postincremented as (*ptr)++
	(*ptr)++; //CORRECT way to POSTINCREMENT a pointer, here due to brackets first ptr is deferenced 
	//& then value at derefenced addr is postincremented
	//at this point *ptr is 6, at next statement it'll be 7
	printf("Answer of (*ptr)++ = %d\n", *ptr); //brackets are necessary to postincrement / postdecrement

	return(0);
}
