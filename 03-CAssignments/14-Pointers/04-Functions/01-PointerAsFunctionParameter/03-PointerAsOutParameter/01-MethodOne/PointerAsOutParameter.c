//C Pointers assignment : Functions
//Program to show use of pointer as an out parameter

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	//func signature
	void MathOps(int, int, int*, int *, int*, int *, int*);

	int a;
	int b;
	int AnswerAdd;
	int AnswerSubtract;
	int AnswerMultiply;
	int AnswerQuotient;
	int AnswerRemainder;

	//code
	printf("\n\n");
	printf("Enter value of 'a' : ");
	scanf("%d", &a);

	printf("Enter value of 'b' : ");
	scanf("%d", &b);

	//passing addresses to function, function will fill them up with values, hence they go into the function as
	//addr parameters and come out of the function filled with valid values

	//thus, (&answerAdd, &answerSubtract, &answerMultiply, &AnswerQuotient, &AnswerRemainder) are called
	//'OUT PARAMETERS' or 'PARAMETERIZED RETURN VALUES' i.e return values of functions coming via parameters
	//i.e sending empty parameters while func starts & when func ends getting those empty paras filled with results
	//& considering them as return values

	//hence although every func returns only one value, using this concept of 'OUT PARAMETERS' or 'PARAMETERIZED RETURN VALUES'
	//MathOps func gives 5 return values

	MathOps(a, b, &AnswerAdd, &AnswerSubtract, &AnswerMultiply, &AnswerQuotient, &AnswerRemainder);

	printf("\n\n");
	printf("RESULTS : \n\n");
	printf("ADDITION = %d\n", AnswerAdd);
	printf("SUBTRACTION = %d\n", AnswerSubtract);
	printf("MULTIPLICATION = %d\n", AnswerMultiply);
	printf("QUOTIENT = %d\n", AnswerQuotient);
	printf("REMAINDER = %d\n", AnswerRemainder);

	return(0);	
}

//function definition
void MathOps(int x, int y, int *sum, int* difference, int *product, int* quotient, int *remainder)
{
	//code
	*sum = x + y;
	*difference = x - y;
	*product = x * y;
	*quotient = x / y;
	*remainder = x % y;
}
