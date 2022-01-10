//C Structs assignment : Struct Containing Struct
//Program to show struct within struct & inline initialization

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int length, breadth, area;

    struct ampPoint
    {
        int x;
        int y;
    };

    struct ampRect
    {
        struct ampPoint pt1;
        struct ampPoint pt2;
    };

    struct ampRect rect = { {19, 30}, {24, 35} };   //inline initialization

    //code
    length = rect.pt2.y - rect.pt1.y;
    if(length < 0)
        length = length * -1;   //to make length positive

    breadth = rect.pt2.x - rect.pt1.x;
    if(breadth < 0)
        breadth = breadth * -1;   //to make breadth positive

    area = length * breadth;

    printf("\n\n");
    printf("Length of rectangle = %d\n\n", length);
    printf("Breadth of rectangle = %d\n\n", breadth);
    printf("Area of rectangle = %d\n\n", area);

    return(0);
}
