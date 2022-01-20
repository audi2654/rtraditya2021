//C Pointers assignment : Functions
//Program to show use of pointer as an out parameter - method 2

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	//func signature
	void MathOps(int, int, int*, int *, int*, int *, int*);

	int a;
	int b;
	int *AnswerAdd = NULL;
	int *AnswerSubtract = NULL;
	int *AnswerMultiply = NULL;
	int *AnswerQuotient = NULL;
	int *AnswerRemainder = NULL;

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

	//allocating memories to pointers to hold results
	AnswerAdd = (int*)malloc(1 * sizeof(int));
	if(AnswerAdd == NULL)
	{
		printf("Memory allocation for AnswerAdd FAILED, exiting now\n");
		exit(0);
	}

	AnswerSubtract = (int*)malloc(1 * sizeof(int));
	if(AnswerSubtract == NULL)
	{
		printf("Memory allocation for AnswerSubtract FAILED, exiting now\n");
		exit(0);
	}

	AnswerMultiply = (int*)malloc(1 * sizeof(int));
	if(AnswerMultiply == NULL)
	{
		printf("Memory allocation for AnswerMultiply FAILED, exiting now\n");
		exit(0);
	}

	AnswerQuotient = (int*)malloc(1 * sizeof(int));
	if(AnswerQuotient == NULL)
	{
		printf("Memory allocation for AnswerQuotient FAILED, exiting now\n");
		exit(0);
	}

	AnswerRemainder = (int*)malloc(1 * sizeof(int));
	if(AnswerRemainder == NULL)
	{
		printf("Memory allocation for AnswerRemainder FAILED, exiting now\n");
		exit(0);
	}

	MathOps(a, b, AnswerAdd, AnswerSubtract, AnswerMultiply, AnswerQuotient, AnswerRemainder);

	printf("\n\n");
	printf("RESULTS : \n\n");
	printf("ADDITION = %d\n", *AnswerAdd);
	printf("SUBTRACTION = %d\n", *AnswerSubtract);
	printf("MULTIPLICATION = %d\n", *AnswerMultiply);
	printf("QUOTIENT = %d\n", *AnswerQuotient);
	printf("REMAINDER = %d\n", *AnswerRemainder);

	printf("\n\n");

	if(AnswerRemainder)
	{
		free(AnswerRemainder);
		AnswerRemainder = NULL;
		printf("Memory allocated for AnswerRemainder FREED successfully\n");
	}

	if(AnswerQuotient)
	{
		free(AnswerQuotient);
		AnswerQuotient = NULL;
		printf("Memory allocated for AnswerQuotient FREED successfully\n");
	}

	if(AnswerMultiply)
	{
		free(AnswerMultiply);
		AnswerMultiply = NULL;
		printf("Memory allocated for AnswerMultiply FREED successfully\n");
	}

	if(AnswerSubtract)
	{
		free(AnswerSubtract);
		AnswerSubtract = NULL;
		printf("Memory allocated for AnswerSubtract FREED successfully\n");
	}

	if(AnswerAdd)
	{
		free(AnswerAdd);
		AnswerAdd = NULL;
		printf("Memory allocated for AnswerAdd FREED successfully\n");
	}

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
