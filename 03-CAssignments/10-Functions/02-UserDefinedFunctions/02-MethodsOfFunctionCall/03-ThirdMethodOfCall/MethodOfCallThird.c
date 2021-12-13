//C Functions assignment : User Defined Functions : Methods of Calling - 3
//Program to show different ways of calling a user defined function

//User Defined Function : Method of Calling - 3
//Calling only 1 function in main() directly & rest functions trace their call indirectly to main()

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototypes/signatures/declarations
    void ampFunctionCountry();

    //code
    ampFunctionCountry();
    return(0);
}

void ampFunctionCountry(void)   //function definition
{
    //function declarations
    void Function_OfAMC(void);

    //code
    Function_OfAMC();

    printf("\n");

    printf("I live in India\n");
}

void Function_OfAMC(void)
{
    //function decl.
    void Function_Surname(void);

    //code
    Function_Surname();

    printf("\n");

    printf("Of ASTROMEDICOMP");
}

void Function_Surname(void)
{
    //function decl.
    void Function_MiddleName(void);

    //code
    Function_MiddleName();

    printf("\n");

    printf("Panchal");
}

void Function_MiddleName(void)
{
    //func. decl
    void Function_FirstName(void);

    //code
    Function_FirstName();

    printf("\n");

    printf("Mohan");
}

void Function_FirstName(void)
{
    //func. decl.
    void Function_Is(void);

    //code
    Function_Is();

    printf("\n");

    printf("Aditya");
}

void Function_Is(void)
{
    //func. decl.
    void Function_Name(void);

    //code
    Function_Name();

    printf("\n");

    printf("Is");
}

void Function_Name(void)
{
    //func decl. 
    void Function_My(void);

    //code
    Function_My();

    printf("\n");

    printf("Name");
}

void Function_My(void)
{
    //code
    printf("\n");

    printf("My");
}
