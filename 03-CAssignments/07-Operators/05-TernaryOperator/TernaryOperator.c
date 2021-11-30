//C Ternary Operator assignment
//Program to show the working of ternary operator(?:)

//Ternary operator is a concised form of if-else statement,
//& is usually used when some value is to be assigned to the RHS var through if-else mechanism

#include <stdio.h>

int main(void)
{
    //var decl.
    int a, b;
    int p, q;
    char ch_result1, ch_result2;
    int i_result1, i_result2;

    //code
    printf("\n\n");

    a = 7;
    b = 5;
    ch_result1 = (a > b) ? 'A' : 'B';   //if (a > b) is TRUE do 'A' : else if FALSE do 'B'
    i_result1 = (a > b) ? a : b;
    printf("Ternary Operator Answer-1 --- %c & %d\n", ch_result1, i_result1);

    p = 30;
    q = 30;
    ch_result2 = (p != q) ? 'P' : 'Q';   //if (p != q) is TRUE asssign 'P' : else if FALSE assign 'Q'
    i_result2 = (p != q) ? p : q;
    printf("Ternary Operator Answer-2 --- %c & %d\n", ch_result2, i_result2);

    printf("\n\n");

    return(0);
}
