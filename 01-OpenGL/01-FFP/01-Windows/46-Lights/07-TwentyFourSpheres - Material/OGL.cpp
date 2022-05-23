//Date: 20/05/2022 - 21/05/2022
//RTR2021 OGL TwentyFour Spheres - Material

//home work : do this in perspective & push

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

GLUquadric *quadric = NULL;		//bowl to draw spheres into

//for lights
BOOL gbLight = FALSE;

GLfloat gfaLightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat gfaLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gfaLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gfaLightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };	//positional light

//lighting models
GLfloat gfaLight_Model_Ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat gfaLight_Model_Local_Viewer[] = { 0.0f };		//singled member array

GLfloat gfAngleForXRotation = 0.0f;
GLfloat gfAngleForYRotation = 0.0f;
GLfloat gfAngleForZRotation = 0.0f;

GLint giKeyPressed = 0;

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

		case 'L':
		case 'l':
		{
			if (gbLight == FALSE)
			{
				glEnable(GL_LIGHTING);
				gbLight = TRUE;
			}
			else
			{
				glDisable(GL_LIGHTING);
				gbLight = FALSE;
			}
		}
		break;

		case 'X':
		case 'x':
			giKeyPressed = 1;
			gfAngleForXRotation = 0.0f;		//reset
			break;

		case 'Y':
		case 'y':
			giKeyPressed = 2;
			gfAngleForYRotation = 0.0f;		//reset
			break;

		case 'Z':
		case 'z':
			giKeyPressed = 3;
			gfAngleForZRotation = 0.0f;		//reset
			break;

		default:
			giKeyPressed = 0;
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
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);	//RGBA

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		//above 3 lines are must, below 2 lines are optional
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//light related changes
	glEnable(GL_AUTO_NORMAL);	//to generate normals automatically
	glEnable(GL_NORMALIZE);		//normals drawn above must not get transformed by MVM, to avoid this we rescale the normal or normalize them here

	glLightfv(GL_LIGHT0, GL_AMBIENT, gfaLightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, gfaLightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, gfaLightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, gfaLightPosition);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gfaLight_Model_Ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, gfaLight_Model_Local_Viewer);
	glEnable(GL_LIGHT0);

	//create quadric (the bowl)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();		//create quadric in initialize() so that memory is allocated only once for it & free in uninitialize()
	
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
	
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);		//perspective viewing angle 45 degree
	//Orthographic Projection

//---------------------------------------------------------------------some mistake here
	if (width <= height)
	{
		glOrtho(0.0f,
			15.0f,
			(0.0f * ((GLfloat)height / (GLfloat)width)),
			(15.0f * ((GLfloat)height / (GLfloat)width)),
			-10.f,
			10.0f);
	}
	else
	{
		glOrtho((0.0f * ((GLfloat)width / (GLfloat)height)),
			(15.0f * ((GLfloat)width / (GLfloat)height)),
			0.0f,
			15.0f,
			-10.f,
			10.0f);
	}
}

void display(void)
{
	//func. decl.
	void DrawTwentyFourSpheres(void);
	
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (giKeyPressed == 1)
	{
		//x axis rotation
		glRotatef(gfAngleForXRotation, 1.0f, 0.0f, 0.0f);
		gfaLightPosition[2] = gfAngleForXRotation;
	}
	else if (giKeyPressed == 2)
	{
		//y axis rotation
		glRotatef(gfAngleForYRotation, 0.0f, 1.0f, 0.0f);
		gfaLightPosition[0] = gfAngleForYRotation;
	}
	else if (giKeyPressed == 3)
	{
		//z axis rotation
		glRotatef(gfAngleForZRotation, 0.0f, 0.0f, 1.0f);
		gfaLightPosition[1] = gfAngleForZRotation;
	}
	else
	{
		gfaLightPosition[0] = 0.0f;
		gfaLightPosition[1] = 0.0f;
		gfaLightPosition[2] = 0.0f;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, gfaLightPosition);

//-----------------------------------------------------------------------------same mistake here
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -4.0f);

	//drawing the sphere
	DrawTwentyFourSpheres();

	SwapBuffers(ghdc);
}

