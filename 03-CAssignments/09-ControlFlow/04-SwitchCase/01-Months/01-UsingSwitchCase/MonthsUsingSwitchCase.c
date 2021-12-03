//C Control Flow assignment : Switch Case-1A
//Program to show working of switch statement & how it is similar to if elseif else ladder

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

    switch (amp_num_month)
    {
    case 1:     //like 'if' block
        printf("Month num %d is January\n", amp_num_month);
        break;
    
    case 2:     //like 'else if' block
        printf("Month num %d is February\n", amp_num_month);
        break;

    case 3:     //like 'else if' block
        printf("Month num %d is March\n", amp_num_month);
        break;
    
    case 4:     //like 'else if' block
        printf("Month num %d is April\n", amp_num_month);
        break;

    case 5:     //like 'else if' block
        printf("Month num %d is May\n", amp_num_month);
        break;
    
    case 6:     //like 'else if' block
        printf("Month num %d is June\n", amp_num_month);
        break;

    case 7:     //like 'else if' block
        printf("Month num %d is July\n", amp_num_month);
        break;
    
    case 8:     //like 'else if' block
        printf("Month num %d is August\n", amp_num_month);
        break;

    case 9:     //like 'else if' block
        printf("Month num %d is September\n", amp_num_month);
        break;
    
    case 10:     //like 'else if' block
        printf("Month num %d is October\n", amp_num_month);
        break;

    case 11:     //like 'else if' block
        printf("Month num %d is November\n", amp_num_month);
        break;
    
    case 12:     //like 'else if' block
        printf("Month num %d is December\n", amp_num_month);
        break;
    
    default:    //like ending OPTIONAL 'else', just like terminating 'else' is optional in if-else ladder, so is the
                //'default' case optional in switch case
        printf("Invalid month num : %d entered\n", amp_num_month);
        break;
    }

    printf("\nSwitch case block complete\n\n");

    return 0;
}
