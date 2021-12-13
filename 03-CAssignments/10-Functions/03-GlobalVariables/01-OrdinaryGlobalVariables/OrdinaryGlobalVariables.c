//C Functions assignment : Global Variables - 1
//Program to show working of global variables

//Global scope for a var in short means a global var can be accessed & modified by anyone throughout the program i.e they have a File Scope
//A global var is initialized first thing right at the start of program & it exists until the program ends or dies i.e they have a Static Duration

//If not initiatilized explicitly by us, global vars are by default zero-initialized to their zero values as per the data type i.e int 0, float 0.0, etc
//As a good discipline, we should explicitly initialize global vars to their zero value

#include <stdio.h>

int ampGlobalCount = 0; //global scope variable

int main(int argc, char *argv[], char *envp[])
{
    //function prototype
    void change_count_one(void);
    void change_count_two(void);
    void change_count_three(void);

    //code
    printf("\n");

    printf("main() : value of global count = %d\n", ampGlobalCount);

    change_count_one();
    change_count_two();
    change_count_three();

    printf("\n");

    return(0);
}

void change_count_one(void)
{
    //code
    ampGlobalCount = 100;

    printf("change_count_one() : value of global count = %d\n", ampGlobalCount);
}

void change_count_two(void)
{
    //code
    ampGlobalCount = ampGlobalCount + 1;

    printf("change_count_two() : value of global count = %d\n", ampGlobalCount);
}

void change_count_three(void)
{
    //code
    ampGlobalCount = ampGlobalCount - 63;

    printf("change_count_three() : value of global count = %d\n", ampGlobalCount);
}
