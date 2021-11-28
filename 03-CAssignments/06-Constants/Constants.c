//C Constants assignment
//Program to show the working of Constants

#include <stdio.h>

#define AMP_PI 3.1445625635263
#define AMP_STRING "Aditya Mohan Panchal"


//An enum or enumeration is an user defined datatype used to store a set/group of constant values or variables or elements.
//An enum is used to assign names to integral constants to make program easy to read & maintain & select a value from a well defined or fixed ranged or set of values 

//In enums if the first constant is not assigned any value, it is assumed or default value given is 0 i.e 'SUNDAY' will be 0
//And the rest of the constants are assigned consecutive integer values from 0 onwards i.e 'MONDAY' will be 1 & so on

//Unnamed enums
enum
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
};

enum
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

//Named enums
enum numbers
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE = 10,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

enum boolean
{
	TRUE = 1,
	FALSE = 0,
};

int main(void)
{
	//local const decl.
	const double amp_epsilon = 0.0000001;

	//code
	printf("\n\n");
	printf("Local constant epsilon = %.20lf\n\n", amp_epsilon);

	printf("Day num of sunday is %d\n", SUNDAY);
	printf("Day num of monday is %i\n", MONDAY);
	printf("Day num of tuesday is %d\n", TUESDAY);
	printf("Day num of wednesday is %i\n", WEDNESDAY);
	printf("Day num of thursday is %d\n", THURSDAY);
	printf("Day num of friday is %i\n", FRIDAY);
	printf("Day num of saturday is %i\n\n", SATURDAY);

	printf("Enum num of one is %d\n", ONE);
	printf("Enum num of two is %d\n", TWO);
	printf("Enum num of three is %d\n", THREE);
	printf("Enum num of four is %d\n", FOUR);
	printf("Enum num of five is %d\n", FIVE);
	printf("Enum num of six is %d\n", SIX);
	printf("Enum num of seven is %d\n", SEVEN);
	printf("Enum num of eight is %d\n", EIGHT);
	printf("Enum num of nine is %d\n", NINE);
	printf("Enum num of ten is %d\n\n", TEN);

	printf("Month num of jan is %d\n", JANUARY);
	printf("Month num of feb is %d\n", FEBRUARY);
	printf("Month num of mar is %d\n", MARCH);
	printf("Month num of apr is %d\n", APRIL);
	printf("Month num of may is %d\n", MAY);
	printf("Month num of jun is %d\n", JUNE);
	printf("Month num of july is %d\n", JULY);
	printf("Month num of aug is %i\n", AUGUST);
	printf("Month num of sept is %i\n", SEPTEMBER);
	printf("Month num of oct is %i\n", OCTOBER);
	printf("Month num of nov is %i\n", NOVEMBER);
	printf("Month num of july is %i\n\n", DECEMBER);

	printf("Value of TRUE is %d\n", TRUE);
	printf("Value of FALSE is %i\n\n", FALSE);

	printf("Value of AMP_PI macro is %.10lf\n", AMP_PI);
	printf("Area of circle with radius 2 units is %f\n\n", (AMP_PI * 2.0f * 2.0f)); //area of circle = pi * r * r

	printf("My string using #define macro is \"" AMP_STRING "\"\n");

	return 0;
}
