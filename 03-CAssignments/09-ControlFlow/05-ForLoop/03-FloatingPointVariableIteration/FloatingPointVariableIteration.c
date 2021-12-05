//C Control Flow assignment : For Loop
//Program to show working of 'for' Loop with Floating Point Iterator

#include <stdio.h>

int main(void)
{
    //var decl.
    float f;
    float amp_f_num = 3.17f;

    //code
    printf("\n\n");

    printf("Printing numbers from %f to %f\n", amp_f_num, (amp_f_num * 10.0f));

    for(f = amp_f_num; f <= (amp_f_num * 10.0f); f = f + amp_f_num)
        printf("\t%f\n", f);

    printf("\n\n");

    return(0);
}
