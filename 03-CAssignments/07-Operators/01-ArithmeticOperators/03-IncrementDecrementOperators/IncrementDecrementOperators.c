//C Increment Decrement operators assignment
//Program to show working of Increment Decrement postfix & prefix operators

#include <stdio.h>

int main(void)
{
    //variable decl.
    int a = 100;
    int b = 200;

    //code
    printf("\n");
    printf("a = %d\n", a);      //prints the latest assigned/updated value as it is
    printf("a = %d\n", a++);    //POSTFIX Increment, prints/uses the current value of var & THEN increments value by 1
    printf("a = %d\n", a);      //prints the latest assigned/updated value as it is
    printf("a = %d\n\n", ++a);  //PREFIX Increment, increments value by 1 & THEN prints/uses the incremented new value of var

    printf("b = %d\n", b);      //prints the latest assigned/updated value as it is
    printf("b = %d\n", b--);    //POSTFIX Decrement, prints/uses the current value of var & THEN decrements value by 1
    printf("b = %d\n", b);      //prints the latest assigned/updated value as it is
    printf("b = %d\n\n", --b);    //PREFIX Decrement, decrements value by 1 & THEN prints/uses the decremented new value of var

    return 0;
}
