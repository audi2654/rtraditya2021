//C Structs assignment : Struct declaration method - 2C
//Program to declare TWO struct & using MULTIPLE struct variables

#include <stdio.h>

//defining struct
struct ampPoint
{
    int x;
    int y;
};

struct ampPointProperties
{
    int quadrant;
    char axisLocation[15];
};

//declaring struct vars globally
struct ampPoint ptA;
struct ampPointProperties ptProperties;


int main(int argc, char* argv[], char* envp[])
{
    //code
    //user input to initialize members of struct ampPoint var
    printf("\n\n");
    printf("Enter X-coordinate for pt. A : ");  
    scanf("%d", &ptA.x);
    printf("Enter Y-coordinate for pt. A : ");  
    scanf("%d", &ptA.y);

    printf("\n");
    printf("Coordinates of ptA : x = %d, y = %d\n", ptA.x, ptA.y);

    if(ptA.x == 0 && ptA.y == 0)
        printf("pt. A is at Origin (%d, %d)\n", ptA.x, ptA.y);
    else
    {
        if(ptA.x == 0)
        {
            if(ptA.y < 0)
                strcpy(ptProperties.axisLocation, "Negative Y");

            if(ptA.y > 0)
                strcpy(ptProperties.axisLocation, "Positive Y");

            ptProperties.quadrant = 0;  //a point lying on any of the coordinate axis is not a part of any quadrant
            printf("pt. A lies on %s axis\n", ptProperties.axisLocation);
        }
        else if(ptA.y == 0)
        {
            if(ptA.x < 0)
                strcpy(ptProperties.axisLocation, "Negative X");

            if(ptA.x > 0)
                strcpy(ptProperties.axisLocation, "Positive X");

            ptProperties.quadrant = 0;  //a point lying on any of the coordinate axis is not a part of any quadrant
            printf("pt. A lies on %s axis\n", ptProperties.axisLocation);
        }
        else
        {
            ptProperties.axisLocation[0] = '\0';    //a point lying in any of the 4 quadrants cannot be lying on any of the coordinate axes

            if(ptA.x > 0 && ptA.y > 0)          //x is +ve, y is +ve
                ptProperties.quadrant = 1;
            else if(ptA.x < 0 && ptA.y > 0)     //x is -ve, y is +ve
                ptProperties.quadrant = 2;
            else if(ptA.x < 0 && ptA.y < 0)     //x is -ve, y is -ve
                ptProperties.quadrant = 3;
            else                                //x is +ve, y is -ve
                ptProperties.quadrant = 4;

            printf("Pt. A lies in quadrant number %d\n\n", ptProperties.quadrant);
        }
    }

    //size of any struct will rarely be equal to the total of sizes of each of its members
    //the difference in size is due to compiler padding & it is machine dependant

    return(0);
}
