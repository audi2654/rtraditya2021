//C Pointers assignment : Functions
//Program to show significance of an out parameter or parameterized return value

#include <stdio.h>

enum
{
    NEGATIVE = -1,
    ZERO,
    POSITIVE
};

int main(int argc, char* argv[], char* envp[])
{
	//func decl.
    int ampDifference(int, int, int*);

    //var decl.
    int a, b, answer, ret;

    //code
    printf("\n\n");
    printf("Enter value for 'a' : ");
    scanf("%d", &a);

    printf("\n\n");
    printf("Enter value for 'b' : ");
    scanf("%d", &b);

    ret = ampDifference(a, b, &answer);

    printf("\n\n");
    printf("%d - %d = %d\n\n", a, b, answer);

    if(ret == POSITIVE)
        printf("Result of %d - %d is POSITIVE\n", a, b);
    else if(ret == NEGATIVE)
        printf("Result of %d - %d is NEGATIVE\n", a, b);
    else
        printf("Result of %d - %d is ZERO\n", a, b);

    return 0;
}

//here, we want our func to do 2 things
//First is to subtract given nums & return its result
//Second, is to tell if the result is +ve, -ve or zero

//But any func can return only value & in one type only\
//so to do above both things & return multiple value we use Parmeterized Return Values or Out Parameter
//Numerical result can be returned via out parameter & the actual return value returns the status of result

int ampDifference(int x, int y, int *diff)
{
    //code
    *diff = x - y;

    if(*diff > 0)
        return POSITIVE;
    else if(*diff < 0)
        return(NEGATIVE);
    else 
        return(ZERO);
}
