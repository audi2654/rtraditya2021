//ampGlobalCount is a global var declared in source code file
//To access it in this file, it must first be redeclared or 'Forward Declared' as an external variable in the global scope
//of this file using 'extern' keyword & its proper data type. Then it can be used as any ordinary global var throughput this file as well

#include <stdio.h>

extern int ampGlobalCount;  //redeclaring or forward declaring as GLOBAL Variable

void change_count1(void)
{
    //code
    ampGlobalCount = ampGlobalCount + 5;
    printf("change_count1() global count in File1 = %d\n", ampGlobalCount);
}
