//C Structs assignment : Size of Unions
//Program to show difference of sizes between struct & unions

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
    printf("\n\n");
    printf("Size of ampStruct = %lu\n", sizeof(s)); //Struct size is addition of the sizes of all data members inside it, here 4+4+8+1 = 17 with padding 24 bytes
    printf("\n\n");
    printf("Size of ampUnion = %lu\n", sizeof(u));  //Union size is the size of the highest sized data member inside it, here double i.e 8 bytes    
    return(0);
}
