//Date: 10/04/2022
//RTR2021 OGL PushPopMatrix SolarSystem with Moon
//Press Y, D, Q, W, M, N to make movements

//header files
#include <windows.h>
#include <stdio.h>			//for file I/O functions
#include <stdlib.h>			//for exit()
#include "OGL.h"			//for icon
#include <GL/glu.h>

//OpenGL header files
#include <GL/gl.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//OpenGL libraries
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

//global func decl.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global var decl.
//for fullscreen
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL gbFullScreen = FALSE;

//for centered window
int xWindowPosition = 0;
int yWindowPosition = 0;

int cxWindowWidth = 800;
int cyWindowHeight = 600;

//for active window
BOOL gbActiveWindow = FALSE;

//for file I/O
FILE* gpFile = NULL;

//for solar system
GLint day = 0;
GLint year = 0;
GLint moon_revolve = 0;
GLint moon_spin = 0;
GLint satellite_revolve = 0;
GLint satellite_spin = 0;

GLUquadric *quadric = NULL;		//bowl to draw speheres into

//entry point func
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function decl.
	int initialize(void);
	void display(void);
	void update(void);
	void uninitialize(void);

	//local var decl.
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("AMP RTR Window");
	BOOL bDone = FALSE;		//for special loop
	int iRetVal = 0;

	int cxScreenWidth, cyScreenHeight;
	cxScreenWidth = GetSystemMetrics(SM_CXSCREEN);		//1366
	cyScreenHeight = GetSystemMetrics(SM_CYSCREEN);     //768

	//code
	//file IO
	if (fopen_s(&gpFile, "Log.txt", "w") != 0)      //fopen_s safe/secured
	   //fopen_s(out parameter ptr for the file opened or created, "name of file to open or create / path of file to read/write", reason to open file "r", "w", "a", "r+", etc)
	{
		MessageBox(HWND_DESKTOP, "Creation of Log file failed. Exitting!", "File I/O Error", MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Window Log file CREATED successfully!\n");
	}

	//initialize wndclass struct
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));

	//register wndclass struct in memory
	RegisterClassEx(&wndclass);

	//create window
	xWindowPosition = (cxScreenWidth / 2) - (cxWindowWidth / 2);
	yWindowPosition = (cyScreenHeight / 2) - (cyWindowHeight / 2);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("AMP OpenGL"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		xWindowPosition,
		yWindowPosition,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//initialize
	iRetVal = initialize();
	if (iRetVal == -1)
	{
		fprintf(gpFile, "Choose Pixel Format FAILED\n");
		uninitialize();
	}
	else if (iRetVal == -2)
	{
		fprintf(gpFile, "Set Pixel Format FAILED\n");
		uninitialize();
	}
	else if (iRetVal == -3)
	{
		fprintf(gpFile, "Create OpenGL Rendering Context FAILED\n");
		uninitialize();
	}
	else if (iRetVal == -4)
	{
		fprintf(gpFile, "Making OpenGL Context as Current Context FAILED\n");
		uninitialize();
	}
	else
	{
		fprintf(gpFile, "initialize() SUCCESSFULL\n");
	}

	//show window
	ShowWindow(hwnd, iCmdShow);

	//foregrounding & focusing the window
	SetForegroundWindow(hwnd);		//here ghwnd would also work, but its primary use is for funcs outside winmain, we should use local var hwnd here
	SetFocus(hwnd);					//sends WM_SETFOCUS

	//game loop
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == TRUE)
			{
				//render the scene
				display();

				//update the scene
				update();
			}
		}
	}

	uninitialize();

	return((int)msg.wParam);
}

