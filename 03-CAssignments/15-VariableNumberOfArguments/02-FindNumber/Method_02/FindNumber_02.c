//C Variable number of arguments assignment : Function with variable number of arguments
//Program to show how variadic function work

#include <stdio.h>
#include <stdarg.h>

#define NUM_TO_BE_FOUND 99
#define NUM_ELEMENTS 5

int main(int argc, char** argv, char** envp)
{
    //func decl.
    int ampSum(int, ...);   //variadic function

    //var decl.
    int amp_answer;

    //code
    printf("\n\n");
    
    FindNumber(NUM_TO_BE_FOUND, NUM_ELEMENTS, 99, 8, 99, 99, 7);

    return(0);
}

//function definition
int FindNumber(int numToBeFound, int num, ...) 
{
    //func decl.
    int va_FindNumber(int, int, va_list);

    //var decl.
    int count = 0;
    int n;
    va_list number_list;    //used to collect all args
    
    //code
    va_start(number_list, num);

    count = va_FindNumber(numToBeFound, num, number_list);

    if(count == 0)
        printf("Number %d not found\n", numToBeFound);
    else
        printf("Number %d found %d times\n", numToBeFound, count);

    va_end(number_list);
}

int va_FindNumber(int numToBeFound, int num, va_list list)    //first parameter 'num' tells the count of arguments that'll be passed next
{
    //var decl.
    int countOfNum = 0;
    int n;

    //code
    while(num)
    {
        n = va_arg(list, int);
        if(n == numToBeFound)
            countOfNum++;
        num--;
    }

    return(countOfNum);
}
