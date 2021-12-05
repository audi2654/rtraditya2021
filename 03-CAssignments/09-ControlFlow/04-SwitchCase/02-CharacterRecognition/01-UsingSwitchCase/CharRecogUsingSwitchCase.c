//C Control Flow assignment : Switch Case-2A
//Character Recognition Program to show working of switch statement & how it is similar to if elseif else ladder

#include <stdio.h>  //for printf()
#include <conio.h>  //MS DOS Windows compiler specific header file for getch(), won't work on Linux

//ASCII values for '0' to '9' => 48 to 57
#define CHAR_DIGIT_BEGINNING 48
#define CHAR_DIGIT_ENDING 57

//ASCII values for 'A' to 'Z' => 65 to 90
#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

//ASCII values for 'a' to 'z' => 97 to 122
#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122

int main(void)
{
    //var decl.
    char amp_ch;
    int amp_ch_value;

    //code
    printf("\n\n");

    printf("Enter Char : ");
    amp_ch = getch();

    printf("\n");

    switch (amp_ch)
    {
        //Using FALL THROUGH CONDITION for the benefit of reducing the no. of comparisons our program makes
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
            printf("Char \'%c\' entered is VOWEL character\n\n", amp_ch);
            break;

        default:
            amp_ch_value = (int)amp_ch;
            
            //if cases for VOWELS doesn't execute & entered char has ASCII value between 65 & 90 or between 97 & 122, it is still an alphabet but a CONSONANT
            if ((amp_ch_value >= CHAR_ALPHABET_UPPER_CASE_BEGINNING && amp_ch_value <= CHAR_ALPHABET_UPPER_CASE_ENDING) ||
                (amp_ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && amp_ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING))
            {
                printf("Char \'%c\' entered is a CONSONANT\n\n", amp_ch);
            }
            else if (amp_ch_value >= CHAR_DIGIT_BEGINNING && amp_ch_value <= CHAR_DIGIT_ENDING)
            {
                printf("Char \'%c\' entered is a DIGIT CHARACTER\n\n", amp_ch);
            }
            else
            {
                printf("Char \'%c\' entered is a SPECIAL CHARACTER\n\n", amp_ch);
            }
    }
    printf("Switch case block complete\n\n");

    return(0);
}
