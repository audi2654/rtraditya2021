//C Typedef assignment : Typedef for Primitive Datatypes
//Program to show working of typedef for primitive datatypes

//typedef specifier is used to define or give an alias name(definition) specifically to some datatype primitive or userdefined
//typedef is similar to 'using' in C++, 'using' has reversed syntax
//although typedef also works in C++ 

#include <stdio.h>

//global typedef
typedef int MY_INT; //'type' int has been re'def'ined as MY_INT, now MY_INT can be used anywhere instead of 'int'

int main(int argc, char* argv[], char* envp[])
{
    //funtion prototype
    MY_INT Add(MY_INT, MY_INT);     //internally this is exactly same as : int Add(int, int);

    //typedef
    typedef int MY_INT;
    typedef float AMP_FLOAT;
    typedef char AMP_CHARACTER;
    typedef double AMP_DOUBLE;

    /*
    in C++
    using MY_INT = int;
    using AMP_FLOAT = float;
    */

    //just like below Microsoft uses lots of typedefs in Win32SDK
    typedef unsigned int UINT;
    typedef UINT HANDLE;
    typedef HANDLE HWND;
    typedef HANDLE HINSTANCE;

    /*
    in C++
    using UINT = unsigned int;
    using HANDLE = UINT;
    using HWND = HANDLE;
    using HINSTANCE = HANDLE;
    */

    //var decl.
    MY_INT a = 10, i;
    MY_INT amp_iArray[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };

    AMP_FLOAT f_amp = 20.0f;
    const AMP_FLOAT f_amp_pi = 3.14f;

    AMP_CHARACTER ch = '#';
    AMP_CHARACTER amp_chArray1[] = "Hello";
    AMP_CHARACTER amp_chArray2[][10] = { "RTR", "Batch", "2021-23" };

    AMP_DOUBLE d = 6.2314;

    UINT uint = 2451;
    HANDLE handle = 7854;
    HWND hwnd = 1230;
    HINSTANCE hInstance = 1000;

    //code
    printf("\n\n");
    printf("type MY_INT var a = %d\n", a);

    printf("\n");
    for(i = 0; i < (sizeof(amp_iArray) / sizeof(int)); i++)
    {
        printf("type MY_INT array var amp_iArray[%d] = %d\n", i, amp_iArray[i]);
    }

    printf("\n");
    printf("type AMP_FLOAT var f = %f\n", f_amp);
    printf("type AMP_FLOAT const var f_amp_pi = %f\n", f_amp_pi);

    printf("\n");
    printf("type AMP_DOUBLE var d = %lf\n", d);

    printf("\n");
    printf("type AMP_CHARACTER var ch = %c\n", ch);

    printf("\n");
    printf("type AMP_CHARACTER array var amp_chArray1 = %s\n", amp_chArray1);

    printf("\n");
    for(i = 0; i < (sizeof(amp_chArray2) / sizeof(amp_chArray2[0])); i++)
    {
        printf("%s\t", amp_chArray2[i]);
    }

    printf("\n\n");
    printf("type UINT var uint = %u\n", uint);
    printf("type HANDLE var uint = %u\n", handle);
    printf("type HWND var uint = %u\n", hwnd);
    printf("type HINSTANCE var uint = %u\n", hInstance);

    printf("\n");
    MY_INT x = 20;
    MY_INT y = 8;

    printf("%d + %d = %d\n\n", x, y, Add(x, y));

    return(0);
}

MY_INT Add(MY_INT a, MY_INT b)
{
    //var decl.
    MY_INT c;

    //code
    c = a + b;

    return(c);
}
