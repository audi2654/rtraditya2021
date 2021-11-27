//C Variables assignment

#include <stdio.h>
int main(void)
{
    //var decl.
    int i = 5;
    float f = 3.9f;
    double d = 8.041997;
    char c = 'A';

    //code
    printf("\n\n");

    printf("i = %d\n", i);
	printf("f = %f\n", f);
	printf("d = %lf\n", d);
	printf("c = %c\n", c);

	printf("\n\n");

	i = 56;
	f = 80.56f;
	d = 121.12123;
	f = 'z';

	printf("i = %d\n", i);
	printf("f = %f\n", f);
	printf("d = %lf\n", d);
	printf("c = %c\n", c);

	printf("\n\n");

	return(0);
}
