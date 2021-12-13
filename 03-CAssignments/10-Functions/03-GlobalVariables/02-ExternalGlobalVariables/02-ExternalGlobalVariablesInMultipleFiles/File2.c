//ampGlobalCount is a global var declared in source code file
//To access it in this file, it must first be redeclared or 'Forward Declared' as an external variable in the global scope
//of this file using 'extern' keyword & its proper data type. Then it can be used as any ordinary global var throughput this file as well

#include <stdio.h>

void change_count2(void)
{
    //code
    extern int ampGlobalCount;  //redeclaring or forward declaring as LOCAL Variable although it'll always be a global var

    ampGlobalCount = ampGlobalCount + 10;
    printf("change_count2() global count in File2 = %d\n", ampGlobalCount);
}
