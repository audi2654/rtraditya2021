//C TypeConversion or TypeCasting assign.
//Program to show how to convert one datatype into other datatype & different ways to do it

#include <stdio.h>

int main(void)
{
    //var decl.
    int i, j;
    char ch1, ch2;

    int a, result_int;
    float f, result_float;

    int i_explicit;
    float f_explicit;

    //code
    printf("\n\n");

    //Interconversion & IMPLICIT type casting (aka Automatic Type Conversion) between 'char' & 'int' types
    i = 70;
    ch1 = i;    //Implicitly converting here (by assigning) an int(4bytes) into char(1byte)    (Narrowing - DATA LOSS)
    printf("i = %d\n", i);
    printf("ch1 (after operation ch1 = i) = %c\n", ch1);

    ch2 = 'Q';
    j = ch2;   //Implicitly converting here (by assigning) a char(1byte) into int(4bytes)    (Widening - NO DATA LOSS)
    printf("ch2 = %c\n", ch2);
    printf("j (after operation j = ch2) = %d\n\n", j);

    //IMPLICIT type conversion between 'int' & 'float' types
    a = 5;
    f = 7.8f;
    
    result_float = a + f;   //Implicit conversion by assigning : float = int + float    (Widening - NO DATA LOSS)
    printf("Addition of int a = %d & float f = %f gives float Sum = %f\n", a, f, result_float);

    result_int = a + f;   //Implicit conversion by assigning : int = int + float    (Widening - NO DATA LOSS)
    printf("Addition of int a = %d & float f = %f gives int Sum = %i\n\n", a, f, result_int);

    
    //EXPLICIT type conversion using Cast Operator (is also known as Type Casting)
    //Different ways to Explicitly convert or type cast datatypes
    //1. C-style type casting or Cast Notation
    //2. Function style/notation (C++ style type casting, NA for C, only in C++)
    //3. Type conversion operators (NA for C, only in C++)

    f_explicit = 30.464545f;
    i_explicit = (int)f_explicit;   //C-style explicit type casting float into int (Narrowing - DATA LOSS)
    
    printf("Original Floating point number : %f\n", f_explicit);
    printf("Resulted Integer after explicitly type casting Floating point num %f = %d\n\n", f_explicit, i_explicit);

    return 0;
}

//Other things in TypeConversion/TypeCasting
//Narrowing (DATA LOSS) & Widening (NO DATA LOSS) Conversion of datatypes
