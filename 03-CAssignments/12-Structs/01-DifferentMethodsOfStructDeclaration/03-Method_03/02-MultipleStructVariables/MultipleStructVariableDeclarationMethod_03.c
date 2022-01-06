//C Structs assignment : Struct declaration method - 3B
//Program to declare a struct & using MULTIPLE struct variables

#include <stdio.h>

struct ampPoint ; //declaring 1 struct var globally

int main(int argc, char* argv[], char* envp[])
{
    //defining struct
    struct ampPoint
    {
        int x;
        int y;
    } ptA, ptB, ptC, ptD; //directly declaring struct variables of type 'struct ampPoint' locally
    
    //var decl.
    struct ampPoint ptE;    //declaring 1 struct var locally

    //code
    //assigning values to each struct var
    ptA.x = -10;
    ptA.y = -30;
    
    ptB.x = 90;
    ptB.y = 70;

    ptC.x = -45;
    ptC.y = 80;

    ptD.x = -60;
    ptD.y = 100;

    ptE.x = 6;
    ptE.y = 2;

    //displaying values of data members of each struct var
    printf("\n\n");
    printf("Coordinates of ptA : x = %d, y = %d\n", ptA.x, ptA.y);
    printf("Coordinates of ptB : x = %d, y = %d\n", ptB.x, ptB.y);
    printf("Coordinates of ptC : x = %d, y = %d\n", ptC.x, ptC.y);
    printf("Coordinates of ptD : x = %d, y = %d\n", ptD.x, ptD.y);
    printf("Coordinates of ptE : x = %d, y = %d\n", ptE.x, ptE.y);

    //size of any struct will rarely be equal to the total of sizes of each of its members
    //the difference in size is due to compiler padding & it is machine dependant

    return(0);
}
