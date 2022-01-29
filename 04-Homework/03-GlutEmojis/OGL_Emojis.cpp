// GLUT OGL Emojis

// Command
// cl.exe /c /EHcs /I C:\RTR2021Files\freeglut\include OGL.cpp	(including here a folder with specific path)
// link.exe OGL.obj /LIBPATH:C:\RTR2021Files\freeglut\lib freeglut.lib /SUBSYSTEM:CONSOLE

// header files
//#include <GL\freeglut.h>
#include "C:\RTR2021Files\freeglut\include\GL\freeglut.h"
#include <Windows.h>
#include <math.h>
#include <corecrt_math_defines.h>

// global variables
bool bFullScreen = false;

void amp_MouthLess(void);
void amp_NeutralFace();
void amp_ExpressionLess();

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

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Aditya's Emojis");

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	/*
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);				//top
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, -0.05f, 0.0f);			//bottom-left
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.05f, -0.05f, 0.0f);			//bottom-right
	glEnd();
	*/

	
	//amp_MouthLess();
	//amp_NeutralFace();
	amp_ExpressionLess();


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

void amp_MouthLess()
{
	//-----------------------------------
	//Circle
	//degress to radians
	// 360 * pi / 180 = rad
	// rad * 180 / pi = deg

	glPointSize(5.0f);
	glColor3f(1.0f, 0.843f, 0.0f);
	glBegin(GL_POLYGON);

	GLfloat radius = 0.7f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate, Y_coordinate);
	}

	glEnd();
	//-----------------------------------

	//-----------------------------------
	//EYE CIRCLE - RIGHT side
	glPointSize(0.5f);
	glColor3f(0.545f, 0.271f, 0.075f);
	glBegin(GL_POLYGON);

	GLfloat Rradius = 0.1f;
	GLfloat Rincre = 1.0f;
	GLfloat RoriginX = 0.3f;
	GLfloat RoriginY = 0.3f;


	for (float i = 0; i < 360; i = i + Rincre)
	{
		GLfloat RX_coordinate = Rradius * cos(i * M_PI / 180.0f);
		GLfloat RY_coordinate = Rradius * sin(i * M_PI / 180.0f);
		glVertex2f(RoriginX + RX_coordinate, RoriginY + RY_coordinate);
	}
	glEnd();
	//-----------------------------------

	//EYE CIRCLE - LEFT side
	glPointSize(0.5f);
	glColor3f(0.545f, 0.271f, 0.075f);
	glBegin(GL_POLYGON);

	GLfloat Lradius = 0.1f;
	GLfloat Lincre = 1.0f;
	GLfloat LoriginX = -0.3f;
	GLfloat LoriginY = 0.3f;


	for (float i = 0; i < 360; i = i + Rincre)
	{
		GLfloat LX_coordinate = Lradius * cos(i * M_PI / 180.0f);
		GLfloat LY_coordinate = Lradius * sin(i * M_PI / 180.0f);
		glVertex2f(LoriginX + LX_coordinate, LoriginY + LY_coordinate);
	}
	glEnd();
	//-----------------------------------
}

void amp_NeutralFace()
{
	amp_MouthLess();

	//------------------------------------
	//MOUTH
	glColor3f(0.545f, 0.271f, 0.075f);
	glLineWidth(7.0f);

	glBegin(GL_LINES);

	//top line
	glVertex3f(0.2f, -0.3f, 0.0f);
	glVertex3f(-0.2f, -0.3f, 0.0f);

	glEnd();
}

void amp_ExpressionLess()
{
	//-----------------------------------
	//Circle
	//degress to radians
	// 360 * pi / 180 = rad
	// rad * 180 / pi = deg

	glPointSize(5.0f);
	glColor3f(1.0f, 0.843f, 0.0f);
	glBegin(GL_POLYGON);

	GLfloat radius = 0.7f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate, Y_coordinate);
	}

	glEnd();
	//-----------------------------------

	//-----------------------------------
	//EYE CIRCLE - RIGHT side
	glPointSize(0.5f);
	glColor3f(0.545f, 0.271f, 0.075f);
	glBegin(GL_POLYGON);

	GLfloat RoriginX = 0.3f;
	GLfloat RoriginY = 0.6f;

	//top line
	glVertex3f(RoriginX + 0.2f, RoriginY + (-0.3f), 0.0f);
	glVertex3f(RoriginX + (-0.2f), RoriginY + (-0.3f), 0.0f);

	//left line
	glVertex3f(RoriginX + (-0.2f), RoriginY + (-0.3f), 0.0f);
	glVertex3f(RoriginX + (-0.2f), RoriginY + (-0.4f), 0.0f);

	//bottom line
	glVertex3f(RoriginX + 0.2f, RoriginY + (-0.4f), 0.0f);
	glVertex3f(RoriginX + (-0.2f), RoriginY + (-0.4f), 0.0f);

	//right line
	glVertex3f(RoriginX + (0.2f), RoriginY + (-0.3f), 0.0f);
	glVertex3f(RoriginX + (0.2f), RoriginY + (-0.4f), 0.0f);

	glEnd();
	//-----------------------------------

	//EYE CIRCLE - LEFT side
	glPointSize(0.5f);
	glColor3f(0.545f, 0.271f, 0.075f);
	glBegin(GL_POLYGON);

	GLfloat LoriginX = -0.3f;
	GLfloat LoriginY = 0.6f;

	//top line
	glVertex3f(LoriginX + 0.2f, LoriginY + (-0.3f), 0.0f);
	glVertex3f(LoriginX + (-0.2f), LoriginY + (-0.3f), 0.0f);

	//left line
	glVertex3f(LoriginX + (-0.2f), LoriginY + (-0.3f), 0.0f);
	glVertex3f(LoriginX + (-0.2f), LoriginY + (-0.4f), 0.0f);

	//bottom line
	glVertex3f(LoriginX + 0.2f, LoriginY + (-0.4f), 0.0f);
	glVertex3f(LoriginX + (-0.2f), LoriginY + (-0.4f), 0.0f);

	//right line
	glVertex3f(LoriginX + (0.2f), LoriginY + (-0.3f), 0.0f);
	glVertex3f(LoriginX + (0.2f), LoriginY + (-0.4f), 0.0f);

	glEnd();
	//-----------------------------------

	//------------------------------------
	//MOUTH
	glColor3f(0.545f, 0.271f, 0.075f);

	glBegin(GL_POLYGON);

	//top line
	glVertex3f(0.2f, -0.3f, 0.0f);
	glVertex3f(-0.2f, -0.3f, 0.0f);

	//left line
	glVertex3f(-0.2f, -0.3f, 0.0f);
	glVertex3f(-0.2f, -0.4f, 0.0f);

	//bottom line
	glVertex3f(0.2f, -0.4f, 0.0f);
	glVertex3f(-0.2f, -0.4f, 0.0f);

	//right line
	glVertex3f(0.2f, -0.3f, 0.0f);
	glVertex3f(0.2f, -0.4f, 0.0f);

	glEnd();
}
