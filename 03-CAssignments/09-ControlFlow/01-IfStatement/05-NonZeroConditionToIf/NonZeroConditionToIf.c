//C Control Flow assignment : If Statement-5
//Program to show working of if statement using non zero condition

#include <stdio.h>

int main(void)
{
    //var decl.
    int a;

    //code
    printf("\n\n");
    
    a = 5;
    if (a)  //Non zero positive value
    {
        printf("If-block 1 : a exists & has value = %d\n", a);
    }

    a = -5;
    if (a)  //Non zero positive value
    {
        printf("If-block 2 : a exists & has value = %d\n", a);
    }

    a = 0;
    if (a)  //Zero value
    {
        printf("If-block 3 : a exists & has value = %d\n", a);  //this will not print because value is 0, neither +ve not -ve
    }

    printf("All three if-statements are done\n");

    printf("\n");

    return 0;
}
