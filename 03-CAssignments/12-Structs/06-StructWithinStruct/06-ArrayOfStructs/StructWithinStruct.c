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
    struct ampNumber n;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct NumTables tables[10];    //declaring an array of 10 'struct Numtables'
    int i, j;

    //code
    for(i = 0; i < 10; i++)
    {
        tables[i].n.num = (i + 1);
    }

    for(i = 0; i < 10; i++)
    {
        printf("\n\n");
        printf("Table of %d : \n", tables[i].n.num);
        for(j = 0; j < 10; j++)
        {
            tables[i].n.num_table[j] = tables[i].n.num * (j + 1);
            printf("%d x %d = %d\n", tables[i].n.num, (j + 1), tables[i].n.num_table[j]);
        }
    }

    return(0);
}
