//C Structs assignment : Struct Containing Struct
//Program to show struct within struct declaration

#include <stdio.h>

struct ampPoint
{
    int x;
    int y;
};

struct ampRect
{
    struct ampPoint pt1, pt2;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    int length, breadth, area;
    struct ampRect rect;

    //code
    printf("\n\n");
    printf("Enter leftmost X-coordinate of rectangle : ");
    scanf("%d", &rect.pt1.x);

    printf("\n");
    printf("Enter bottommost Y-coordinate of rectangle : ");
    scanf("%d", &rect.pt1.y);

    printf("\n");
    printf("Enter rightmost X-coordinate of rectangle : ");
    scanf("%d", &rect.pt2.x);

    printf("\n");
    printf("Enter topmost Y-coordinate of rectangle : ");
    scanf("%d", &rect.pt2.y);

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
