//C Relational Operators assignment
//Program to show the working of relational operators

#include <stdio.h>

int main(void)
{
    //var decl.
    int a;
    int b;
    int result;

    //code
    printf("\n\n");

    printf("Enter one int : ");
    scanf("%i", &a);

    printf("Enter another int : ");
    scanf("%d", &b);

    printf("\n");
    printf("If Answer = 0, it is considered as 'FALSE'\n");
    printf("If Answer = 1, it is considered as 'TRUE'\n\n");

    result = (a < b);
    printf("(a < b) a = %d is less than b = %d \t\t\t Answer = %d\n", a, b, result);

    result = (a > b);
    printf("(a > b) a = %d is greater than b = %d \t\t\t Answer = %d\n", a, b, result);
    
    result = (a <= b);
    printf("(a <= b) a = %d is less than or equal to b = %d \t Answer = %d\n", a, b, result);

    result = (a >= b);
    printf("(a >= b) a = %d is greater than or equal to b = %d \t Answer = %d\n", a, b, result);

    result = (a == b);
    printf("(a == b) a = %d is equal to b = %d \t\t\t Answer = %d\n", a, b, result);

    result = (a != b);
    printf("(a != b) a = %d is not equal to b = %d \t\t\t Answer = %d\n\n", a, b, result);

    return(0);
}
