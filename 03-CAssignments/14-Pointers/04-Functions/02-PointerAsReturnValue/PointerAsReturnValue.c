//C Pointers assignment : Functions - String Operations
//Program to concatenate strings using pointers

#include <stdio.h>

#define MAX_STRING_LEN 512

int main(int argc, char* argv[], char *envp[])
{
    //func signature
    char* ReplaceVowelsWithHashSymbol(char *);

    //var decl
    char string[MAX_STRING_LEN];
    char *replaced_string = NULL;

    //code
    printf("\n\n");
    printf("Enter string : ");
    gets_s(string, MAX_STRING_LEN);

    replaced_string = ReplaceVowelsWithHashSymbol(string);
    if(replaced_string == NULL)
    {
        printf("ReplaceVowelsWithHashSymbol() function FAILED, exiting now\n");
        exit(0);
    }

    printf("\n\n");
    printf("Replaced String is : ");
    printf("%s\n", replaced_string);
    printf("\n\n");

    if(replaced_string)
    {
        free(replaced_string);
        replaced_string = NULL;
        printf("Allocated memory to replaced_string FREED\n\n");
    }

    return(0);
}

//func definition
char* ReplaceVowelsWithHashSymbol(char *s)
{
    //func prototype
    void ampStrCopy(char*, char *);
    int ampStrLen(char *);

    //var decl.
    char *new_string = NULL;
    int i;

    //code
    new_string = (char *)malloc(ampStrLen(s) * sizeof(char));
    if(new_string == NULL)
    {
        printf("Memory allocation for NEW STRING FAILED\n");
        return(NULL);
    }

    ampStrCopy(new_string, s);
    for(i = 0; i < ampStrLen(new_string); i++)
    {
        switch (new_string[i])      
        {
        case 'A':
        case 'a':
        case 'E':
        case 'e':
        case 'I':
        case 'i':
        case 'O':
        case 'o':
        case 'U':
        case 'u':
            new_string[i] = '#';
            break;
        default:
            break;
        }
    }
    return(new_string);
}

void ampStrCopy(char* str_destination, char *str_source)
{
    //func prototype
    int ampStrLen(char*);

    //var decl.
    int iStringLength = 0;
    int j;

    //code
    iStringLength = ampStrLen(str_source);
    for(j = 0; j < iStringLength; j++)
        *(str_destination + j) = *(str_source + j);

    *(str_destination + j) = '\0';
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
        if(*(str + j) == '\0')
            break;
        else
            string_length++;
    }
    return(string_length);
}
