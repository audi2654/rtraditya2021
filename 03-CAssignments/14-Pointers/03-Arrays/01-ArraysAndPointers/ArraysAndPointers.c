//C Pointer Arrays assignment : Arrays & pointers
//Program for arrays & pointers

#include <stdio.h>

int main(void)
{
	//var decl.
	int amp_iArray[] = {1,2,3,4,5};
	float amp_fArray[] = {9.9f, 8.8f, 7.7f, 6.6, 5.5f};
	double amp_dArray[] = {6.8888, 5.88, 2.111111};
	char amp_cArray[] = {'A', 'D', 'I', 'T', 'Y', 'A'};

	//code
	printf("\n\n");
	printf("Integer array elements & their addresses are :\n");
	printf("amp_iArray[0] = %d \t at address : %p\n", *(amp_iArray + 0), (amp_iArray + 0));
	printf("amp_iArray[1] = %d \t at address : %p\n", *(amp_iArray + 1), (amp_iArray + 1));
	printf("amp_iArray[2] = %d \t at address : %p\n", *(amp_iArray + 2), (amp_iArray + 2));
	printf("amp_iArray[3] = %d \t at address : %p\n", *(amp_iArray + 3), (amp_iArray + 3));
	printf("amp_iArray[4] = %d \t at address : %p\n", *(amp_iArray + 4), (amp_iArray + 4));

	printf("\n\n");
	printf("Floating array elements & their addresses are :\n");
	printf("amp_fArray[0] = %f \t at address : %p\n", *(amp_fArray + 0), (amp_fArray + 0));
	printf("amp_fArray[1] = %f \t at address : %p\n", *(amp_fArray + 1), (amp_fArray + 1));
	printf("amp_fArray[2] = %f \t at address : %p\n", *(amp_fArray + 2), (amp_fArray + 2));
	printf("amp_fArray[3] = %f \t at address : %p\n", *(amp_fArray + 3), (amp_fArray + 3));
	printf("amp_fArray[4] = %f \t at address : %p\n", *(amp_fArray + 4), (amp_fArray + 4));

	printf("\n\n");
	printf("Double array elements & their addresses are :\n");
	printf("amp_dArray[0] = %lf \t at address : %p\n", *(amp_dArray + 0), (amp_dArray + 0));
	printf("amp_dArray[1] = %lf \t at address : %p\n", *(amp_dArray + 1), (amp_dArray + 1));
	printf("amp_dArray[2] = %lf \t at address : %p\n", *(amp_dArray + 2), (amp_dArray + 2));

	printf("\n\n");
	printf("Character array elements & their addresses are :\n");
	printf("amp_cArray[0] = %c \t at address : %p\n", *(amp_cArray + 0), (amp_cArray + 0));
	printf("amp_cArray[1] = %c \t at address : %p\n", *(amp_cArray + 1), (amp_cArray + 1));
	printf("amp_cArray[2] = %c \t at address : %p\n", *(amp_cArray + 2), (amp_cArray + 2));
	printf("amp_cArray[3] = %c \t at address : %p\n", *(amp_cArray + 3), (amp_cArray + 3));
	printf("amp_cArray[4] = %c \t at address : %p\n", *(amp_cArray + 4), (amp_cArray + 4));
	printf("amp_cArray[5] = %c \t at address : %p\n", *(amp_cArray + 5), (amp_cArray + 5));

	return 0;
}
