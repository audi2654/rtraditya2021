//C Functions assignment : User Defined Functions : Methods of Calling - 2
//Program to show different ways of calling a user defined function

//User Defined Function : Method of Calling - 2
//Calling only 2 functions in main() directly & rest functions trace their call indirectly to main()

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototypes/signatures/declarations
    void ampDisplayInformation(void);
    void ampFunctionCountry(void);

    //code
    ampDisplayInformation();    //function call
    ampFunctionCountry();   //function call

    return(0);
}

//User defined function's definitions
void ampDisplayInformation(void)
{
    //function prototypes
    void Function_My(void);
    void Function_Name(void);
    void Function_Is(void);
    void Function_FirstName(void);
    void Function_MiddleName(void);
    void Function_Surname(void);
    void Function_OfAMC(void);

    //code
    //function calls
    Function_My();
    Function_Name();
    Function_Is();
    Function_FirstName();
    Function_MiddleName();
    Function_Surname();
    Function_OfAMC();
}

//function definitions
void Function_My(void)
{
    //code
    printf("\n\n");

    printf("My\n");
}

void Function_Name(void)
{
    //code
    printf("Name\n");
}

void Function_Is(void)
{
    //code
    printf("Is\n");
}

void Function_FirstName(void)
{
    //code
    printf("Aditya\n");
}

void Function_MiddleName(void)
{
    //code
    printf("Mohan\n");
}

void Function_Surname(void)
{
    //code
    printf("Panchal\n");
}

void Function_OfAMC(void)
{
    //code
    printf("of ASTROMEDICOMP\n");
}

void ampFunctionCountry(void)
{
    //code
    printf("I live in INDIA");

    printf("\n\n");
}
