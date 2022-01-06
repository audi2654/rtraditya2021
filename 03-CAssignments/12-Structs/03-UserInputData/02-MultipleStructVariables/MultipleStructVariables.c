//C Structs assignment : Struct User Input method - 2
//Program to show various ways to take user input in struct vars

#include <stdio.h>

//defining struct
struct ampPoint
{
    int x;
    int y;
};

int main(int argc, char* argv[], char* envp[])
{
    //var decl.
    struct ampPoint ptA, ptB, ptC,ptD, ptE;

    //code
    //taking user input for values of data members of struct var data
    printf("\n\n");
    printf("Enter X-coordinate for ptA : ");
    scanf("%d", &ptA.x);
    printf("Enter Y-coordinate for ptA : ");
    scanf("%d", &ptA.y);

    printf("\n");
    printf("Enter X-coordinate for ptB : ");
    scanf("%d", &ptB.x);
    printf("Enter Y-coordinate for ptB : ");
    scanf("%d", &ptB.y);

    printf("\n");
    printf("Enter X-coordinate for ptC : ");
    scanf("%d", &ptC.x);
    printf("Enter Y-coordinate for ptC : ");
    scanf("%d", &ptC.y);

    printf("\n");
    printf("Enter X-coordinate for ptD : ");
    scanf("%d", &ptD.x);
    printf("Enter Y-coordinate for ptD : ");
    scanf("%d", &ptD.y);

    printf("\n");
    printf("Enter X-coordinate for ptE : ");
    scanf("%d", &ptE.x);
    printf("Enter Y-coordinate for ptE : ");
    scanf("%d", &ptE.y);
    
    //displaying values of data members of 'struct ampDataStruct'
    printf("\n\n");
    printf("ptA : X-coordinate = %d, Y-Coordinate = %d\n", ptA.x, ptA.y);
    printf("ptB : X-coordinate = %d, Y-Coordinate = %d\n", ptB.x, ptB.y);
    printf("ptC : X-coordinate = %d, Y-Coordinate = %d\n", ptC.x, ptC.y);
    printf("ptD : X-coordinate = %d, Y-Coordinate = %d\n", ptD.x, ptD.y);
    printf("ptE : X-coordinate = %d, Y-Coordinate = %d\n", ptE.x, ptE.y);

    return(0);
}
