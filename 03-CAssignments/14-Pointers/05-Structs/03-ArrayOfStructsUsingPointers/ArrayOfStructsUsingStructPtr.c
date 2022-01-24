//C Pointers assignment : Arrays of struct using pointers
//Program to arrays of struct using pointers

#include <stdio.h>
#include <ctype.h>

#define NAME_LENGTH 50
#define MARITAL_STATUS 10

struct ampEmployee
{
    char name[NAME_LENGTH];
    int age;
    float salary;
    char gender;
    char maritalStatus;
};

int main(int argc, char* argv[], char* envp[])
{
    //function signature
    void ampGetString(char[], int);

    //var decl.
    struct ampEmployee *ptr_for_EmpRecord = NULL;
    int numEmp, i;

    //code
    printf("\n\n");
    printf("Enter number of employees you want to record : ");
    scanf("%d", &numEmp);

    printf("\n\n");
    ptr_for_EmpRecord = (struct ampEmployee *)malloc(sizeof(struct ampEmployee) * numEmp);
    if(ptr_for_EmpRecord == NULL)
    {
        printf("FAILED to allocate memory for %d employees, exiting now\n\n", numEmp);
        exit(0);
    }
    else
    {
        printf("SUCCESSFULLY allocated memory for %d employees\n\n", numEmp);
    }

    //initializing array of struct Employee by user input
    for(i = 0; i < numEmp; i++)
    {
        printf("\n\n");
        printf("DATA ENTRY FOR EMPLOYEE - %d\n", (i + 1));
        printf("Enter Employee Name : ");
        ampGetString(ptr_for_EmpRecord[i].name, NAME_LENGTH);

        printf("\n\n");
        printf("Enter Employee Age : ");
        scanf("%d", &ptr_for_EmpRecord[i].age);

        printf("\n\n");
        printf("Enter Employee Gender (F/M) : ");
        ptr_for_EmpRecord[i].gender = getch();
        printf("%c",ptr_for_EmpRecord[i].gender);
        ptr_for_EmpRecord[i].gender = toupper(ptr_for_EmpRecord[i].gender);

        printf("\n\n");
        printf("Enter Employee Salary : ");
        scanf("%f", &ptr_for_EmpRecord[i].salary);

        printf("\n\n");
        printf("Enter Employee Marital Status (Y/N) : ");
        ptr_for_EmpRecord[i].maritalStatus = getch();
        printf("%c",ptr_for_EmpRecord[i].maritalStatus);
        ptr_for_EmpRecord[i].maritalStatus = toupper(ptr_for_EmpRecord[i].maritalStatus);
    }

    //display
    printf("\n\n");
    printf("Displaying employee records\n");
    for(i = 0; i < numEmp; i++)
    {
        printf("Employee Number - %d\n", (i + 1));
        printf("Name 			: %s\n",ptr_for_EmpRecord[i].name);
        printf("Age 			: %i years\n",ptr_for_EmpRecord[i].age);

		if(ptr_for_EmpRecord[i].gender == 'M')
			printf("Gender			: Male\n");
		else if (ptr_for_EmpRecord[i].gender == 'F')
			printf("Gender			: Female\n");
        else
            printf("Invalid Gender Data Entered\n");

		printf("Salary			: Rs.%f\n",ptr_for_EmpRecord[i].salary);

        if(ptr_for_EmpRecord[i].maritalStatus == 'Y')
			printf("Marital Status : Married\n");
		else if(ptr_for_EmpRecord[i].maritalStatus == 'N')
			printf("Marital Status : Not Married\n");
        else
            printf("Invalid Marital Status Data Entered\n");
		
		printf("\n\n");
    }

    if(ptr_for_EmpRecord)
    {
        free(ptr_for_EmpRecord);
        ptr_for_EmpRecord = NULL;
        printf("Allocated memory to %d employees FREED", numEmp);
    }

    printf("\n\n");
	return(0);
}

//function definition
void ampGetString(char str[], int str_size)
{
    //var decl.
    int i;
    char ch = '\0';

    //code
    i = 0;
    do
    {
        ch = getch();
        str[i] = ch;
        printf("%c", str[i]);
        i++;
    } while ((ch != '\r') && (i < str_size));

    if(i == str_size)
        str[i - 1] = '\0';
    else
        str[i] = '\0';   
}
