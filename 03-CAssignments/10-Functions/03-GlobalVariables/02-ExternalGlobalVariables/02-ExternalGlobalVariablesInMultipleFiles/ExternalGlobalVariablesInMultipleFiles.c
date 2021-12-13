//C Functions assignment : Global Variables - 2B
//Program to show working of external global variables with multiple files

//cl.exe /c /EHsc ExternalGlobalVariablesInMultipleFiles.c File1.c File2.c
//link.exe ExternalGlobalVariablesInMultipleFiles.obj File1.obj File2.obj
//gcc ExternalGlobalVariablesInMultipleFiles.c File1.c File2.c

#include <stdio.h>

int ampGlobalCount = 0; //declaration as well as definition

int main(int argc, char *argv[], char *envp[])
{
    //function prototype
    void change_count(void);
    void change_count1(void);   //function defined in File1.c
    void change_count2(void);   //function defined in File2.c

    //code
    printf("\n");

    change_count();
    change_count1();
    change_count2();

    return(0);
}

void change_count(void)
{
    //code
    ampGlobalCount = ampGlobalCount + 1;
    printf("change_count() global count = %d\n", ampGlobalCount);
}