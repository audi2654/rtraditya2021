//C EscapeSequence assignment
//Program to show different types of Escape Sequences in C

#include <stdio.h>
int main(void)
{
    //code
    printf("\n\n");

    printf("Going on the next line using \\n Escape Sequence\n\n");
    printf("Demonstrating \t Horizontal \t Tab \t using \\t Escape Sequence\n\n");
    printf("\"This is a Double Quote Output\" done using \\\" \\\" Escape Sequence\n\n");
    printf("\'This is a Single Quote Output\' done using \\\' \\\' Escape Sequence\n\n");
    printf("Backspace turned to Backspace\b using \\b Escape Sequence\n\n");

    printf("\r Demonstrating Carriage Return using \\r Escape Sequence\n");
    printf("Demonstrating \r Carriage Return using \\r Escape Sequence\n");
    printf("Demonstrating Carriage \r Return using \\r Escape Sequence\n\n");

    printf("Demonstrating \x41 using \\xhh Escape Sequence\n"); //0x41 is hexa for letter 'A', 
    //'xhh' is the place holder for 'x' followed by 2 digits 'hh', together forming a Hexadecimal number

    printf("Demonstrating \102 using \\ooo Escape Sequence\n\n"); //0x41 is octal code for letter 'B', 
    //'ooo' is the place holder for the 3 digits forming a Hexadecimal number

    printf("Demostrating modulo operator %%\n");

    return(0);
}
