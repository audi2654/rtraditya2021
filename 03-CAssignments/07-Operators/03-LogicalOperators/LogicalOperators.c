//C Logical Operators assignment
//Program to show working of Logical Operators in C

#include<stdio.h>

int main(void)
{
    //var decl.
    int a;
    int b;
    int c;
    int result;

    //code
    printf("\n\n");

    printf("Enter 1st int : ");
    scanf("%d", &a);

    printf("Enter 2nd int : ");
    scanf("%d", &b);

    printf("Enter 3rd int : ");
    scanf("%d", &c);

    printf("\n\n");

    printf("If answer = 0, it is FALSE\n");
    printf("If answer = 1, it is TRUE\n\n");

    //Logical AND (&&)
    result = (a <= b) && (b != c);
    printf("LOGICAL AND (&&) : Answer is TRUE(1) if & only if both conditions are true or relations exist. Answer is FALSE(0), if any one or both conditions are false or both relations don't exist.\n");
    printf("a = %d is less than or equal to b = %d AND b = %d is not equal to c = %d \t\t\t Answer = %d\n\n", a, b, b, c, result);

    //Logical OR (||)
    result = (b >= a) && (a == c);
    printf("LOGICAL OR (||) : Answer is FALSE(0) if & only if both conditions are false or both relations don't exist. Answer is TRUE(1), if any one or both conditions are true or relations exist.\n");
    printf("b = %d is greater than or equal to a = %d OR a = %d is equal to c = %d \t\t\t Answer = %d\n\n", b, a, a, c, result);

    //Logical NOT or Negation (!)
    result = !a;
    printf("a = %d, using logical NOT(!) operator on a gives Result = %d\n", a, result);

    result = !b;
    printf("b = %d, using logical NOT(!) operator on b gives Result = %d\n", b, result);

    result = !c;
    printf("c = %d, using logical NOT(!) operator on c gives Result = %d\n\n", c, result);

    result = (!(a <= b) && !(b != c));
    printf("Using logical NOT(!) on (a <= b) & on (b != c) & then ANDing them gives Result = %d\n", result);

    result = (!(b >= a) || !(a == c));
    printf("Using logical NOT(!) on (b >= a) & on (a == c) & then ORing them gives Result = %d\n", result);

    printf("\n\n");

    return 0;
}
