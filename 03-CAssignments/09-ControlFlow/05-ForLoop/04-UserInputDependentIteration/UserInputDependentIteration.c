//C Control Flow assignment : For Loop
//Program to show working of 'for' Loop by taking Iterator from user

#include <stdio.h>

int main(void)
{
    //var decl.
    int i_num, amp_num, i;

    //code
    printf("\n\n");

    printf("Enter a number from which Iteration must begin : ");
    scanf("%d", &i_num);

    printf("How many digits do you want to print from %d onwards ? : ", i_num);
    scanf("%d", &amp_num);

    printf("Printing digits from %d to %i\n", i_num, (i_num + amp_num));

    for(i = i_num; i <= (i_num + amp_num); i++)
        printf("\t%d\n", i);

    printf("\n\n");

    return 0;
}
