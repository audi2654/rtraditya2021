//C Control Flow assignment : Switch Case-1B
//Previous Months program using if elseif else ladder

#include <stdio.h>

int main(void)
{   
    //var decl.
    int amp_num_month;

    //code
    printf("\n\n");

    printf("Enter number of month (1-12) : ");
    scanf("%d", &amp_num_month);

    printf("\n\n");

    //If-ElseIf-Else ladder begins from here
    if (amp_num_month == 1) //like 'case 1'
        printf("Month num %d is January\n", amp_num_month);

    else if (amp_num_month == 2) //like 'case 2'
        printf("Month num %d is February\n", amp_num_month);

    else if (amp_num_month == 3) //like 'case 3'
        printf("Month num %d is March\n", amp_num_month);

    else if (amp_num_month == 4) //like 'case 4'
        printf("Month num %d is April\n", amp_num_month);

    else if (amp_num_month == 5) //like 'case 5'
        printf("Month num %d is May\n", amp_num_month);

    else if (amp_num_month == 6) //like 'case 6'
        printf("Month num %d is June\n", amp_num_month);

    else if (amp_num_month == 7) //like 'case 7'
        printf("Month num %d is July\n", amp_num_month);

    else if (amp_num_month == 8) //like 'case 8'
        printf("Month num %d is August\n", amp_num_month);

    else if (amp_num_month == 9) //like 'case 9'
        printf("Month num %d is September\n", amp_num_month);

    else if (amp_num_month == 10) //like 'case 10'
        printf("Month num %d is October\n", amp_num_month);

    else if (amp_num_month == 11) //like 'case 11'
        printf("Month num %d is November\n", amp_num_month);

    else if (amp_num_month == 12) //like 'case 12'
        printf("Month num %d is December\n", amp_num_month);

    else //like 'default', just like 'default' in switch case, terminating 'else' is optional in if-else ladder
        printf("Invalid month num : %d entered\n", amp_num_month);

    printf("\nIf ElseIf Else ladder complete\n\n");

    return 0;
}
