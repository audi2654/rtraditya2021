// GLUT OGL Clock
// Date: 11th Jan 2022 02:39pm

// Command
// cl.exe /c /EHcs /I C:\RTR2021Files\freeglut\include GlutClock.cpp	(including here a folder with specific path)
// link.exe GlutClock.obj /LIBPATH:C:\RTR2021Files\freeglut\lib freeglut.lib /SUBSYSTEM:CONSOLE

// header files
//#include <GL\freeglut.h>
#include "C:\RTR2021Files\freeglut\include\GL\freeglut.h"
#include <Windows.h>
#include <math.h>

// global variables
bool bFullScreen = false;

// entry-point function
int main(int argc, char* argv[])
{
	// local function declarations
	void initialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	// code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(600, 600);	//put 800, 800 for clock
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Aditya's GLUT Clock");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	return(0);
}

void initialize(void)
{
	// code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//window background color
}

void resize(int width, int height)
{
	// code
	glViewport(0, 0, width, height);
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	//Points
	//Lines
	//Triangles

	//Quads
	//Polygons (shape with n vertices)

	//projection matrix

	//glLineWidth(); //1.0f <-> 32.0f
	//glPointSize(10.0f);

	//for points
	//use graph paper
	//use trignometry
	//glRotatef()
	//glTranslatef()

	glPointSize(10.0f);
	glBegin(GL_POINTS);

		//-1.0 <-> 1.0
		//From top anticlockwise

		//pt1 - origin
		glColor3f(0.3f, 0.7f, 0.5f);	//RGB
		glVertex3f(0.0f, 0.0f, 0.0f);	//X, Y, Z

		//pt2 - left
		glColor3f(1.0f, 1.0f, 0.0f);		//YELLOW
		glVertex3f(-0.30f, 0.0f, 0.0f);
		
		//pt3 - right
		glColor3f(1.0f, 1.0f, 0.0f);		//YELLOW
		glVertex3f(0.30f, 0.0f, 0.0f);
		
		//pt4 - top
		glColor3f(1.0f, 0.0f, 0.0f);		//RED
		glVertex3f(0.0f, 0.30f, 0.0f);
		
		//pt5 - bottom
		glColor3f(1.0f, 0.0f, 0.0f);		//RED
		glVertex3f(0.0f, -0.30f, 0.0f);
		
		//pt6-7 - between 12-3
		glColor3f(0.0f, 0.0f, 1.0f);		//BLUE
		glVertex3f(0.24f, 0.13f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);		//GREEN
		glVertex3f(0.13f, 0.24f, 0.0f);
		
		//pt8-9 - between 3-6
		glColor3f(1.0f, 0.0f, 1.0f);		//MAGENTA
		glVertex3f(0.24f, -0.13f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f);		//CYAN
		glVertex3f(0.13f, -0.24f, 0.0f);

		//pt9-10 - between 6-9
		glColor3f(0.0f, 0.0f, 1.0f);		//BLUE
		glVertex3f(-0.24f, -0.13f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);		//GREEN
		glVertex3f(-0.13f, -0.24f, 0.0f);

		//pt10-11 - between 9-12
		glColor3f(1.0f, 0.0f, 1.0f);		//MAGENTA
		glVertex3f(-0.24f, 0.13f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f);		//CYAN
		glVertex3f(-0.13f, 0.24f, 0.0f);

	glEnd();

	//for hour short hand
	glLineWidth(4.0f);
	glBegin(GL_LINES);

		//origin
		glColor3f(1.0f, 1.0f, 2.0f);	//RGB
		glVertex3f(0.0f, 0.0f, 0.0f);	//X, Y, Z

		//short hand
		glColor3f(1.0f, 1.0f, 2.0f);
		glVertex3f(-0.08f, 0.14f, 0.0f);

	glEnd();

	//for minute long hand
	glLineWidth(2.0f);
	glBegin(GL_LINES);

		//origin	
		glColor3f(1.0f, 1.0f, 2.0f);	//RGB
		glVertex3f(0.0f, 0.0f, 0.0f);	//X, Y, Z
		
		//long hand
		glColor3f(1.0f, 1.0f, 2.0f);
		glVertex3f(0.14f, 0.18f, 0.0f);

	glEnd();

	//for seconds long hand
	glLineWidth(1.0f);
	glBegin(GL_LINES);

		//origin	
		glColor3f(1.0f, 1.0f, 2.0f);	//RGB
		glVertex3f(0.0f, 0.0f, 0.0f);	//X, Y, Z
		
		//long hand
		glColor3f(1.0f, 1.0f, 2.0f);
		glVertex3f(0.14f, -0.18f, 0.0f);

	glEnd();
/*
//Frame around clock
//-----------------------------------

	//Circle formula (x-a)^2 + (y-b)^2 = r^2  where a & b are 0,0 origin coordinates
	//a & b is origin so  0, 0
	//hence (x*x) + (y*y) = (r*r)
	//x^2 = r^2 - y^2
	//y^2 = r^2 - x^2

	float radiusOfCircle = 1.0f;
	float ptX = 0.0f;
	float ptY = 0.5f;

	float i,j;
	glPointSize(1.0f);
	glBegin(GL_POINTS);

	for(i = ptX, j = ptY; i <= 1.0f, j >= 0.001f; i = i + 0.001, j = j - 0.001)
	{
		//pt1 - origin
		// glColor3f(1.0f, 1.0f, 2.0f);	//RGB
		// glVertex3f(0.0f, 0.0f, 0.0f);	//X, Y, Z

		if(((ptX * ptX) + (ptY * ptY) >= (radiusOfCircle * radiusOfCircle)) || ((ptX * ptX) + (ptY * ptY) <= (radiusOfCircle * radiusOfCircle)))
		{
			// glColor(1.0f, 1.0f, 1.0f);
			// glVertex3f(0.0f,0.0f,0.0f);

			glColor3f(0.3f, 0.7f, 0.5f);	//RGB
			glVertex3f(i, j, 0.0f);

			glColor3f(0.3f, 0.7f, 0.5f);	//RGB
			glVertex3f(-i, j, 0.0f);

			glColor3f(0.3f, 0.7f, 0.5f);	//RGB
			glVertex3f(-i, -j, 0.0f);

			glColor3f(0.3f, 0.7f, 0.5f);	//RGB
			glVertex3f(i, -j, 0.0f);
		}
	}

	glEnd();
*/	
//-----------------------------------------------------

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	// code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;

	case 'F':
	case 'f':
		if (bFullScreen == false)
		{
			glutFullScreen();
			bFullScreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullScreen = false;
		}
		break;

	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	// code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		glutLeaveMainLoop();
		break;

	default:
		break;
	}
}

void uninitialize()
{
	// empty function
}
