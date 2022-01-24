//C Variable number of arguments assignment : Function with variable number of arguments
//Program to show how variadic function work

#include <stdio.h>
#include <stdarg.h>

int main(int argc, char** argv, char** envp)
{
    //func decl.
    int ampSum(int, ...);   //variadic function

    //var decl.
    int amp_answer;

    //code
    printf("\n\n");
    
    amp_answer = ampSum(3, 1, 1, 1);
    printf("Answer = %d\n\n", amp_answer);

    amp_answer = ampSum(0);
    printf("Answer = %d\n\n", amp_answer);

    amp_answer = ampSum(8, 2, 2, 2, 2, 2, 2, 2, 2);
    printf("Answer = %d\n\n", amp_answer);

    return(0);
}

//function definition
int ampSum(int num, ...)    //first parameter 'num' tells the count of arguments that'll be passed next
{
    //var decl.
    int sum_total = 0;
    int n;

    va_list number_list;    //used to collect all args

    //code
    va_start(number_list, num);
    while(num)
    {
        n = va_arg(number_list, int);
        sum_total = sum_total + n;
        num--;
    }
    va_end(number_list);
    return(sum_total);
}
