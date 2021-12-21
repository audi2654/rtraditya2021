//C Arrays assignment : 1D Array
//Program to show inline initialization of 1D array with piece meal display

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

    //code
    //iArray
    printf("\n\n");
    printf("Inline initialization & piece meal display of elements of iArray[] : \n");
    printf("iArray[0]) (1st element) = %d\n", iArray[0]);
    printf("iArray[1]) (2nd element) = %d\n", iArray[1]);
    printf("iArray[2]) (3rd element) = %d\n", iArray[2]);
    printf("iArray[3]) (4th element) = %d\n", iArray[3]);
    printf("iArray[4]) (5th element) = %d\n", iArray[4]);
    printf("iArray[5]) (6th element) = %d\n", iArray[5]);
    printf("iArray[6]) (7th element) = %d\n", iArray[6]);
    printf("iArray[7]) (8th element) = %d\n", iArray[7]);
    printf("iArray[8]) (9th element) = %d\n", iArray[8]);
    printf("iArray[9]) (10th element) = %d\n\n", iArray[9]);

    intSize = sizeof(int);
    iArraySize = sizeof(iArray);
    iArrayNumElements = iArraySize / intSize;
    printf("Size of datatype 'int'                              = %d bytes\n", intSize);
    printf("No. of elements in 'iArray[]'                       = %d elements\n", iArrayNumElements);
    printf("Size of 'iArray[]' (%d elements * %d bytes)         = %d bytes\n\n", iArrayNumElements, intSize, iArraySize);


    //fArray
    printf("\n\n");
    printf("Inline initialization & piece meal display of elements of fArray[] : \n");
    printf("fArray[0]) (1st element) = %f\n", fArray[0]);
    printf("fArray[1]) (2nd element) = %f\n", fArray[1]);
    printf("fArray[2]) (3rd element) = %f\n", fArray[2]);
    printf("fArray[3]) (4th element) = %f\n", fArray[3]);
    printf("fArray[4]) (5th element) = %f\n", fArray[4]);
    printf("fArray[5]) (6th element) = %f\n", fArray[5]);
    printf("fArray[6]) (7th element) = %f\n", fArray[6]);
    printf("fArray[7]) (8th element) = %f\n", fArray[7]);
    printf("fArray[8]) (9th element) = %f\n", fArray[8]);
    printf("fArray[9]) (10th element) = %f\n\n", fArray[9]);

    floatSize = sizeof(float);
    fArraySize = sizeof(fArray);
    fArrayNumElements = fArraySize / floatSize;
    printf("Size of datatype 'float'                            = %d bytes\n", floatSize);
    printf("No. of elements in 'fArray[]'                       = %d elements\n", fArrayNumElements);
    printf("Size of 'fArray[]' (%d elements * %d bytes)         = %d bytes\n\n", fArrayNumElements, floatSize, fArraySize);


    //cArray
    printf("\n\n");
    printf("Inline initialization & piece meal display of elements of cArray[] : \n");
    printf("cArray[0]) (1st element) = %c\n", cArray[0]);
    printf("cArray[1]) (2nd element) = %c\n", cArray[1]);
    printf("cArray[2]) (3rd element) = %c\n", cArray[2]);
    printf("cArray[3]) (4th element) = %c\n", cArray[3]);
    printf("cArray[4]) (5th element) = %c\n", cArray[4]);
    printf("cArray[5]) (6th element) = %c\n", cArray[5]);
    printf("cArray[6]) (7th element) = %c\n", cArray[6]);
    printf("cArray[7]) (8th element) = %c\n", cArray[7]);
    printf("cArray[8]) (9th element) = %c\n", cArray[8]);
    printf("cArray[9]) (10th element) = %c\n", cArray[9]);
    printf("cArray[10]) (11th element) = %c\n", cArray[10]);
    printf("cArray[11]) (12th element) = %c\n", cArray[11]);
    printf("cArray[12]) (13th element) = %c\n\n", cArray[12]);

    charSize = sizeof(char);
    cArraySize = sizeof(cArray);
    cArrayNumElements = cArraySize / charSize;
    printf("Size of datatype 'char'                                 = %d bytes\n", charSize);
    printf("No. of elements in 'cArray[]'                           = %d elements\n", cArrayNumElements);
    printf("Size of 'cArray[]' (%d elements * %d bytes)             = %d bytes\n\n", cArrayNumElements, charSize, cArraySize);
    
    return(0);
}
