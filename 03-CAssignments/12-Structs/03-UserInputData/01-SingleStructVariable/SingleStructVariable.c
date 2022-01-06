//C Structs assignment : Struct User Input method - 1
//Program to show various ways to take user input in struct vars

#include <stdio.h>
#include <conio.h>

//defining struct
struct ampDataStruct
{
    int i;
    float f;
    double d;
    char c;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct ampDataStruct data;

    //code
    //taking user input for values of data members of struct var data
    printf("\n\n");

    printf("Enter int value for 'i' data member of struct var 'data' : ");
    scanf("%d", &data.i);

    printf("Enter float value for 'f' data member of struct var 'data' : ");
    scanf("%f", &data.f);

    printf("Enter double value for 'd' data member of struct var 'data' : ");
    scanf("%lf", &data.d);

    printf("Enter char value for 'c' data member of struct var 'data' : ");
    data.c = getch();

    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("Data members of struct ampDataStruct data are : \n");
    printf("i = %d\n", data.i);
    printf("f = %f\n", data.f);
    printf("d = %lf\n", data.d);
    printf("c = %c\n", data.c);

    return(0);
}
