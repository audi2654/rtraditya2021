//C Structs & Unions assignment : Struct With Functions
//Program to show working of structs using functions

#include <stdio.h>

//defining data
struct ampData
{
    int i;
    float f;
    double d;
    char c;
};

int main(int argc, char* argv[], char* envp[])
{
    //function prototype
    struct ampData AddStructMembers(struct ampData, struct ampData, struct ampData);

    //var decl.
    struct ampData d1, d2, d3, answer_data;

    //code
    printf("\n\n");

    //data - 1
    printf("DATA - 1");
    printf("\n");
    printf("Enter int value for i of data1 : ");
    scanf("%d", &d1.i);

    printf("\n");
    printf("Enter float value for f of data1 : ");
    scanf("%f", &d1.f);

    printf("\n");
    printf("Enter double value for d of data1 : ");
    scanf("%lf", &d1.d);

    printf("\n");
    printf("Enter char value for c of data1 : ");
    d1.c = getch();
    printf("%c", d1.c);

    //data - 2
    printf("\n\n");
    printf("DATA - 2");
    printf("\n");
    printf("Enter int value for i of data2 : ");
    scanf("%d", &d2.i);

    printf("\n");
    printf("Enter float value for f of data2 : ");
    scanf("%f", &d2.f);

    printf("\n");
    printf("Enter double value for d of data2 : ");
    scanf("%lf", &d2.d);

    printf("\n");
    printf("Enter char value for c of data2 : ");
    d2.c = getch();
    printf("%c", d2.c);

    //data - 3
    printf("\n\n");
    printf("DATA - 3");
    printf("\n");
    printf("Enter int value for i of data3 : ");
    scanf("%d", &d3.i);

    printf("\n");
    printf("Enter float value for f of data3 : ");
    scanf("%f", &d3.f);

    printf("\n");
    printf("Enter double value for d of data3 : ");
    scanf("%lf", &d3.d);

    printf("\n");
    printf("Enter char value for c of data3 : ");
    d3.c = getch();
    printf("%c", d3.c);

    answer_data = AddStructMembers(d1, d2, d3);

    printf("\n\n");
    printf("ANSWER\n");
    printf("answer_data.i = %d\n", answer_data.i);
    printf("answer_data.f = %f\n", answer_data.f);
    printf("answer_data.d = %lf\n\n", answer_data.d);

    answer_data.c = d1.c;
    printf("answer_data.c (from data1) = %c\n", answer_data.c);

    answer_data.c = d2.c;
    printf("answer_data.c (from data2) = %c\n", answer_data.c);

    answer_data.c = d3.c;
    printf("answer_data.c (from data3) = %c\n\n", answer_data.c);

    return(0);
}

//function definition
struct ampData AddStructMembers(struct ampData md1, struct ampData md2, struct ampData md3)
{
    //var decl.
    struct ampData answer;

    //code
    answer.i = md1.i + md2.i + md3.i;
    answer.f = md1.f + md2.f + md3.f;
    answer.d = md1.d + md2.d + md3.d;

    return(answer);
}
