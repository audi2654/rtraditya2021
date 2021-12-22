//C Arrays assignment : 1D Array : String operations
//Program to concatenation a string using user defined function MyStrCat

#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(int argc, char* argv[], char* envp[])
{
    //func prototype
    void MyStrCat(char[], char[]);

    //var decl.
    char ampChArray_One[MAX_STRING_LENGTH], ampChArray_Two[MAX_STRING_LENGTH];   //a character array is a string

    printf("\n\n");
    printf("Enter first string : ");
    gets_s(ampChArray_One, MAX_STRING_LENGTH);

    printf("\n");
    printf("Enter second string : ");
    gets_s(ampChArray_Two, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("Before Concatenation\n");
    printf("First string is : %s\n", ampChArray_One);
    printf("Second string is : %s\n", ampChArray_Two);

    MyStrCat(ampChArray_One, ampChArray_Two);     //string concatenation user defined function

    printf("\n");
    printf("After Concatenation\n");
    printf("First string is : %s\n", ampChArray_One);       //concatenates with string 2
    printf("Second string is : %s\n", ampChArray_Two);      //remains as it is

    return(0);
}

//func definition
void MyStrCat(char str_destination[], char str_source[])
{
    //func prototype
    int MyStrLen(char[]);

    //var decl.
    int iStringLength_Source = 0;
    int iStringLength_Destination = 0;
    int i, j;

    //code
    iStringLength_Source = MyStrLen(str_source);
    iStringLength_Destination = MyStrLen(str_destination);

    //array indices begin from 0 hence last index will always be (length-1)
    //so concatenation must begin from index number equal to length of array str_destination
    //we need to put the character at first index of str_source to the first index+1 position of str_destination
    for(i = iStringLength_Destination, j = 0; j < iStringLength_Source; i++, j++)
    {
        str_destination[i] = str_source[j];
    }
    str_destination[i] = '\0';
}

int MyStrLen(char str[])
{
    //var decl.
    int j;
    int string_length = 0;

    //code
    //determining exact length of the string by detecting first '\0' character
    for(j = 0; j < MAX_STRING_LENGTH; j++)
    {
        if(str[j] == '\0')
            break;
        else
            string_length++ ;
    }
    return(string_length);
}
