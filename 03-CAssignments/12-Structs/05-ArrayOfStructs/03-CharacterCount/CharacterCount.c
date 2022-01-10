//C Structs assignment : Struct Containing Arrays
//Program to count the occurence of characters in a string using structs

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

struct ampCharCount
{
    char ch;
    int ch_count;
}char_and_count[] = { {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}, {'E', 0}, {'F', 0}, {'G', 0}, {'H', 0},
                      {'I', 0}, {'J', 0}, {'K', 0}, {'L', 0}, {'M', 0}, {'N', 0}, {'O', 0}, {'P', 0},
                      {'Q', 0}, {'R', 0}, {'S', 0}, {'T', 0}, {'U', 0}, {'V', 0}, {'W', 0}, {'X', 0},
                      {'Y', 0}, {'Z', 0} }; //inline initialization

#define SIZEOF_ENTIRE_ARRAY_OF_STRUCTS sizeof(char_and_count)
#define SIZEOF_ONE_STRUCT_FROM_ARRAY_OF_STRUCTS sizeof(char_and_count[0])
#define NUM_OF_ELEMENTS_IN_ARRAY (SIZEOF_ENTIRE_ARRAY_OF_STRUCTS / SIZEOF_ONE_STRUCT_FROM_ARRAY_OF_STRUCTS)

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    char str[MAX_STRING_LENGTH];
    int i, j , actual_str_length = 0;

    //code
    printf("\n\n");
    printf("Enter string : ");
    gets_s(str, MAX_STRING_LENGTH);

    actual_str_length = strlen(str);

    printf("\n\n");
    printf("The string you have entered is : ");
    printf("%s\n", str);

    for(i = 0; i < actual_str_length; i++)
    {
        for(j = 0; j < NUM_OF_ELEMENTS_IN_ARRAY; j++)
        {
            str[i] = toupper(str[i]);
            if(str[i] == char_and_count[j].ch)
                char_and_count[j].ch_count++;
        }
    }

    printf("\n\n");
    printf("The number of occurences of all chars are : \n");
    for (int i = 0; i < NUM_OF_ELEMENTS_IN_ARRAY; i++)
    {
        printf("Character %c = %d\n", char_and_count[i].ch, char_and_count[i].ch_count);
    }
    printf("\n\n");

    return(0);
}
