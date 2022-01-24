//C Pointers assignment : Struct pointer as parameter
//Program to show use of struct pointer as parameter

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
    //function prototype
    void ChangeValues(struct ampData *);

    //var decl.
    struct ampData *ptr_for_ampData = NULL;

    //code
    printf("\n\n");

    ptr_for_ampData = (struct ampData *)malloc(sizeof(struct ampData));
    if(ptr_for_ampData == NULL)
    {
        printf("FAILED to allocate memory to ptr_for_ampData, BYE\n");
        exit(0);
    }
    else
    {
        printf("SUCCESSFULLY allocated memory to ptr_for_ampData\n");
    }

    //assigning data values to data members of struct ampData
    ptr_for_ampData->i = 99;
    ptr_for_ampData->f = 99.99f;
    ptr_for_ampData->d = 999.999;

    //displaying values
    printf("\n\n");
    printf("i = %d\n", ptr_for_ampData->i);
    printf("i = %f\n", (*ptr_for_ampData).f);
    printf("i = %lf\n", ptr_for_ampData->d);

    ChangeValues(ptr_for_ampData);

    //displaying values
    printf("\n\n");
    printf("i = %d\n", ptr_for_ampData->i);
    printf("i = %f\n", (*ptr_for_ampData).f);
    printf("i = %lf\n\n", ptr_for_ampData->d);

    if(ptr_for_ampData)
    {
        free(ptr_for_ampData);
        ptr_for_ampData = NULL;
        printf("Memory FREED for ptr_for_ampData\n\n");
    }

    return(0);
}

//defining function
void ChangeValues(struct ampData *pParam_Data)
{
    //code
    pParam_Data->i = 22;
    (*pParam_Data).f = 2.2f;
    pParam_Data->d = 22.22;
}
