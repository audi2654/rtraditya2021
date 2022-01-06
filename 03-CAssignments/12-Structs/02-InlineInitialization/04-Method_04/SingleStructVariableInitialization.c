//C Structs assignment : Struct Inline Initialization method - 4
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

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    //while inline initializing a struct it is must to initialize data members, 
    //as per the order in which they are written in the struct definition
    struct ampDataStruct data1 = { 14, 1.4f, 40.25252, 'j'}; //inline initialization of struct var
    struct ampDataStruct data2 = { 7, 0.7f, 20.51515, 'i'};
    struct ampDataStruct data3 = { 36, 'G'}; //here G is converted into float, d is 0.00000 & c is assigned no character
    struct ampDataStruct data4 = { 79 }; //here f = 0.000, d = 0.0000000, no char assigned to c

    //code
    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("Data members of struct ampDataStruct data1 are : \n");
    printf("i = %d\n", data1.i);
    printf("f = %f\n", data1.f);
    printf("d = %lf\n", data1.d);
    printf("c = %c\n", data1.c);

    printf("\n\n");
    printf("Data members of struct ampDataStruct data2 are : \n");
    printf("i = %d\n", data2.i);
    printf("f = %f\n", data2.f);
    printf("d = %lf\n", data2.d);
    printf("c = %c\n", data2.c);

    printf("\n\n");
    printf("Data members of struct ampDataStruct data3 are : \n");
    printf("i = %d\n", data3.i);
    printf("f = %f\n", data3.f);
    printf("d = %lf\n", data3.d);
    printf("c = %c\n", data3.c);

    printf("\n\n");
    printf("Data members of struct ampDataStruct data4 are : \n");
    printf("i = %d\n", data4.i);
    printf("f = %f\n", data4.f);
    printf("d = %lf\n", data4.d);
    printf("c = %c\n\n", data4.c);
    
    return(0);
}
