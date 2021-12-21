//C Arrays assignment : 1D Array : Int Array Operation-3
//Program to print prime number elements separately from an array

#include <stdio.h>

#define NUM_ELEMENTS 10

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int ampArray[NUM_ELEMENTS];
    int i, num, j, count = 0;

    //code
    printf("\n\n");
    printf("Enter int elements for array : \n\n");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        scanf("%d", &num);

        //if entered num is negative, then convert it to positive (multiply by -1)
        if(num < 0)
            num = num * -1;

        ampArray[i] = num;
    }

    printf("\n\n");

    //Even numbers
    printf("Entire array is : ");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        printf("%d ", ampArray[i]);
    }

    printf("\n\n");

    //Odd numbers
    printf("Prime numbers are : ");
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        for(j = 1; j <= ampArray[i]; j++)
        {
        if((ampArray[i] % j) == 0)
            count++;
        }
    

        //number 1 is neither a prime number nor a consonant
        //if a num is prime, it is only divisible by 1 & itself
        //hence, if a number is prime the value of count will be exactly 2
        //if the value of count is greater than 2, means num is divisible by other than 2 numbers 0 & itself, so not prime
        //the value of count will be 1 only if ampArray[i] is 1

        if(count == 2)
            printf("%d ", ampArray[i]);

        count = 0; //reset count to 0 for checking next number in loop
    }

    printf("\n\n");

    return(0);
}