void update(void)
{
	//code

	//home work: use trignometric increment

	if (giKeyPressed == 1)
	{
		gfAngleForXRotation = gfAngleForXRotation + 1.0f;
		if (gfAngleForXRotation >= 360.f)
			gfAngleForXRotation = gfAngleForXRotation - 360.0f;
	}
	
	if (giKeyPressed == 2)
	{
		gfAngleForYRotation = gfAngleForYRotation + 1.0f;
		if (gfAngleForYRotation >= 360.f)
			gfAngleForYRotation = gfAngleForYRotation - 360.0f;
	}
	
	if (giKeyPressed == 3)
	{
		gfAngleForZRotation = gfAngleForZRotation + 1.0f;
		if (gfAngleForZRotation >= 360.f)
			gfAngleForZRotation = gfAngleForZRotation - 360.0f;
	}
}

void DrawTwentyFourSpheres(void)
{
	//local var decl.
	GLfloat faMaterialAmbient[4];
	GLfloat faMaterialDiffuse[4];
	GLfloat faMaterialSpecular[4];
	GLfloat fMaterialShininess;

	//code
	//Mark Kilgard's materials.c program for sphere materials
 
	// ***** 1st sphere on 1st column, emerald - paachu budhacha *****
	// ambient material
	faMaterialAmbient[0] = 0.0215; // r
	faMaterialAmbient[1] = 0.1745; // g
	faMaterialAmbient[2] = 0.0215; // b
	faMaterialAmbient[3] = 1.0f;   // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.07568; // r
	faMaterialDiffuse[1] = 0.61424; // g
	faMaterialDiffuse[2] = 0.07568; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.633;    // r
	faMaterialSpecular[1] = 0.727811; // g
	faMaterialSpecular[2] = 0.633;    // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.6 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 2nd sphere on 1st column, jade - hirva kirtikhada *****
	// ambient material
	faMaterialAmbient[0] = 0.135;  // r
	faMaterialAmbient[1] = 0.2225; // g
	faMaterialAmbient[2] = 0.1575; // b
	faMaterialAmbient[3] = 1.0f;   // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.54; // r
	faMaterialDiffuse[1] = 0.89; // g
	faMaterialDiffuse[2] = 0.63; // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.316228; // r
	faMaterialSpecular[1] = 0.316228; // g
	faMaterialSpecular[2] = 0.316228; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.1 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 3rd sphere on 1st column, obsidian/blue sapphire - nilmani shanicha *****
	// ambient material
	faMaterialAmbient[0] = 0.05375; // r
	faMaterialAmbient[1] = 0.05;    // g
	faMaterialAmbient[2] = 0.06625; // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.18275; // r
	faMaterialDiffuse[1] = 0.17;    // g
	faMaterialDiffuse[2] = 0.22525; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.332741; // r
	faMaterialSpecular[1] = 0.328634; // g
	faMaterialSpecular[2] = 0.346435; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.3 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 9.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 4th sphere on 1st column, pearl - moti chandracha khadaa *****
	// ambient material
	faMaterialAmbient[0] = 0.25;    // r
	faMaterialAmbient[1] = 0.20725; // g
	faMaterialAmbient[2] = 0.20725; // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 1.0;   // r
	faMaterialDiffuse[1] = 0.829; // g
	faMaterialDiffuse[2] = 0.829; // b
	faMaterialDiffuse[3] = 1.0f;  // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.296648; // r
	faMaterialSpecular[1] = 0.296648; // g
	faMaterialSpecular[2] = 0.296648; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.088 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 6.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 5th sphere on 1st column, ruby - maanik ravi khadaa *****
	// ambient material
	faMaterialAmbient[0] = 0.1745;  // r
	faMaterialAmbient[1] = 0.01175; // g
	faMaterialAmbient[2] = 0.01175; // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.61424; // r
	faMaterialDiffuse[1] = 0.04136; // g
	faMaterialDiffuse[2] = 0.04136; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.727811; // r
	faMaterialSpecular[1] = 0.626959; // g
	faMaterialSpecular[2] = 0.626959; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.6 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 4.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 6th sphere on 1st column, turquoise - jwalamukhicha khadaa *****
	// ambient material
	faMaterialAmbient[0] = 0.1;     // r
	faMaterialAmbient[1] = 0.18725; // g
	faMaterialAmbient[2] = 0.1745;  // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.396;   // r
	faMaterialDiffuse[1] = 0.74151; // g
	faMaterialDiffuse[2] = 0.69102; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.297254; // r
	faMaterialSpecular[1] = 0.30829;  // g
	faMaterialSpecular[2] = 0.306678; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.1 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f, 1.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************
	// *******************************************************
	// *******************************************************

	// ***** 1st sphere on 2nd column, brass *****
	// ambient material
	faMaterialAmbient[0] = 0.329412; // r
	faMaterialAmbient[1] = 0.223529; // g
	faMaterialAmbient[2] = 0.027451; // b
	faMaterialAmbient[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.780392; // r
	faMaterialDiffuse[1] = 0.568627; // g
	faMaterialDiffuse[2] = 0.113725; // b
	faMaterialDiffuse[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.992157; // r
	faMaterialSpecular[1] = 0.941176; // g
	faMaterialSpecular[2] = 0.807843; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.21794872 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 2nd sphere on 2nd column, bronze *****
	// ambient material
	faMaterialAmbient[0] = 0.2125; // r
	faMaterialAmbient[1] = 0.1275; // g
	faMaterialAmbient[2] = 0.054;  // b
	faMaterialAmbient[3] = 1.0f;   // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.714;   // r
	faMaterialDiffuse[1] = 0.4284;  // g
	faMaterialDiffuse[2] = 0.18144; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.393548; // r
	faMaterialSpecular[1] = 0.271906; // g
	faMaterialSpecular[2] = 0.166721; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.2 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 3rd sphere on 2nd column, chrome *****
	// ambient material
	faMaterialAmbient[0] = 0.25; // r
	faMaterialAmbient[1] = 0.25; // g
	faMaterialAmbient[2] = 0.25; // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.4;  // r
	faMaterialDiffuse[1] = 0.4;  // g
	faMaterialDiffuse[2] = 0.4;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.774597; // r
	faMaterialSpecular[1] = 0.774597; // g
	faMaterialSpecular[2] = 0.774597; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.6 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 9.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 4th sphere on 2nd column, copper *****
	// ambient material
	faMaterialAmbient[0] = 0.19125; // r
	faMaterialAmbient[1] = 0.0735;  // g
	faMaterialAmbient[2] = 0.0225;  // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.7038;  // r
	faMaterialDiffuse[1] = 0.27048; // g
	faMaterialDiffuse[2] = 0.0828;  // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.256777; // r
	faMaterialSpecular[1] = 0.137622; // g
	faMaterialSpecular[2] = 0.086014; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.1 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 6.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 5th sphere on 2nd column, gold *****
	// ambient material
	faMaterialAmbient[0] = 0.24725; // r
	faMaterialAmbient[1] = 0.1995;  // g
	faMaterialAmbient[2] = 0.0745;  // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.75164; // r
	faMaterialDiffuse[1] = 0.60648; // g
	faMaterialDiffuse[2] = 0.22648; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.628281; // r
	faMaterialSpecular[1] = 0.555802; // g
	faMaterialSpecular[2] = 0.366065; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.4 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 4.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 6th sphere on 2nd column, silver *****
	// ambient material
	faMaterialAmbient[0] = 0.19225; // r
	faMaterialAmbient[1] = 0.19225; // g
	faMaterialAmbient[2] = 0.19225; // b
	faMaterialAmbient[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.50754; // r
	faMaterialDiffuse[1] = 0.50754; // g
	faMaterialDiffuse[2] = 0.50754; // b
	faMaterialDiffuse[3] = 1.0f;    // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.508273; // r
	faMaterialSpecular[1] = 0.508273; // g
	faMaterialSpecular[2] = 0.508273; // b
	faMaterialSpecular[3] = 1.0f;     // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.4 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.5f, 1.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************
	// *******************************************************
	// *******************************************************

	// ***** 1st sphere on 3rd column, black *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.0;  // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.01; // r
	faMaterialDiffuse[1] = 0.01; // g
	faMaterialDiffuse[2] = 0.01; // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.50; // r
	faMaterialSpecular[1] = 0.50; // g
	faMaterialSpecular[2] = 0.50; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.25 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 2nd sphere on 3rd column, cyan *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.1;  // g
	faMaterialAmbient[2] = 0.06; // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.0;        // r
	faMaterialDiffuse[1] = 0.50980392; // g
	faMaterialDiffuse[2] = 0.50980392; // b
	faMaterialDiffuse[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.50196078; // r
	faMaterialSpecular[1] = 0.50196078; // g
	faMaterialSpecular[2] = 0.50196078; // b
	faMaterialSpecular[3] = 1.0f;       // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.25 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 3rd sphere on 3rd column, green *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.0;  // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.1;  // r
	faMaterialDiffuse[1] = 0.35; // g
	faMaterialDiffuse[2] = 0.1;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.45; // r
	faMaterialSpecular[1] = 0.55; // g
	faMaterialSpecular[2] = 0.45; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.25 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 9.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 4th sphere on 3rd column, red *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.0;  // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.5;  // r
	faMaterialDiffuse[1] = 0.0;  // g
	faMaterialDiffuse[2] = 0.0;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.7;  // r
	faMaterialSpecular[1] = 0.6;  // g
	faMaterialSpecular[2] = 0.6;  // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.25 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 6.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 5th sphere on 3rd column, white *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.0;  // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.55; // r
	faMaterialDiffuse[1] = 0.55; // g
	faMaterialDiffuse[2] = 0.55; // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.70; // r
	faMaterialSpecular[1] = 0.70; // g
	faMaterialSpecular[2] = 0.70; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.25 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 4.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 6th sphere on 3rd column, yellow plastic *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.0;  // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.5;  // r
	faMaterialDiffuse[1] = 0.5;  // g
	faMaterialDiffuse[2] = 0.0;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.60; // r
	faMaterialSpecular[1] = 0.60; // g
	faMaterialSpecular[2] = 0.50; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.25 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(13.5f, 1.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************
	// *******************************************************
	// *******************************************************

	// ***** 1st sphere on 4th column, black *****
	// ambient material
	faMaterialAmbient[0] = 0.02; // r
	faMaterialAmbient[1] = 0.02; // g
	faMaterialAmbient[2] = 0.02; // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.01; // r
	faMaterialDiffuse[1] = 0.01; // g
	faMaterialDiffuse[2] = 0.01; // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.4;  // r
	faMaterialSpecular[1] = 0.4;  // g
	faMaterialSpecular[2] = 0.4;  // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.078125 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 14.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 2nd sphere on 4th column, cyan *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.05; // g
	faMaterialAmbient[2] = 0.05; // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.4;  // r
	faMaterialDiffuse[1] = 0.5;  // g
	faMaterialDiffuse[2] = 0.5;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.04; // r
	faMaterialSpecular[1] = 0.7;  // g
	faMaterialSpecular[2] = 0.7;  // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.078125 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 3rd sphere on 4th column, green *****
	// ambient material
	faMaterialAmbient[0] = 0.0;  // r
	faMaterialAmbient[1] = 0.05; // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.4;  // r
	faMaterialDiffuse[1] = 0.5;  // g
	faMaterialDiffuse[2] = 0.4;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.04; // r
	faMaterialSpecular[1] = 0.7;  // g
	faMaterialSpecular[2] = 0.04; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.078125 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 9.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 4th sphere on 4th column, red *****
	// ambient material
	faMaterialAmbient[0] = 0.05; // r
	faMaterialAmbient[1] = 0.0;  // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.5;  // r
	faMaterialDiffuse[1] = 0.4;  // g
	faMaterialDiffuse[2] = 0.4;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.7;  // r
	faMaterialSpecular[1] = 0.04; // g
	faMaterialSpecular[2] = 0.04; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.078125 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 6.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 5th sphere on 4th column, white *****
	// ambient material
	faMaterialAmbient[0] = 0.05; // r
	faMaterialAmbient[1] = 0.05; // g
	faMaterialAmbient[2] = 0.05; // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.5;  // r
	faMaterialDiffuse[1] = 0.5;  // g
	faMaterialDiffuse[2] = 0.5;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.7;  // r
	faMaterialSpecular[1] = 0.7;  // g
	faMaterialSpecular[2] = 0.7;  // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.078125 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 4.0f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************

	// ***** 6th sphere on 4th column, yellow rubber *****
	// ambient material
	faMaterialAmbient[0] = 0.05; // r
	faMaterialAmbient[1] = 0.05; // g
	faMaterialAmbient[2] = 0.0;  // b
	faMaterialAmbient[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_AMBIENT, faMaterialAmbient);

	// diffuse material
	faMaterialDiffuse[0] = 0.5;  // r
	faMaterialDiffuse[1] = 0.5;  // g
	faMaterialDiffuse[2] = 0.4;  // b
	faMaterialDiffuse[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_DIFFUSE, faMaterialDiffuse);

	// specular material
	faMaterialSpecular[0] = 0.7;  // r
	faMaterialSpecular[1] = 0.7;  // g
	faMaterialSpecular[2] = 0.04; // b
	faMaterialSpecular[3] = 1.0f; // a
	glMaterialfv(GL_FRONT, GL_SPECULAR, faMaterialSpecular);

	// shininess
	fMaterialShininess = 0.078125 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, fMaterialShininess);

	// geometry
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(19.5f, 1.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	// *******************************************************
	// *******************************************************
	// *******************************************************
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
		fprintf(gpFile, "Quadric FREED successfully!\n");
		gluDeleteQuadric(quadric);
		quadric = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "Window Log file CLOSED successfully!\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
