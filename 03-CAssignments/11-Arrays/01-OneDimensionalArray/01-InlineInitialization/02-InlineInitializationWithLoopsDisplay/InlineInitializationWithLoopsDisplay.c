//C Arrays assignment : 1D Array
//Program to show inline initialization of 1D array with using LOOPS

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //var decl.
    int iArray[] = {9, 30, 6, 12, 98, 95, 20, 23, 2, 45};   //inline initialization of array
    int intSize;
    int iArraySize;
    int iArrayNumElements;

    float fArray[] = {1.2f, 2.3F, 3.4f, 4.5F, 5.6f, 6.7F, 7.8f, 8.9F};
    int floatSize;
    int fArraySize;
    int fArrayNumElements;

    char cArray[] = {'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P'}; 
    int charSize;
    int cArraySize;
    int cArrayNumElements;

    int i;

    //code
    //iArray
    printf("\n\n");
    printf("Inline initialization & piece meal display of elements of iArray[] : \n");

    intSize = sizeof(int);
    iArraySize = sizeof(iArray);
    iArrayNumElements = iArraySize / intSize;

    for(i = 0; i < iArrayNumElements; i++)
    {
        printf("iArray[%d] (element %d) = %d\n", i, (i+1), iArray[i]);
    }

    printf("\n");
    printf("Size of datatype 'int'                              = %d bytes\n", intSize);
    printf("No. of elements in 'iArray[]'                       = %d elements\n", iArrayNumElements);
    printf("Size of 'iArray[]' (%d elements * %d bytes)         = %d bytes\n\n", iArrayNumElements, intSize, iArraySize);


    //fArray
    printf("\n\n");
    printf("Inline initialization & piece meal display of elements of fArray[] : \n");

    floatSize = sizeof(float);
    fArraySize = sizeof(fArray);
    fArrayNumElements = fArraySize / floatSize;

    i = 0;
    while(i < fArrayNumElements)
    {
        printf("fArray[%d] (element %d) = %f\n", i, (i+1), fArray[i]);
        i++;
    }

    printf("Size of datatype 'float'                            = %d bytes\n", floatSize);
    printf("No. of elements in 'fArray[]'                       = %d elements\n", fArrayNumElements);
    printf("Size of 'fArray[]' (%d elements * %d bytes)         = %d bytes\n\n", fArrayNumElements, floatSize, fArraySize);


    //cArray
    printf("\n\n");
    printf("Inline initialization & piece meal display of elements of cArray[] : \n");

    charSize = sizeof(char);
    cArraySize = sizeof(cArray);
    cArrayNumElements = cArraySize / charSize;

    i = 0;
    do
    {
        printf("cArray[%d] (element %d) = %c\n", i, (i+1), cArray[i]);
        i++;
    }while(i < cArrayNumElements);

    printf("Size of datatype 'char'                                 = %d bytes\n", charSize);
    printf("No. of elements in 'cArray[]'                           = %d elements\n", cArrayNumElements);
    printf("Size of 'cArray[]' (%d elements * %d bytes)             = %d bytes\n\n", cArrayNumElements, charSize, cArraySize);
    
    return(0);
}
