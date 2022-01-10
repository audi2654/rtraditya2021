//C Structs assignment : Struct Containing Arrays Data Members
//Program with structs having data member arrays & their initialization by User Input

#include <stdio.h>
#include <conio.h>

#define NUM_EMPLOYEES 2
#define NAME_LENGTH 80

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
    //func prototype
    void MyGetString(char[], int);

    //var decl.
    struct ampEmployee EmpRecord[NUM_EMPLOYEES];    //an array of structs of type struct ampEmployee
    int i;

    //code
    //user input initialization of array of struct ampEmployee

    for(i = 0; i < NUM_EMPLOYEES; i++)
    {
        printf("\n\n\n");
        printf("Enter data for Employee-%d\n", (i + 1));

        printf("Enter emp name : ");
        MyGetString(EmpRecord[i].name, NAME_LENGTH);

        printf("\n");
        printf("Enter emp age : ");
        scanf("%d", &EmpRecord[i].age);

        printf("\n");
        printf("Enter emp gender (M/m for Male, F/f for Female) : ");
        EmpRecord[i].gender = getch();
        printf("%c", EmpRecord[i].gender);
        EmpRecord[i].gender = toupper(EmpRecord[i].gender);

        printf("\n");
        printf("Enter emp salary in Rs : ");
        scanf("%f", &EmpRecord[i].salary);

        printf("\n");
        printf("Enter marital status Y/y for Yes, N/n for No : ");
        EmpRecord[i].maritalStatus = getch();
        printf("%c", EmpRecord[i].maritalStatus);
        EmpRecord[i].maritalStatus = toupper(EmpRecord[i].maritalStatus);
    }

    //display
    printf("\n\n");
    printf("Displaying employee records\n");
    for(i = 0; i < NUM_EMPLOYEES; i++)
    {
        printf("Employee Number - %d\n", (i + 1));
        printf("Name 			: %s\n", EmpRecord[i].name);
        printf("Age 			: %i years\n", EmpRecord[i].age);

		if(EmpRecord[i].gender == 'M')
			printf("Gender			: Male\n");
		else if(EmpRecord[i].gender == 'F')
			printf("Gender			: Female\n");
        else
            printf("Gender                  : Invalid Gender Entered\n");

		printf("Salary			: Rs.%f\n", EmpRecord[i].salary);

        if(EmpRecord[i].maritalStatus == 'Y')
			printf("Marital Status		: Married\n");
		else if(EmpRecord[i].maritalStatus == 'N')
			printf("Marital Status		: Not Married\n");
        else
            printf("Marital Status          : Invalid Marital Status Entered\n");

		printf("\n\n");
    }
	return(0);
}

//Simple Rudimentary implementation of gets_s()
//implemented due to different behaviour of gets_s() / fgets() / fscanf() on different platforms
//backspace / character deletion & arrow key cursor movement not implemented

void MyGetString(char str[], int str_size)
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
    }while((ch != '\r') && (i < str_size));

    if(i == str_size)
        str[i - 1] = '\0';
    else
        str[i] = '\0';
}
