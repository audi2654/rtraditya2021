//C Structs & Unions assignment : Unions
//Program to show addresses of struct & union

#include <stdio.h>

struct ampData
{
    int i;
    float f;
    double d;
    char c;
};

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
    struct ampData s;
    union ampUnion u;

    //code
    //ampUnion u1
    printf("\n\n");
    printf("Members of struct s are : \n");
    
    s.i = 8;
    s.f = 8.8;
    s.d = 88.888;
    s.c = 'A';

    printf("s.i = %d\n", s.i);
    printf("s.f = %f\n", s.f); 
    printf("s.d = %lf\n", s.d);
    printf("s.c = %c\n\n", s.c);

    printf("Addresses of members of struct s are :\n");
    printf("s.i = %p\n", &s.i);
    printf("s.f = %p\n", &s.f); 
    printf("s.d = %p\n", &s.d);
    printf("s.c = %p\n\n", &s.c);
    printf("struct s = %p\n\n", &s);

    printf("Members of union u are : \n");

    u.i = 6;
    printf("u.i = %i\n", u.i);

    u.f = 6.6f;
    printf("u.f = %f\n", u.f);

    u.d = 66.666;
    printf("u.d = %lf\n", u.d);

    u.c = '6';
    printf("u.c = %c\n\n", u.c);

    printf("Addresses of members of union u are : \n");
    printf("u.i = %p\n", &u.i);
    printf("u.f = %p\n", &u.f);
    printf("u.d = %p\n", &u.d);
    printf("u.c = %p\n\n", &u.c);
    printf("ampUnion u = %p\n\n", &u);

    return(0);
}
