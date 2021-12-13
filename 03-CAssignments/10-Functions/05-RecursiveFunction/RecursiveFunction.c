//C Functions assignment : Recursive Function
//Program to show working of recursion in function

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    unsigned int ampNum;

    //function prototype
    void ampRecursive(unsigned int);

    //code
    printf("\n\n");

    printf("Enter any number : ");
    scanf("%u", &ampNum);

    printf("\n");

    printf("Output of Recursive Function : \n");
    ampRecursive(ampNum);

    printf("\n");
    return(0);
}

void ampRecursive(unsigned int n)
{
    //code
    printf("n = %d\n", n);

    if(n > 0)
    {
        ampRecursive(n - 1);
    }
}
