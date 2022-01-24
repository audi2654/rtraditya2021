//C Pointers assignment : Pointers within Struct 
//Program to show use of pointers from within a struct & accessing with a struct ptr var - Method 2

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
    struct ampDataStruct *pData = NULL;

    //code
    printf("\n\n");
    pData = (struct ampDataStruct *)malloc(sizeof(struct ampDataStruct));
    if(pData == NULL)
    {
        printf("FAILED to allocate memory to struct ampDataStruct, bye\n");
        exit(0);
    }
    else
    {
        printf("SUCCESSFULLY allocated memory to struct ampDataStruct\n");
    }

    //Assigning data values to data members
    (*pData).i = 63;
    pData->ptr_i = &pData->i;
    
    pData->f = 63.63f;
    (*pData).ptr_f = &(*pData).f;

    pData->d = 636.636;
    pData->ptr_d = &(*pData).d;

    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("Data members of struct ampDataStruct are : \n");
    printf("i = %d\n", (*pData).i);
    printf("Address of 'i' = %p\n\n", (*pData).ptr_i);

    printf("f = %f\n", *(pData->ptr_f));
    printf("Address of 'f' = %p\n\n", pData->ptr_f);

    printf("d = %lf\n", *((*pData).ptr_d));
    printf("Address of 'd' = %p\n\n", (*pData).ptr_d);

    if(pData)
    {
        free(pData);
        pData = NULL;
        printf("FREED allocated memory allocated memory to struct ampDataStruct\n");
    }

    return(0);
}
