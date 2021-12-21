//C Arrays assignment : 1D Array
//Program to show different method to declare a character array

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    //must give \0 explicitly for proper initialization
    char ampChar1[] = {'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P', '\0'};   
    char ampChar2[9] = {'W', 'E', 'L', 'C', 'O', 'M', 'E', 'S', '\0'};
    char ampChar3[] = {'Y', 'O', 'U', '\0'};
    char ampChar4[] = "To"; //here \0 is assumned, size is given as 3 although string has only 2 characters
    char ampChar5[] = "REAL TIME RENDERING BATCH OF 2020-21"; //here \0 is assumned, size is given as 40 although string has only 39 characters

    char ampArrayWithoutNullTerminator[] = {'H', 'e', 'l', 'l', 'o'};
    int i, num, j, count = 0;

    //code
    printf("\n\n");
    
    printf("Size of ampChar1 : %lu\n", sizeof(ampChar1));
    printf("Size of ampChar2 : %lu\n", sizeof(ampChar2));
    printf("Size of ampChar3 : %lu\n", sizeof(ampChar3));
    printf("Size of ampChar4 : %lu\n", sizeof(ampChar4));
    printf("Size of ampChar5 : %lu\n", sizeof(ampChar5));

    printf("\n\n");

    printf("The strings are : \n");
    printf("ampChar1 : %s\n", ampChar1);
    printf("ampChar2 : %s\n", ampChar2);
    printf("ampChar3 : %s\n", ampChar3);
    printf("ampChar4 : %s\n", ampChar4);
    printf("ampChar5 : %s\n", ampChar5);

    printf("\n\n");
    printf("Size of ampArrayWithoutNullTerminator : %lu\n", sizeof(ampArrayWithoutNullTerminator));
    printf("ampArrayWithoutNullTerminator : %s\n", ampArrayWithoutNullTerminator);  //displays garbage at the end of string due to absense of \0 

    printf("\n\n");

    return(0);
}
