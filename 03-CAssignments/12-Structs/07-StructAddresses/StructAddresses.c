//C Structs assignment : Struct Addresses
//Program to show that struct are stored contiguously in memory like arrays

#include <stdio.h>

struct ampData
{
    int i;
    float f;
    double d;
    char c;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct ampData data;

    //code
    //assigning data values to the data members of 'struct ampData'
    data.i = 80;
    data.f = 320.41f;
    data.d = 321.1234;
    data.c = 'A';

    //displaying values & addresses of data members of struct
    printf("\n\n");
    printf("Data members & addresses of struct ampData are : \n\n");
    printf("i = %d,                        its address = %p\n", data.i, &data.i);
    printf("f = %f,                its address = %p\n", data.f, &data.f);
    printf("d = %lf,                its address = %p\n", data.d, &data.d);
    printf("c = %c,                         its address = %p\n\n", data.c, &data.c);

    printf("Starting address of 'struct ampData' var 'data' = %p\n\n", &data);

    return(0);
}
