//C Functions assignment : Local Variables - 1
//Program to show working of local variables

#include <stdio.h>

//global scope

int main(int argc, char *argv[], char *envp[])
{
    //local scope of main() begins
    
    //local var decl
    int a = 5; //'a' has 'Block level or Local scope', it is accessible only within main()
    
    //function prototype
    void change_count(void);

    //code
    printf("\n");
    printf("a = %d\n\n", a);

    change_count(); //first, local_count is initialized to 0, then, local_count = local_count + 1 = 0 + 1 = 1

    change_count(); //since, local_count is ordinary local var of change_count(), it does not retain its value from the previous calls to itself
    //so local_count will be initialized to 0 everytime we call change_count()

    change_count(); //again local_count is reinitialized to 0

    printf("\n");

    return(0);

    //local scope of main() ends
}

void change_count(void)
{
    //local scope of change_count() begins 

    //local var decl.
    int local_count = 0; //'local_count' has 'Block level or Local scope', it is accessible only within change_count()

    //code
    local_count = local_count + 1;
    printf("local count = %d\n", local_count);

    //local scope of change_count() ends
}
