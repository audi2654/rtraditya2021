//C Control Flow assignment : While Loop
//Program to show working of 'while' Loop with Floating Point Iterator

#include <stdio.h>

int main(void)
{
    //var decl.
    float amp_f;
    float amp_f_num = 2.8f;

    //code
    printf("\n\n");

    printf("Printing numbers from %f to %f\n", amp_f_num, (amp_f_num * 10.0f));
    amp_f = amp_f_num;
    while(amp_f <= (amp_f_num * 10.0f))
    {
        printf("\t%f\n", amp_f);
        amp_f = amp_f + amp_f_num;
    }

    printf("\n\n");

    return(0);
}