//callback func definition
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local func decl.
	void ToggleFullScreen(void);
	void resize(int, int);

	//local var decl.

	
	//code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = FALSE;
		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_CHAR:
		switch (wParam)
		{
		case 'F':
		case 'f':
			ToggleFullScreen();
			break;

		case 'D':
			day = (day + 6) % 360;
			break;

		case 'd':
			day = (day - 6) % 360;
			break;

		case 'Y':
			year = (year + 3) % 360;
			break;

		case 'y':
			year = (year - 3) % 360;
			break;

		case 'M':
			moon_revolve = (moon_revolve + 3) % 360;
			break;

		case 'm':
			moon_revolve = (moon_revolve - 3) % 360;
			break;

		case 'N':
			moon_spin = (moon_spin + 3) % 360;
			break;

		case 'n':
			moon_spin = (moon_spin - 3) % 360;
			break;

		case 'Q':
			satellite_revolve = (satellite_revolve + 3) % 360;
			break;

		case 'q':
			satellite_revolve = (satellite_revolve - 3) % 360;
			break;

		case 'W':
			satellite_spin = (satellite_spin + 3) % 360;
			break;

		case 'w':
			satellite_spin = (satellite_spin - 3) % 360;
			break;

		default:
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 27:
			DestroyWindow(hwnd);
			break;

		default:
			break;
		}
		break;

	case WM_SIZE:	//WM_SIZE comes as soon as a window is resized & hence handling it
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE:	//this comes when window is closed, WM_CLOSE comes just before WM_DESTROY
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	//local var decl.
	static DWORD dwStyle;   //static to sustain values across different func calls
	static WINDOWPLACEMENT wp;
	MONITORINFO mi;
	//static BOOL bFullScreen = FALSE; OR bFullScreen = gbFullScreen; also works

	//code
	wp.length = sizeof(WINDOWPLACEMENT);

	if (gbFullScreen == FALSE)  //bFullScreen also works
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi.cbSize = sizeof(MONITORINFO);


			if (GetWindowPlacement(ghwnd, &wp) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);    //framechanged internally send WM_NCCALCSIZE
			}
			ShowCursor(FALSE);
			gbFullScreen = TRUE;
		}
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wp);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);     //0, 0, 0, 0 because everything is given in wp


		ShowCursor(TRUE);
		gbFullScreen = FALSE;
	}
}

int initialize(void)
{
	//function declarations
	void resize(int, int);
	
	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	//code
	//zeroing/initializing all member of pfd to 0
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//initializing pfd struct
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;	//24 bits can also be used

	//get Device Context
	ghdc = GetDC(ghwnd);

	//choose pixel format
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		return(-1);
	}

	//set the choosen pixel format
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
		return(-2);

	//create OpenGL rendering context
	ghrc = wglCreateContext(ghdc);				//calling first Windows Bridging API
	if (ghrc == NULL)
		return(-3);

	//make the rendering context as the current context
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
		return(-4);

	//here starts OpenGL code
	//clear the screen using blue color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		//above 3 lines are must, below 2 lines are optional
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//create quadric (the bowl)
	quadric = gluNewQuadric();
	
	//warm up resize call
	//without this maroon or brownish window comes first
	resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);
	//16 is border size 8-8 right & left size
	//39 is 8 top border, 23 menu bar, 8 bottom border of window
	//all funcs give window size including its border

	return(0);
}

void resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls

	glViewport(0, 0, GLsizei(width), GLsizei(height));

	//Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//first view/camera transformation
	//changing only eye coordinates to get better view
	gluLookAt(0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//now at this moment CTM is with all the changes made above in modelview matrix (MVM)
	//in order to come back to this CTM, save it by pushing it on MVM stack
	glPushMatrix();		//pushes CTM on MVM stack : State-1

	//Redbook approach :
	//when you push a CTM on MVM or Projection matrix stack, a copy of CTM is created & then pushed on the respective matrix
	//if glRotate(), glTranslate, glScale() are used then stack is of MVM
	//if glOrtho(), glFrustum or gluPerspective() are used then stack is of Projection matrix
	//OpenGL specification approach : read book notes from 4 Apr 2022, Day - 54

	//beautification - 1
	glRotatef(90.f, 1.0f, 0.0f, 0.0f);		//this is for Sun, we write here but in anyway Sun doesn't rotate

	//beautification - 2
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//beautification - 3
	glColor3f(1.0f, 1.0f, 0.0f);	//yellow for sun

	//drawing the sphere for Sun
	gluSphere(quadric, 0.75, 30, 30);		//parameters - bowl to draw in, radius, no of vertical slices, no of horizontal stacks

	//the CTM State - 1 was changed with all the modifications done above & we have drawn what we wanted at this new CTM
	//but now we want to go back to previous saved CTM that had State - 1 which was without all above modifications
	//& start drawing from that CTM point/state so we pop the saved CTM State - 1 stack frame from MVM stack
	glPopMatrix();		//pops the saved CTM State-1 & makes it as new CTM
	//For glPopMatrix
	//Redbook approach : CTM is detroyed & popped matrix becomes the new CTM
	//OpenGL specification approach : read book notes from 4 Apr 2022, Day - 54 

//Earth related code starts from here
	
	//saving CTM here for no reason or as discipline
	glPushMatrix();		//pushes CTM on MVM stack : State-2

	//rotation around sun i.e Revolution Rotation
	glRotatef((GLfloat)year, 0.0f, 1.0f, 0.0f);
	//without enabling depth test earth will always draw over sun

	//doing translation for earth
	glTranslatef(1.5f, 0.0f, 0.0f);

	//beautification - 4
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	glPushMatrix();		//saves & pushes CTM on MVM stack before earth spins around itself : State-3

	//rotation around itself i.e Spinning Rotation
	glRotatef((GLfloat)day, 0.0f, 0.0f, 1.0f);

	//now above we do 2 glRotatef() where 1 would've sufficed to solve a small issue with OGL sphere
	//the gluSphere() when creates a earth like sphere object 
	//1. its 'magnetic' poles are horizontal i.e north/south are in horizontal direction
	//2. since they are in horizontal line, as per OGL coordinate system they are on Z axis 
	
	//to solve the above issue, bring more realism & represent earth like object more accurately,
	//we with beaut-4 statement rotate sphere around x-axis by 90 degrees, so that its horizontal z-axis becomes & looks
	//like as if it is vertical y-axis, then with the next spinning statement we make the current vertical axis which is
	//z-axis now to spin by 'day' angle forcing it to behave as y-axis

	//instead of doing all this, try spinning it around y-axis & see what happens

	//beautification - 5
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 		//wireframe

	//beautification - 6
	glColor3f(0.4f, 0.9f, 1.0f);	//blue for earth

	//draw sphere for earth
	gluSphere(quadric, 0.2f, 20, 20);

//MOON related code starts from here
	glPopMatrix();		//restores & pops CTM on MVM stack of State-3 
	//so that moon is drawn on that CTM where earth was before its spinning around itself

	//rotation around earth i.e Revolution Rotation
	glRotatef((GLfloat)moon_revolve, 0.0f, 0.0f, 1.0f);
	//without enabling depth test earth will always draw over sun

	//doing translation for moon
	glTranslatef(0.5f, 0.0f, 0.0f);

	//rotation around itself i.e Spinning Rotation
	glRotatef((GLfloat)moon_spin, 0.0f, 0.0f, 1.0f);

	//beautification - 5
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 		//wireframe

	//beautification - 6
	glColor3f(1.0f, 1.0f, 1.0f);	//white for moon

	//draw sphere for earth
	gluSphere(quadric, 0.1f, 20, 20);

//drawing satellite around Moon
	//rotation around moon i.e Revolution Rotation
	glRotatef((GLfloat)satellite_revolve, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.5f, 0.0f, 0.0f);			//doing translation for moon	//above rotation & this translate cause revolution 

	//rotation around itself i.e Spinning Rotation
	glRotatef((GLfloat)satellite_spin, 0.0f, 1.0f, 0.0f);	//above translate & this rotation cause rotation
	
	glScalef(0.08f, 0.08f, 0.01f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 		//wireframe

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);	//red for satellite apex
	glVertex3f(0.0f, 3.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);	//green for base
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);	//blue for base
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	glPopMatrix(); 	//pops the saved CTM State-2 & makes it as new CTM

	SwapBuffers(ghdc);
}

void update(void)
{
	//code

}

void uninitialize(void)
{
	//function declarations
	void ToggleFullScreen(void);

	//code
	if (gbFullScreen)
	{
		ToggleFullScreen();		//window should not die in Fullscreen mode
	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (ghwnd)
	{
		DestroyWindow(ghwnd);	//we destroy here if in WinMain iRetVal = initialize(); fails, we can immediately call unintialize() there itself
		ghwnd = NULL;
	}

	if (quadric)
	{
		gluDeleteQuadric(quadric);
		fprintf(gpFile, "Quadric FREED successfully!\n");
		quadric = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "Window Log file CLOSED successfully!\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
