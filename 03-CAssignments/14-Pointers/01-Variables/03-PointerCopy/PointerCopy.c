//C Pointers assignment : Pointer Copy
//Program to copying the value of a pointer var in another pointer var

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int ampNum;
    int *ptr = NULL;
    int *copy_of_ptr = NULL;

    //code
    ampNum = 5;
    ptr = &ampNum;

    printf("\n\n");
    printf("ampNum          = %d\n", ampNum);           //value of ampNum
    printf("&ampNum         = %p\n", &ampNum);          //address of ampNum
    printf("*(&ampNum)      = %d\n", *(&ampNum));       //value at address of ampNum  
    printf("ptr             = %p\n", ptr);              //value of ptr
    printf("*ptr            = %d\n", *ptr);             //value at ptr, ptr=&ampNum hence value at addr of ampNum

    //'ptr' is an integer pointer var, that can hold the address of any integer var only
    //'copy_of_ptr' is another integer pointer var
    //if ptr = &ampNum, 'ptr' will contain address of integer var 'ampNum'
    //if 'ptr' is assigned to 'copy_of_ptr', 'copy_of_ptr' will also contain addr of int var 'ampNum'
    //hence both ptr & copy_of_ptr will point to ampNum

    copy_of_ptr = ptr;  //copy_of_ptr = ptr = &ampNum

    printf("\n\n");
    printf("After copy_of_ptr = ptr\n");
	printf("ampNum          = %d\n", ampNum);           //value of ampNum
    printf("&ampNum         = %p\n", &ampNum);          //address of ampNum
    printf("*(&ampNum)      = %d\n", *(&ampNum));       //value at address of ampNum  
    printf("ptr             = %p\n", ptr);              //value of ptr
    printf("*ptr            = %d\n", *ptr);             //value at ptr, ptr=&ampNum hence value at addr of ampNum 

	printf("copy_of_ptr             = %p\n", copy_of_ptr);  	//value of copy_of_ptr
    printf("*copy_of_ptr            = %d\n\n", *copy_of_ptr);  
	//value at copy_of_ptr, copy_of_ptr=ptr=&ampNum hence value at addr of ampNum

	return(0);
}
