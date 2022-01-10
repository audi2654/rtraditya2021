//C Structs assignment : Struct Containing Arrays Data Members
//Program with structs having data member arrays & their hard coded initialization

#include <stdio.h>

#define NAME_LENGTH 50
#define MARITAL_STATUS 10   //put 20

struct ampEmployee
{
    char name[NAME_LENGTH];
    int age;
    float salary;
    char gender;
    char maritalStatus[MARITAL_STATUS];
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct ampEmployee EmpRecord[5];    //an array of 5 structs of struct ampEmployee

    char emp_Ramesh[] = "Ramesh";
    char emp_Suresh[] = "Suresh";
    char emp_Gajesh[] = "Gajesh";
    char emp_Vishesh[] = "Vishesh";
    char emp_Namesh[] = "Namesh";

    int i;

    //code
    //hardcoded initialization of array of struct ampEmployee

    //Emp-1
    strcpy(EmpRecord[0].name, emp_Ramesh);
    EmpRecord[0].age = 30;
    EmpRecord[0].gender = 'M';
    EmpRecord[0].salary = 32000.0f;
    strcpy(EmpRecord[0].maritalStatus, "Not Married");	//here next name comes up, why ? although if MARITAL_STATUS is increased it goes

    //Emp-2
	EmpRecord[1].age = 40;
    strcpy(EmpRecord[1].name, emp_Suresh);
    EmpRecord[1].gender = 'M';
    EmpRecord[1].salary = 2000.0f;
    strcpy(EmpRecord[1].maritalStatus, "Married");

    //Emp-1
    strcpy(EmpRecord[2].name, emp_Gajesh);
    EmpRecord[2].age = 60;
    EmpRecord[2].gender = 'F';
    EmpRecord[2].salary = 120000.0f;
    strcpy(EmpRecord[2].maritalStatus, "NotMarried");

    //Emp-1
    strcpy(EmpRecord[3].name, emp_Vishesh);
    EmpRecord[3].age = 10;
    EmpRecord[3].gender = 'M';
    EmpRecord[3].salary = 1000.0f;
    strcpy(EmpRecord[3].maritalStatus, "NotMarried");

    //Emp-1
    strcpy(EmpRecord[4].name, emp_Namesh);
    EmpRecord[4].age = 35;
    EmpRecord[4].gender = 'M';
    EmpRecord[4].salary = 999999.9f;
    strcpy(EmpRecord[4].maritalStatus, "Married");

    //display
    printf("\n\n");
    printf("Displaying employee records\n");
    for(i = 0; i < 5; i++)
    {
        printf("Employee Number - %d\n", (i + 1));
        printf("Name 			: %s\n", EmpRecord[i].name);
        printf("Age 			: %i years\n", EmpRecord[i].age);

		if(EmpRecord[i].gender == 'M')
			printf("Gender			: Male\n");
		else
			printf("Gender			: Female\n");

		printf("Salary			: Rs.%f\n", EmpRecord[i].salary);
		printf("Marital Status		: %s\n", EmpRecord[i].maritalStatus);

		printf("\n\n");
    }
	return(0);
}
