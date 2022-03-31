// gluLookAt() Concept Program
// Date: 19th March 2022

// Command only in 32 bit dev cmd prompt
// cl.exe /c /EHcs /I C:\RTR2021Files\freeglut\include\GL OGL.cpp	(including here a folder with specific path)
// link.exe OGL.obj /LIBPATH:C:\RTR2021Files\freeglut\lib freeglut.lib /SUBSYSTEM:CONSOLE

// header files
#include "C:\RTR2021Files\freeglut\include\GL\freeglut.h"
//#include <GL\freeglut.h>
#include <Windows.h>

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
	glutInit(&argc, argv);	//combo of WinMain, WndProc, wndclass, RegisterClassEx()

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//similar to PFD_DOUBLEBUFFER & PFD_TYPE_RGBA
	//GLUT_DEPTH here is similar to pfd.cDepthBits = 32; in native & must to create 3D in glut 
	
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("AMP OpenGL");	//combo of CreateWindow, ShowWindow, SetForegroundWindow, SetFocus

	initialize();

	glutReshapeFunc(resize);		//combo of WM_SIZE & void resize(int width, int height)
	glutDisplayFunc(display);		//similar to void display(void)
	glutKeyboardFunc(keyboard);		//WM_KEYDOWN & WM_KEYDOWN
	glutMouseFunc(mouse);			//WM_LBUTTONDOWN
	glutCloseFunc(uninitialize);	//uninitialize()

	glutMainLoop();					//game loop in WinMain()

	return(0);
}

void initialize(void)
{
	// code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void resize(int width, int height)
{
	// code
	if (height < 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(-1.0f,1.0f,-1.0f,1.0f,1.5f,20.0f);
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//moving camera i.e view transformation
	gluLookAt(-3.0f, -2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);

	/*glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();*/

	glutWireCube(1.0f);

	glutSwapBuffers();		//similar to SwapBuffers(ghdc);
}

void keyboard(unsigned char key, int x, int y)	//similar to (key is window message, lparam, wparam)
{
	// code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();	//DestroyWindow()
		break;

	case 'F':
	case 'f':
		//ToggleFullScreen()
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
