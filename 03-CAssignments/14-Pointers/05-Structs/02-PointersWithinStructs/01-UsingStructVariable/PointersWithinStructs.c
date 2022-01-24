//C Pointers assignment : Pointers within Struct 
//Program to show use of pointers from within a struct

#include <stdio.h>

//defining struct
struct ampDataStruct
{
    int *ptr_i;
    int i;

    float *ptr_f;
    float f;

    double *ptr_d;
    double d;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct ampDataStruct aData;

    //code
    //Assigning data values to data members
    aData.i = 11;
    aData.ptr_i = &aData.i;
    
    aData.f = 11.88f;
    aData.ptr_f = &aData.f;

    aData.d = 111.888;
    aData.ptr_d = &aData.d;

    //displaying values of data members of 'struct amaDataStruct'
    printf("\n\n");
    printf("Data members of struct amaDataStruct are : \n");
    printf("i = %d\n", aData.i);
    printf("Address of 'i' = %p\n\n", aData.ptr_i);

    printf("f = %f\n", *(aData.ptr_f));
    printf("Address of 'f' = %p\n\n", aData.ptr_f);

    printf("d = %lf\n", aData.d);
    printf("Address of 'd' = %p\n\n", aData.ptr_d);

    return(0);
}
