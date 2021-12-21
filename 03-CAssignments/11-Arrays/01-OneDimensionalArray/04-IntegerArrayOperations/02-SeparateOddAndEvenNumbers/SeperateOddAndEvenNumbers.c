//C Arrays assignment : 1D Array : Int Array Operation-2
//Program to show odd & even of elements separately from an array

#include <stdio.h>

#define NUM_ELEMENTS 10

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int ampArray[NUM_ELEMENTS];
    int i, num;

    //code
    printf("\n\n");
    printf("Enter int elements for array : \n\n");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        scanf("%d", &num);
        ampArray[i] = num;
    }

    printf("\n\n");

    //Even numbers
    printf("Even numbers are : ");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        if((ampArray[i] % 2) == 0)
            printf("%d ", ampArray[i]);
    }

    printf("\n\n");

    //Odd numbers
    printf("Even numbers are : ");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        if((ampArray[i] % 2) != 0)
            printf("%d ", ampArray[i]);
    }

    return(0);
}
