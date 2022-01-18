//C Pointers assignment : Datatypes & Pointer sizes
//Program to show sizes of pointers of different datatypes

#include <stdio.h>

//struct definition
struct ampEmp
{
    char name[50];
    int age;
    float salary;
    char sex;
    char maritalStatus;
};

int main(int argc, char* argv[], char* envp[])
{
    //code
    printf("\n\n");
    printf("Sizes of pointers of different datatypes are : \n\n");
    printf("Size of (int)       : %zd, \t Size of pointer to int (int*)          : %zd\n", sizeof(int), sizeof(int*));
    printf("Size of (float)     : %zd, \t Size of pointer to float (float*)      : %zd\n", sizeof(float), sizeof(float*));
    printf("Size of (double)    : %zd, \t Size of pointer to double (double*)    : %zd\n", sizeof(double), sizeof(double*));
    printf("Size of (char)      : %zd, \t Size of pointer to char (char*)        : %zd\n", sizeof(char), sizeof(char*));
    
    printf("Size of (struct ampEmp) : %zd, \t Size of pointer to struct ampEmp (struct ampEmp*) : %zd\n", sizeof(struct ampEmp), sizeof(struct ampEmp*));

    printf("\n\n");
    return(0);
}

//while printing %d
//32 bit dev compiler %d, %zd works - pointer size is 4 bytes
//64 bit dev compiler only %zd works - pointer size is 8 bytes
