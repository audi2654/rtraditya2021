//C Pointers assignment : Functions
//Program to swap numbers using a function without pointers

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	//func decl.
	void SwapNumbers(int, int);

	//var decl.
	int ampA, ampB;

	//code
	printf("\n\n");
	printf("Enter value for 'ampA : ");
	scanf("%d", &ampA);

	printf("Enter value for 'ampB : ");
	scanf("%d", &ampB);

	printf("\n\n");
	printf("BEFORE SWAPPING\n");
	printf("ampA = %d, ampB = %d\n", ampA, ampB);

	SwapNumbers(ampA, ampB);	//passing arguments 'by value'

	printf("\n\n");
	printf("AFTER SWAPPING\n");
	printf("ampA = %d, ampB = %d\n", ampA, ampB);
}

//function definition
void SwapNumbers(int x, int y)	//when pointers are not used, value of ampA & ampB is copied into x & y as it is
//so actual swapping takes place between x, y & not in ampA, ampB
{
	//var decl.
	int temp;

	//code
	printf("\n\n");
	printf("BEFORE SWAPPING\n");
	printf("X = %d, Y = %d\n", x, y);

	temp = x;
	x = y;
	y = temp;

	printf("\n\n");
	printf("AFTER SWAPPING\n");
	printf("X = %d, Y = %d\n", x, y);

}
