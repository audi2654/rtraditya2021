//C Structs assignment : Struct declaration method - 4A
//Program to declare a struct & using a SINGLE struct variable

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
    struct ampDataStruct data; //declaring a single struct variable of type 'struct ampDataStruct' locally
    int ampDataStruct_size;

    //code
    //assigning data values to the data members of 'struct ampDataStruct'
    data.i = 99;
    data.f = 99.99f;
    data.d = 999.999;
    data.c = '9';

    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("Data members of struct ampDataStruct are : \n");
    printf("i = %d\n", data.i);
    printf("f = %f\n", data.f);
    printf("d = %lf\n", data.d);
    printf("c = %c\n", data.c);

    //displaying size of struct
    printf("\n\n");
    printf("Size of each data member is : \n");
    printf("Size of i = %d\n", sizeof(data.i));
    printf("Size of f = %d\n", sizeof(data.f));
    printf("Size of d = %d\n", sizeof(data.d));
    printf("Size of c = %d\n\n", sizeof(data.c));

    printf("Size of 'struct ampDataStruct' is %d bytes\n\n", sizeof(struct ampDataStruct));     //sizeof(data) also works
    
    //size of any struct will rarely be equal to the total of sizes of each of its members
    //the difference in size is due to compiler padding & it is machine dependant

    return(0);
}
