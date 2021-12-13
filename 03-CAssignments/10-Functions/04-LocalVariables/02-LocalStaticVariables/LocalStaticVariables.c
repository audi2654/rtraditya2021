//C Functions assignment : Local Variables - 2
//Program to show working of local STATIC variables

//Static vars have internal linkage & hence can be accessed only within 1 file

#include <stdio.h>

//global scope

int main(int argc, char *argv[], char *envp[])
{
    //local scope of main() begins
    
    //local var decl
    int a = 5; //'a' has 'Block level or Local visibility scope', it is accessible only within main() & hence have 'Automatic Duration'
    
    //function prototype
    void change_count(void);

    //code
    printf("\n");
    printf("a = %d\n\n", a);

    change_count(); //first, local_count is initialized to 0, then, local_count = local_count + 1 = 0 + 1 = 1

    change_count(); //here since, local_count is a STATIC local var of change_count(), it does retain its value from the previous calls to itself
    //so local_count will be 2 here

    change_count(); //again local_count retain its value & here it'll be 3

    printf("\n");

    return(0);

    //local scope of main() ends
}

void change_count(void)
{
    //local scope of change_count() begins 

    //local var decl.
    static int local_count = 0; //'local_count' is a STATIC local var 'Block level or Local scope'
    //it has visibility scope limited to the function block hence is accessible only within change_count()
    //but it behaves like a global variable in a way that it retains modifications if any from previous calls 

    //code
    local_count = local_count + 1;
    printf("local count = %d\n", local_count);

    //local scope of change_count() ends
}
