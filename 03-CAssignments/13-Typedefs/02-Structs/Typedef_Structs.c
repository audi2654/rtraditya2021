//C Typedef assignment : Typedef for Struct Datatype
//Program to show working of typedef for user defined struct datatype

//typedef specifier is used to define or give an alias name(definition) specifically to some datatype primitive or userdefined
//typedef is similar to 'using' in C++, 'using' has reversed syntax
//although typedef also works in C++ 

#include <stdio.h>

#define MAX_NAME_LENGTH 100

struct amp_Employee
{
    char name[MAX_NAME_LENGTH];
    unsigned int age;
    char gender;
    double salary;
};

struct MyData
{
    int i;
    float f;
    double d;
    char c;
};

int main(int argc, char* argv[], char* envp[])
{
    //typedef
    typedef struct amp_Employee MY_EMPLOYEE_TYPE;
    typedef struct MyData MY_DATA_TYPE;

    //var decl.
    struct amp_Employee emp = {"Money", 25, 'M', 10000.00};
    MY_EMPLOYEE_TYPE emp_typedeffed = {"Honey", 25, 'F', 20000.00};

    struct MyData md = {1, 2.0f, 3.444444, 'M'};
    MY_DATA_TYPE md_typedeffed;

    //code
    md_typedeffed.i = 9;
    md_typedeffed.f = 8.5f;
    md_typedeffed.d = 7.99999;
    md_typedeffed.c = 'A';

    printf("\n\n");
    printf("struct amp_Employee : \n");
    printf("emp.name        = %s\n", emp.name);
    printf("emp.age         = %d\n", emp.age);
    printf("emp.gender      = %c\n", emp.gender);
    printf("emp.salary      = %lf\n", emp.salary);

    printf("\n\n");
    printf("MY_EMPLOYEE_TYPE : \n");
    printf("emp_typedeffed.name        = %s\n", emp_typedeffed.name);
    printf("emp_typedeffed.age         = %d\n", emp_typedeffed.age);
    printf("emp_typedeffed.gender      = %c\n", emp_typedeffed.gender);
    printf("emp_typedeffed.salary      = %lf\n", emp_typedeffed.salary);

    printf("\n\n");
    printf("struct MyData : \n");
    printf("md.i = %i\n", md.i);
    printf("md.f = %f\n", md.f);
    printf("md.d = %lf\n", md.d);
    printf("md.c = %c\n", md.c);

    printf("\n\n");
    printf("MY_DATA_TYPE : \n");
    printf("md_typedeffed.i = %i\n", md_typedeffed.i);
    printf("md_typedeffed.f = %f\n", md_typedeffed.f);
    printf("md_typedeffed.d = %lf\n", md_typedeffed.d);
    printf("md_typedeffed.c = %c\n", md_typedeffed.c);

    printf("\n\n");
    return(0);
}
