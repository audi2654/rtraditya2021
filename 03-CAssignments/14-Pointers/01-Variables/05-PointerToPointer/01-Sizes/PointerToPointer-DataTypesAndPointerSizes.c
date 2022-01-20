//C Pointers assignment : Pointers & sizes
//Program to show pointers types & their sizes

#include <stdio.h>

struct ampEmp
{
	char name[50];
	int age;
	float salary;
	char sex;
	char marital_status;
};

int main(int argc, char* argv[], char* envp[])
{
	//code
	printf("\n\n");
	printf("Sizes of data types & pointers to those data types are : \n");
	printf("Size of (int) : %d \t Size of pointer to int (int*) : %d \t Size of pointer to pointer (int**) : %d\n\n", sizeof(int), sizeof(int*), sizeof(int**));
	printf("Size of (float) : %d \t Size of pointer to float (float*) : %d \t Size of pointer to pointer (float**) : %d\n\n", sizeof(float), sizeof(float*), sizeof(float**));
	printf("Size of (double) : %d \t Size of pointer to double (double*) : %d \t Size of pointer to pointer (double**) : %d\n\n", sizeof(double), sizeof(double*), sizeof(double**));
	printf("Size of (char) : %d \t Size of pointer to char (char*) : %d \t Size of pointer to pointer (char**) : %d\n\n", sizeof(char), sizeof(char*), sizeof(char**));
	printf("Size of (struct ampEmp) : %d \t Size of pointer to struct ampEmp (struct ampEmp*) : %d \t Size of pointer to pointer (struct ampEmp**) : %d\n\n", sizeof(struct ampEmp), sizeof(struct ampEmp*), sizeof(struct ampEmp**));

	return(0);
}
