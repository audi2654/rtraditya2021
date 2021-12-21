//C Arrays assignment : 1D Array
//Program to show initializing of 1d array by user input

#include <stdio.h>

#define AMP_INT_ARRAY_NUM_ELEMENTS 5
#define AMP_FLOAT_ARRAY_NUM_ELEMENTS 5
#define AMP_CHAR_ARRAY_NUM_ELEMENTS 5


int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int iArray[AMP_INT_ARRAY_NUM_ELEMENTS];
    float fArray[AMP_FLOAT_ARRAY_NUM_ELEMENTS];
    char cArray[AMP_CHAR_ARRAY_NUM_ELEMENTS];
    int i, num;

    //code
    //Array Elements INPUT
    printf("\n\n");
    printf("Enter elements for 'integer' array : ");
    for(i = 0; i < AMP_INT_ARRAY_NUM_ELEMENTS; i++)
        scanf("%d", &iArray[i]);

    printf("\n\n");
    printf("Enter elements for 'floating' point array : ");
    for(i = 0; i < AMP_FLOAT_ARRAY_NUM_ELEMENTS; i++)
        scanf("%f", &fArray[i]);

    printf("\n\n");
    printf("Enter elements for 'character' array : ");
    for(i = 0; i < AMP_CHAR_ARRAY_NUM_ELEMENTS; i++)
    {
        cArray[i] = getch();
        printf("%c ", cArray[i]);
    }
   
   
    //Array Elements OUTPUT
    printf("\n\n\n\n");
    printf("Printing elements of 'integer' array : ");
    for(i = 0; i < AMP_INT_ARRAY_NUM_ELEMENTS; i++)
        printf("%d ", iArray[i]);

    printf("\n\n");
    printf("Printing elements of 'floating' point array : ");
    for(i = 0; i < AMP_FLOAT_ARRAY_NUM_ELEMENTS; i++)
        printf("%f ", fArray[i]);

    printf("\n\n");
    printf("Printing elements of 'character' array : ");
    for(i = 0; i < AMP_CHAR_ARRAY_NUM_ELEMENTS; i++)
        printf("%c ", cArray[i]);

    printf("\n\n");
    return(0);
}
