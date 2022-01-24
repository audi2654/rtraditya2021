//C Conditional Compilation assignment : Conditional Compilation
//Program to show how Conditional Compilation works

#include <stdio.h>

#define AMP_PI_VER 4    //change output by this values

#ifdef AMP_PI_VER
#if AMP_PI_VER <= 0
    #define AMP_PI 3.14
#elif AMP_PI_VER == 1
    #define AMP_PI 3.1415
#elif AMP_PI_VER == 2
    #define AMP_PI 3.141592
#elif AMP_PI_VER == 3
    #define AMP_PI 3.14159265
#elif AMP_PI_VER == 4
    #define AMP_PI 3.1415926535
#elif AMP_PI_VER == 5
    #define AMP_PI 3.141592653589
#else
    #define AMP_PI 3.141592653589793
#endif  //for #if
#endif  //for #ifdef

#ifndef AMP_PI_VER
    #define AMP_PI 0.0
#endif

int main(int argc, char** argv, char** envp)
{
    //code
    printf("\n\n");
    printf("Hello World\n");

    printf("\n\n");
    printf("PI version selected = %d\n", AMP_PI_VER);
    printf("PI value = %.15lf\n", AMP_PI);

    return(0);
}
