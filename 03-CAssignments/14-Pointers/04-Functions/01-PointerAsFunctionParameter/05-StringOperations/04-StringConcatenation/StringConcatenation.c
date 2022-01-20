//C Pointers assignment : Functions - String Operations
//Program to concatenate strings using pointers

#include <stdio.h>

#define MAX_STRING_LEN 512

int main(int argc, char* argv[], char *envp[])
{
    //func signature
    void ampStrCat(char*, char *);
    int ampStrLen(char *);

    //var decl
    char *ampChArray_One = NULL;    //char array can be represented by a char pointer to mark the base addr (char*)
    char *ampChArray_Two = NULL;

    //code
    printf("\n\n");
    ampChArray_One = (char *)malloc(MAX_STRING_LEN * sizeof(char));
    if(ampChArray_One == NULL)
    {
        printf("Memory allocation to FIRST string FAILED, exiting now\n");
        exit(0);
    }

    //string input
    printf("Enter FIRST string : ");
    gets_s(ampChArray_One, MAX_STRING_LEN);

    ampChArray_Two = (char*)malloc(MAX_STRING_LEN * sizeof(char));
    if(ampChArray_Two == NULL)
    {
        printf("Memory allocation to SECOND string FAILED, exiting now\n");
        exit(0);
    }

    printf("Enter SECOND string : ");
    gets_s(ampChArray_Two, MAX_STRING_LEN);

    //string output
    printf("\n\n");
    printf("BEFORE CONCATENATION\n");
    printf("First String entered by you is : ");
    printf("%s\n", ampChArray_One);

    printf("\n\n");
    printf("Second String entered by you is : ");
    printf("%s\n", ampChArray_Two);

    //string concat
    ampStrCat(ampChArray_One, ampChArray_Two);
    printf("\n\n");
    printf("AFTER CONCATENATION\n");
    printf("First String becomes : ");
    printf("%s\n", ampChArray_One);

    printf("\n\n");
    printf("Second String is : ");
    printf("%s\n", ampChArray_Two);

    printf("\n\n");

    //release memory
    if(ampChArray_Two)
    {
        free(ampChArray_Two);
        ampChArray_Two = NULL;
        printf("Allocated memory to ampChArray_Two FREED\n\n");
    }

    if(ampChArray_One)
    {
        free(ampChArray_One);
        ampChArray_One = NULL;
        printf("Allocated memory to ampChArray_One FREED\n\n");
    }

    return(0);
}

//func definition
/*
void ampStrCat(char *str_destination, char *str_source)
{
    //func prototype
    int ampStrLen(char*);

    //var decl.
    int srcLen = 0;
    int desLen = 0;
    int i, j,

    //code
    srcLen = ampStrLen(str_source);
    desLen = ampStrLen(str_destination);

    for(i = desLen, j = 0; j < srcLen; i++, j++)
    {
        *(str_destination + i) = *(str_source + j);
    }
    *(str_destination + i) = '\0';
}
*/

void ampStrCat(char *str_destination, char *str_source)
{
    //func prototype
    int ampStrLen(char*);

    //var decl.
    int SrcLen = 0;
    int DesLen = 0;
    int i;
    int j;

    //code
    SrcLen = ampStrLen(str_source);
    DesLen = ampStrLen(str_destination);

    for(i = DesLen, j = 0; j < SrcLen; i++, j++)
    {
        *(str_destination + i) = *(str_source + j);
    }
    *(str_destination + i) = '\0';
}

int ampStrLen(char *str)
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    //determining exact lenght of string by detecting the first occurrence of null terminating char (\0)
    for(j = 0; j < MAX_STRING_LEN; j++)
    {
        if(str[j] == '\0')
            break;
        else
            string_length++;
    }
    return(string_length);
}
