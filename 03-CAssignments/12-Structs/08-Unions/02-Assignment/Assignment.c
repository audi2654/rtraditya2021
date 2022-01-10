//C Structs & Unions assignment : Unions
//Program to show value assignments to member of unions

#include <stdio.h>

union ampUnion
{
    int i;
    float f;
    double d;
    char c;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    union ampUnion u1, u2;

    //code
    //ampUnion u1
    printf("\n\n");
    printf("Members of union u1 are : \n");

    u1.i = 9;
    //printf("u1.i = %d\n", u1.i);  //gives correct value

    u1.f = 9.9f;
    //printf("u1.f = %f\n", u1.f);  //gives correct value

    u1.d = 99.999999;
    u1.c = '9';

    printf("u1.i = %d\n", u1.i);    //will give garbage value because first 4 bytes of 8 bytes of union are overwritten
    printf("u1.f = %f\n", u1.f);    //will give garbage value 
    printf("u1.d = %lf\n", u1.d);
    printf("u1.c = %c\n\n", u1.c);

    printf("Addresses of members of union u1 are : \n");
    printf("u1.i = %p\n", &u1.i);
    printf("u1.f = %p\n", &u1.f);
    printf("u1.d = %p\n", &u1.d);
    printf("u1.c = %p\n\n", &u1.c);

    printf("ampUnion u1 = %p\n\n", &u1);

    //ampUnion u2
    printf("\n\n");
    printf("Members of union u2 are : \n");

    u2.i = 6;
    printf("u2.i = %i\n", u2.i);

    u2.f = 6.6f;
    printf("u2.f = %f\n", u2.f);

    u2.d = 66.666;
    printf("u2.d = %lf\n", u2.d);

    u2.c = '6';
    printf("u2.c = %c\n\n", u2.c);

    printf("Addresses of members of union u2 are : \n");
    printf("u2.i = %p\n", &u2.i);
    printf("u2.f = %p\n", &u2.f);
    printf("u2.d = %p\n", &u2.d);
    printf("u2.c = %p\n\n", &u2.c);

    printf("ampUnion u2 = %p\n\n", &u2);

    return(0);
}
