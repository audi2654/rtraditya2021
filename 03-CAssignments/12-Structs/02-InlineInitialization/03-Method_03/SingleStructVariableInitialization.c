//C Structs assignment : Struct Inline Initialization method - 3
//Program to show different ways of initializing a struct variable

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //defining struct
    struct ampDataStruct
    {
        int i;
        float f;
        double d;
        char c;
    } data = { 79, 79.79f, 797.797, 'Y'}; //inline initialization of struct var
    //while inline initializing a struct it is must to initialize data members, 
    //as per the order in which they are written in the struct definition

    //code

    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("Data members of struct ampDataStruct are : \n");
    printf("i = %d\n", data.i);
    printf("f = %f\n", data.f);
    printf("d = %lf\n", data.d);
    printf("c = %c\n", data.c);
    
    return(0);
}
