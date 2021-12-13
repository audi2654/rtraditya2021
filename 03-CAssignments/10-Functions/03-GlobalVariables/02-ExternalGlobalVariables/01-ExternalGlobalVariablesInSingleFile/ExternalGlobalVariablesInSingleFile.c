//C Functions assignment : Global Variables - 2A
//Program to show working of external global variables with single file

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //function prototype
    void change_count(void);

    //var decl.
    extern int ampGlobalCount;  //when we declare var using 'extern' keyboard we do Forward Declaration
    //& in a way we tell compiler that i'm declaring some var of type int with name ampGlobalCount here 
    //& its proper definition may come up ahead in program or in other program file,
    //so don't give me compile time linker errors right here on this line, go ahead & compile whole program successfully

    //On another note, usually when we declare something, until it is DEFINED or initialized also, no memory is allocated to that thing
    //but when we normally declare a var like int a; here a is declared & implicitly DEFINED as well i.e declaration & definition in one line, for this statement memory is allocated & value is initialized to some garbage
    //now using keyword 'extern' we can purely declare a var & tell compiler that do not implicilty DEFINE this var, the definition for this var may be at some other place or not,
    //so don't allocate any memory until you get definition of this var

    //using extern keyword to declare vars also increases the visibility of that var within & outside the declared program file, giving that var an External Linkage

    //code
    printf("\n");

    printf("Value of global count before change_count() = %d\n", ampGlobalCount);

    change_count();
    //ampGlobalCount = 56;
    printf("Value of global count after change_count() = %d\n", ampGlobalCount);

    printf("\n");

    return(0);
}

int ampGlobalCount = 0; //declaration as well as definition 

void change_count(void)
{
    //code
    ampGlobalCount = 5;
    printf("Value of global count in change_count() = %d\n", ampGlobalCount);
}

//ampGlobalCount is a global variable
//It is declared & defined BEFORE change_count(), hence it can be accessed & used as any usual global var inside change_count()
//But since the definition (& also declaration) of var is given AFTER main() later in the program, 
//we redeclare or 'Forward Declare' the var explicitly before using it using 'extern' keyword in main()
