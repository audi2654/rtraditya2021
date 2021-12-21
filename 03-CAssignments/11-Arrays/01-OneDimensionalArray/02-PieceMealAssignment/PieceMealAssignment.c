//C Arrays assignment : 1D Array
//Program to show piece meal assignment of 1D array

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int iArrayOne[10];
    int iArrayTwo[10];

    //code
    //iArrayone[]
    iArrayOne[0] = 3;
    iArrayOne[1] = 6;
    iArrayOne[2] = 9;
    iArrayOne[3] = 12;
    iArrayOne[4] = 15;
    iArrayOne[5] = 18;
    iArrayOne[6] = 21;
    iArrayOne[7] = 24;
    iArrayOne[8] = 27;
    iArrayOne[9] = 30;

    printf("\n\n");
    printf("Piece meal (HARD CODED) assignment & display of elements of 'iArrayOne[]' : \n\n");

    printf("Element 1 at 0th index of 'iArrayOne[]' = %d\n", iArrayOne[0]);
    printf("Element 2 at 1st index of 'iArrayOne[]' = %d\n", iArrayOne[1]);
    printf("Element 3 at 2nd index of 'iArrayOne[]' = %d\n", iArrayOne[2]);
    printf("Element 4 at 3rd index of 'iArrayOne[]' = %d\n", iArrayOne[3]);
    printf("Element 5 at 4th index of 'iArrayOne[]' = %d\n", iArrayOne[4]);
    printf("Element 6 at 5th index of 'iArrayOne[]' = %d\n", iArrayOne[5]);
    printf("Element 7 at 6th index of 'iArrayOne[]' = %d\n", iArrayOne[6]);
    printf("Element 8 at 7th index of 'iArrayOne[]' = %d\n", iArrayOne[7]);
    printf("Element 9 at 8th index of 'iArrayOne[]' = %d\n", iArrayOne[8]);
    printf("Element 10 at 9th index of 'iArrayOne[]' = %d\n", iArrayOne[9]);


    //iArrayTwo[]
    printf("\n\n");

    printf("Enter element 1 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[0]);
    printf("Enter element 2 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[1]);
    printf("Enter element 3 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[2]);
    printf("Enter element 4 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[3]);
    printf("Enter element 5 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[4]);
    printf("Enter element 6 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[5]);
    printf("Enter element 7 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[6]);
    printf("Enter element 8 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[7]);
    printf("Enter element 9 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[8]);
    printf("Enter element 10 of 'iArrayTwo[]' : "); scanf("%d", &iArrayTwo[9]);

    printf("\n\n");
    printf("Piece meal (USER INPUT) assignment & display of elements of 'iArrayTwo[]' : \n\n");
    printf("Element 1 at 0th index of 'iArrayTwo[]' = %d\n", iArrayTwo[0]);
    printf("Element 2 at 1st index of 'iArrayTwo[]' = %d\n", iArrayTwo[1]);
    printf("Element 3 at 2nd index of 'iArrayTwo[]' = %d\n", iArrayTwo[2]);
    printf("Element 4 at 3rd index of 'iArrayTwo[]' = %d\n", iArrayTwo[3]);
    printf("Element 5 at 4th index of 'iArrayTwo[]' = %d\n", iArrayTwo[4]);
    printf("Element 6 at 5th index of 'iArrayTwo[]' = %d\n", iArrayTwo[5]);
    printf("Element 7 at 6th index of 'iArrayTwo[]' = %d\n", iArrayTwo[6]);
    printf("Element 8 at 7th index of 'iArrayTwo[]' = %d\n", iArrayTwo[7]);
    printf("Element 9 at 8th index of 'iArrayTwo[]' = %d\n", iArrayTwo[8]);
    printf("Element 10 at 9th index of 'iArrayTwo[]' = %d\n", iArrayTwo[9]);

    return(0);
}
