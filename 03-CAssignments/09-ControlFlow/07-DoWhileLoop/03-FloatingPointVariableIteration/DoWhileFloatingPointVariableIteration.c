//C Control Flow assignment : Do While Loop
//Program to show working of 'do while' Loop with Floating Point Iterator

#include <stdio.h>

int main(void)
{
    //var decl.
    float amp_f;
    float amp_f_num = 3.602f;

    //code
    printf("\n\n");

    printf("Printing numbers from %f to %f using Do-While in Increasing order\n", amp_f_num, (amp_f_num * 10.0f));
    amp_f = amp_f_num;
    
    do
    {
        printf("\t%f\n", amp_f);
        amp_f = amp_f + amp_f_num;
    } while(amp_f <= (amp_f_num * 10.0f));

    printf("\n\n");

    printf("Printing numbers from %f to %f using Do-While in Decreasing order\n", amp_f_num, (amp_f_num / 10.0f));
    amp_f = amp_f_num;
    
    do
    {
        printf("\t%f\n", amp_f);
        amp_f = amp_f - (amp_f_num / 10.0f);
    } while(amp_f >= (amp_f_num / 10.0f));

    printf("\n\n");

    return(0);
}
