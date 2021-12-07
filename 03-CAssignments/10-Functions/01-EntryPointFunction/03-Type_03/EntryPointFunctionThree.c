//C Functions assignment : Entry Point Function - 3
//Program to show working of a simple entry point function & different ways to write it

#include <stdio.h>  //'stdio.h' header file contains declaration of 'printf()'

int main(int argc)     //Entry Point Function with Valid Return Type & 1 Parameter
{
    //code
    printf("\n\n");
    printf("Hello World\n");    //Library Function from stdio.h
    printf("Number of Command Line Arguments = %d\n\n", argc);  //By default name of the file itself is considered as 1 cmd line arg

    return 0;
}
