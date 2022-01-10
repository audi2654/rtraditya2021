//C Structs assignment : Struct Containing Struct
//Program to show array within struct

#include <stdio.h>

struct ampNumber
{
    int num;
    int num_table[10];
};

struct NumTables
{
    struct ampNumber a;
    struct ampNumber b, c;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct NumTables tables;
    int i;

    //code
    tables.a.num = 6;
    for(i = 0; i < 10; i++)
    {
        tables.a.num_table[i] = tables.a.num * (i + 1);
    }
    printf("\n\n");
    printf("Table of %d : \n", tables.a.num);
    for(i = 0; i < 10; i++)
    {
        printf("%d x %d = %d\n", tables.a.num, (i + 1), tables.a.num_table[i]);
    }

    tables.b.num = 7;
    for(i = 0; i < 10; i++)
    {
        tables.b.num_table[i] = tables.b.num * (i + 1);
    }
    printf("\n\n");
    printf("Table of %d : \n", tables.b.num);
    for(i = 0; i < 10; i++)
    {
        printf("%d x %d = %d\n", tables.b.num, (i + 1), tables.b.num_table[i]);
    }

    tables.c.num = 8;
    for(i = 0; i < 10; i++)
    {
        tables.c.num_table[i] = tables.c.num * (i + 1);
    }
    printf("\n\n");
    printf("Table of %d : \n", tables.c.num);
    for(i = 0; i < 10; i++)
    {
        printf("%d x %d = %d\n", tables.c.num, (i + 1), tables.c.num_table[i]);
    }

    return(0);
}
