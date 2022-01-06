//C Structs assignment : Struct Inline Initialization method - 2
//Program to show different ways of initializing a struct variable

#include <stdio.h>

//defining struct
struct ampDataStruct
{
    int i;
    float f;
    double d;
    char c;
};

struct ampDataStruct data = { 88, 88.88f, 888.888, '8'}; //inline initialization of struct var
//while inline initializing a struct it is must to initialize data members, 
//as per the order in which they are written in the struct definition

int main(int argc, char* argv[], char* envp[])
{
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
