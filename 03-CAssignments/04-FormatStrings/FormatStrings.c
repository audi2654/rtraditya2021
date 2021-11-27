//C FormatStrings assignment
//Assignment to show how to format & represent different types of data using Format Specifiers

#include <stdio.h>

int main(void)
{
    //code
    printf("*******************\n\n");

    printf("Hello World by Aditya\n");

    int amp_a = 32;
    printf("Integer DECIMAL Value of 'amp_a' = %d\n", amp_a);
    printf("Integer OCTAL Value of 'amp_a' = %o\n", amp_a);
    printf("Integer HEXADECIMAL Value (in lower case) of 'amp_a' = %x\n", amp_a);
    printf("Integer HEXADECIMAL Value (in UPPER CASE) of 'amp_a' = %X\n\n", amp_a);

    char amp_ch = 'A';
    printf("Char 'amp_ch' = %c\n", amp_ch);
    char amp_str[] = "AstroMediComp RTR Batch 2021";
    printf("String 'amp_str' = %s\n\n", amp_str);
    printf("String with padding 'amp_str' = %20.10s\n\n", amp_str);


    long amp_num = 80654123L;
    printf("Long 'amp_num' = %ld\n", amp_num);
    unsigned int amp_b = 7;
    printf("Unsigned integer 'amp_b' = %u\n\n", amp_b);

    //Different ways to format & print same string on console
    //Notice the changes in the format specifiers
    //Notice the changes when the number of digits before & after the point . changes

    float amp_float = 64321.316245f;
    printf("Floating Point Number 'amp_float' is %f\n", amp_float);
    printf("Floating Point Number with just %%f 'amp_float' = %f\n", amp_float);
    printf("Floating Point Number with %%5.1f 'amp_float' = %5.1f\n", amp_float);
    printf("Floating Point Number with %%8.5f 'amp_float' = %8.5f\n\n", amp_float);

    double amp_double = 23.14444444666666;
    printf("Double precision float point number 'amp_double' is %.20lf\n" /*%f*/, amp_double);     //why this prints 23.14444444666666100829 & not original num only, where nums after 6 i.e 5923194 come from ?
    printf("Double precision float point number WITHOUT Exponential = %g\n", amp_double);
    printf("Double precision float point number WITH Exponential (lower case) = %e\n", amp_double);
    printf("Double precision float point number WITH Exponential (UPPER CASE) = %E\n", amp_double);
    printf("Double Hexadecimal value (lower case) = %a\n", amp_double);
    printf("Double Hexadecimal value (UPPER CASE) = %A\n\n", amp_double);

    printf("********************\n");
    return(0);
}
