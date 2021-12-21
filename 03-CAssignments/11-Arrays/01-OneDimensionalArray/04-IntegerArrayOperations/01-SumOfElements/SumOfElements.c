//C Arrays assignment : 1D Array : Int Array Operation-1
//Program to show sum of elements in an array

#include <stdio.h>

#define NUM_ELEMENTS 10

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int ampArray[NUM_ELEMENTS];
    int i, num, sum = 0;

    //code
    printf("\n\n");
    printf("Enter int elements for array : \n\n");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        scanf("%d", &num);
        ampArray[i] = num;
    }

    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        sum = sum + ampArray[i];
    }

    printf("\n\n");
    printf("Sum of all elements of array = %d\n\n", sum);

    return(0);
}
