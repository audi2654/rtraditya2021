//C FormatStrings assignment

#include <stdio.h>

int main(void)
{
    //code
    printf("\n\n");
    printf("*******************");
    printf("\n\n");

    printf("Hello World by Aditya\n");

    int amp_a = 32;
    printf("Integer DECIMAL Value of 'amp_a' = %d\n", amp_a);
    printf("Integer OCTAL Value of 'amp_a' = %o\n", amp_a);
    printf("Integer HEXADECIMAL Value (in lower case) of 'amp_a' = %x\n", amp_a);
    printf("Integer HEXADECIMAL Value (in UPPER CASE) of 'amp_a' = %X\n", amp_a);

    char amp_ch = 'A';
    printf("Char 'amp_ch' = %c\n", amp_ch);

    char amp_str[] = "AstroMediComp RTR Batch 2021";
    printf("String 'amp_str' = %s\n", amp_str);

    long amp_num = 80654123L;
    printf("Long 'amp_num' = %ld\n", amp_num);

    return(0);
}
