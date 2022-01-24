//C Pointers assignment : Struct Pointer
//Program to declare a simple struct pointer - METHOD 1

#include <stdio.h>

//defining struct
struct ampDataStruct
{
    int i;
    float f;
    double d;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int ampDataStruct_size;
    int ptr_to_ampDataStruct_size;

    struct ampDataStruct *pData = NULL;

    //code
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
    (*pData).i = 99;
    (*pData).f = 99.21f;
    (*pData).d = 994.7777;

    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("Data members of struct ampDataStruct are : \n");
    printf("i = %d\n", (*pData).i);
    printf("f = %f\n", (*pData).f);
    printf("d = %lf\n", (*pData).d);

    //displaying size of struct members
    printf("\n\n");
    printf("Size of each data member is : \n");
    printf("Size of i = %d\n", sizeof((*pData).i));
    printf("Size of f = %i\n", sizeof((*pData).f));
    printf("Size of d = %u\n", sizeof((*pData).d));

    ampDataStruct_size = sizeof(struct ampDataStruct);
    ptr_to_ampDataStruct_size = sizeof(struct ampDataStruct*);

    printf("Size of 'struct ampDataStruct' is %d bytes\n\n", ampDataStruct_size);
    printf("Size of pointer to 'struct ampDataStruct' is %d bytes\n\n", ptr_to_ampDataStruct_size);

    if(pData)
    {
        free(pData);
        pData = NULL;
        printf("FREED allocated memory allocated memory to struct ampDataStruct\n");
    }

    return(0);
}
