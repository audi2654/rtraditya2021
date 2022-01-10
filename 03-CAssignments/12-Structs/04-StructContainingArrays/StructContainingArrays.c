//C Structs assignment : Struct Containing Arrays Data Members
//Program with structs having data member arrays

#include <stdio.h>

#define I_ARRAY_SIZE 5
#define F_ARRAY_SIZE 7
#define C_ARRAY_SIZE 26

#define NUM_STRINGS 10
#define MAX_CHARS_PER_STRING 20

#define ALPHABET_BEGIN 65   //'A'

//struct definition
struct ampData1
{
    int iArray[I_ARRAY_SIZE];
    float fArray[F_ARRAY_SIZE];
};

struct ampData2
{
    char cArray[C_ARRAY_SIZE];
    char strArray[NUM_STRINGS][MAX_CHARS_PER_STRING];
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct ampData1 data1;
    struct ampData2 data2;
    int i;

    //code
    //piece meal assignment (hard coded)
    data1.fArray[0] = 9.9f;
    data1.fArray[1] = 8.8f;
    data1.fArray[2] = 7.7f;
    data1.fArray[3] = 6.6f;
    data1.fArray[4] = 5.5f;
    data1.fArray[5] = 4.4f;
    data1.fArray[6] = 3.3f;


    //loop assignment (user input)
    printf("\n\n");
    printf("Enter %d integers for iArray : ", I_ARRAY_SIZE);
    for(i = 0; i < I_ARRAY_SIZE; i++)
    {
        scanf("%d", &data1.iArray[i]);
    }

    //loop assignment (hard coded)
    for(i = 0; i < C_ARRAY_SIZE; i++)
    {
        data2.cArray[i] = (char)(i + ALPHABET_BEGIN);
    }

    //piece meal assignment (hard coded)
    strcpy(data2.strArray[0], "Welcome");
    strcpy(data2.strArray[1], "This");
    strcpy(data2.strArray[2], "Is");
    strcpy(data2.strArray[3], "AstroMediComp's");
    strcpy(data2.strArray[4], "Real");
    strcpy(data2.strArray[5], "Time");
    strcpy(data2.strArray[6], "Rendering");
    strcpy(data2.strArray[7], "Batch");
    strcpy(data2.strArray[8], "Of");
    strcpy(data2.strArray[9], "2021-23");

    //displaying data members of struct ampData1
    printf("\n\n");
    printf("Members of struct 'ampData1' are : \n");

    printf("\n\n");
    printf("int array (data1.iArray[]) : \n");
    for(i = 0; i < I_ARRAY_SIZE; i++)
    {
        printf("data1.iArray[%i] = %i\n", i, data1.iArray[i]);
    }

    printf("\n");
    printf("float array (data1.fArray[]) : \n");
    for(i = 0; i < F_ARRAY_SIZE; i++)
    {
        printf("data1.fArray[%i] = %f\n", i, data1.fArray[i]);
    }

    //displaying data members of struct ampData2
    printf("\n\n");
    printf("Members of struct 'ampData2' are : \n");

    printf("\n");
    printf("char array (data2.cArray[]) : \n");
    for(i = 0; i < C_ARRAY_SIZE; i++)
    {
        printf("data2.cArray[%d] = %c\n", i, data2.cArray[i]);
    }

    printf("\n\n");
    printf("string array (data2.strArray[]) : \n");
    for(i = 0; i < NUM_STRINGS; i++)
    {
        printf("%s ", data2.strArray[i]);
    }

    printf("\n\n");

    return(0);
}
