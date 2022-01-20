//C Pointers assignment : Functions
//Program to show integer array as pointer parameter

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char *envp[])
{
    //func signature
    void MultiplyArrayElmtsByNumber(int *, int, int);
    
    //var decl
    int *amp_iArray = NULL;
    int num_elements;
    int i, num;

    //code
    printf("\n\n");
    printf("Enter how many elemets you want in int array : ");
    scanf("%d", &num_elements);

    amp_iArray = (int *)malloc(num_elements * sizeof(int));
    if(amp_iArray == NULL)
    {
        printf("Memory allocation to amp_iArray FAILED, exiting now\n");
        exit(0);
    }

    printf("Enter %d elements for int array\n", num_elements);
    for(i = 0; i < num_elements; i++)
        scanf("%d", &amp_iArray[i]);

    printf("\n\n");
    printf("Array BEFORE passing to function MultiplyArrayElmtsByNumber() : \n");
    for(i = 0; i < num_elements; i++)
        printf("amp_iArray[%d] = %d\n", i, amp_iArray[i]);

    printf("\n");
    printf("Enter number by which you want to multiply each array element : ");
    scanf("%d", &num);

    MultiplyArrayElmtsByNumber(amp_iArray, num_elements, num);

    printf("\n\n");
    printf("Array returned by MultiplyArrayElmtsByNumber() :\n");
    for(i = 0; i < num_elements; i++)
        printf("amp_iArray[%d] = %d\n", i, amp_iArray[i]);

    printf("\n");
    if(amp_iArray)
    {
        free(amp_iArray);
        amp_iArray = NULL;
        printf("Allocated memory to amp_iArray FREED\n\n");
    }

    return(0);
}

//func definition
void MultiplyArrayElmtsByNumber(int *arr, int iNumElements, int n)
{
    //var decl.
    int i;

    //code
    for(i = 0; i < iNumElements; i++)
        arr[i] = arr[i] * n;
}
