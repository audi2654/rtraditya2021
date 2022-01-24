//C Pointers assignment : Typedef with Struct pointer
//Program to show how to typedef a struct pointer

#include <stdio.h>

//defining struct
struct ampData
{
    int i;
    float f;
    double d;
};

int main(int argc, char** arhv, char** envp)
{
    //var decl.
    int iSize;
    int fSize;
    int dSize;
    int struct_ampData_Size;
    int ptr_for_struct_ampData_Size;

    typedef struct ampData* ampDataPtr;

    ampDataPtr pData = NULL;

    //code
    printf("\n\n");

    pData = (ampDataPtr)malloc(sizeof(struct ampData));
    if(pData == NULL)
    {
        printf("FAILED to allocate memory to pData, BYE\n");
        exit(0);
    }
    else
    {
        printf("SUCCESSFULLY allocated memory to pData\n");
    }

    //assigning data values to data members of struct ampData
    pData->i = 99;
    pData->f = 99.99f;
    pData->d = 999.999;

    //displaying values
    printf("\n\n");
    printf("i = %d\n", pData->i);
    printf("i = %f\n", (*pData).f);
    printf("i = %lf\n", pData->d);

    //sizes of data members
    iSize = sizeof(pData->i);
    fSize = sizeof(pData->f);
    dSize = sizeof((*pData).d);

    //displaying sizes
    printf("\n\n");
    printf("Size of i = %d bytes \n", iSize);
    printf("Size of f = %d bytes \n", fSize);
    printf("Size of d = %d bytes \n", dSize);

    //sizes of struct ampData
    struct_ampData_Size = sizeof(struct ampData);
    ptr_for_struct_ampData_Size = sizeof(ampDataPtr);

    //displaying sizes
    printf("\n\n");
    printf("Size of struct ampData = %d bytes \n", struct_ampData_Size);
    printf("Size of ptr to struct ampData = %d bytes \n", ptr_for_struct_ampData_Size);

    if(pData)
    {
        free(pData);
        pData = NULL;
        printf("Memory FREED for pData\n\n");
    }

    return(0);
}
