//C Control Flow assignment : If-Else Statement-3
//Program to show working of if-else statement & why 'if else if' ladder was needed

#include <stdio.h>

int main(void)
{
    //var decl.
    int num;

    //code
    printf("\n\n");

    printf("Enter num : ");
    scanf("%d", &num);

    if (num < 0)    //if-01
    {
        printf("num = %d is less than 0 (NEGATIVE)\n", num);
    }
    else    //else-01
    {
        if ((num > 0) && (num <= 100))  //if-02
        {
            printf("num = %d is between 0 & 100\n", num);
        }
        else    //else-02
        {
            if ((num > 100) && (num <= 200))    //if-03
            {
                printf("num = %d is between 100 & 200\n", num);
            }
            else    //else-03
            {
                if ((num > 200) && (num <= 300))    //if-04
                {
                    printf("num = %d is between 200 & 300\n", num);
                }
                else    //else-04
                {
                    if ((num > 300) && (num <= 400))    //if-05
                    {
                        printf("num = %d is between 300 & 400\n", num);
                    }
                    else    //else-05
                    {
                        if ((num > 400) && (num <= 500))    //if-06
                        {
                            printf("num = %d is between 400 & 500\n", num);
                        }
                        else    //else-06
                        {
                            if (num > 500)  //if-07
                            {
                                printf("num = %d is greater than 500\n", num);
                            }
                            else    //else-07
                            {
                               printf("Entered number is 0\n");
                            }   //closing brace else-07
                        }   //closing brace else-06
                    }   //closing brace else-05
                }   //closing brace else-04
            }   //closing brace else-03
        }   //closing brace else-02
    }   //closing brace else-01
    
    printf("\n");

    return 0;
}
