//Date: 10/04/2022
//RTR2021 OGL India Dynamic with audio

#define _USE_MATH_DEFINES 1

//header files
#include <windows.h>
#include <stdio.h>			//for file I/O functions
#include <stdlib.h>			//for exit()
#include "OGL.h"			//for icon
#include <GL/glu.h>
#include <math.h>			//for PI, sin, cos

//OpenGL header files
#include <GL/gl.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 700

//OpenGL libraries
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")			//for audio file

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

int cxWindowWidth = 1200;
int cyWindowHeight = 700;

//for active window
BOOL gbActiveWindow = FALSE;

//for file I/O
FILE* gpFile = NULL;

//for moving letters
GLfloat gfMoveI_x = -30.0f;
GLfloat gfMoveI_y = 0.0f;

GLfloat gfMoveN_y = 20.0f;

GLfloat gfMoveD_z = -90.0f;

GLfloat gfMoveI2_y = -20.0f;

GLfloat gfMoveA_x = 30.0f;

//for moving planes
GLfloat gfMovePlaneMiddle_x = -20.0f;
GLfloat gfMovePlaneMiddle_y = 0.0f;

GLfloat gfMovePlaneUpper_x = -10.0f;
GLfloat gfMovePlaneUpper_y = 10.0f;

GLfloat gfMovePlaneLower_x = -10.0f;
GLfloat gfMovePlaneLower_y = -10.0f;

GLfloat gfAnglePlaneUpper = 60.0f;
GLfloat gfAnglePlaneLower = 0.0f;

//flags
BOOL gbFlag_I = TRUE;
BOOL gbFlag_N = FALSE;
BOOL gbFlag_D = FALSE;
BOOL gbFlag_I2 = FALSE;
BOOL gbFlag_A = FALSE;
BOOL gbFlag_Planes = FALSE;

//for fading effect of D
GLfloat gfAlpha = 0.0f;

GLfloat gfSaffColor_R = -1.0f;
GLfloat gfSaffColor_G = -1.0f;
GLfloat gfSaffColor_B = -1.0f;

GLfloat gfWhiteColor_R = -1.0f;
GLfloat gfWhiteColor_G = -1.0f;
GLfloat gfWhiteColor_B = -1.0f;

GLfloat gfGreenColor_R = -1.0f;
GLfloat gfGreenColor_G = -1.0f;
GLfloat gfGreenColor_B = -1.0f;

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
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
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
	pfd.cDepthBits = 32;

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
	
	//depth related
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//for alpha in glColor4f()
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);

	//warm up resize call
	//without this maroon or brownish window comes first
	resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);
	//16 is border size 8-8 right & left size
	//39 is 8 top border, 23 menu bar, 8 bottom border of window
	//all funcs give window size including its border

	//ToggleFullScreen();	//to start program in fullscreen

	//start song
	PlaySound(TEXT("audiofile.wav"), GetModuleHandle(NULL), SND_ASYNC | SND_NODEFAULT);

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
	//func decl.
	void amp_I();
	void amp_N();
	void amp_D();
	void amp_A();
	void amp_M();
	void amp_P();
	void amp_PlaneMiddle(GLfloat smokeArray[3]);

	//local var decl.
	GLfloat array_saffron[] = {1.0, 0.60, 0.20}; 	//saffron
	GLfloat array_white[] = {1.0, 1.0, 1.0}; 		//white
	GLfloat array_green[] = {0.19, 0.9, 0.08}; 		//green

	//code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	if(gbFlag_I == TRUE)
	{
		glLoadIdentity();
		glTranslatef(gfMoveI_x, gfMoveI_y, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_I();
	}
	

	if(gbFlag_N == TRUE)
	{
		glLoadIdentity();
		glTranslatef(-6.0, gfMoveN_y, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_N();
	}
	
	if(gbFlag_D == TRUE)
	{
		glLoadIdentity();
		glTranslatef(-0.0f, 0.0f, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_D();
	}
	
	if(gbFlag_I2 == TRUE)
	{
		glLoadIdentity();
		glTranslatef(5.1f, gfMoveI2_y, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_I();
	}
	
	if(gbFlag_A == TRUE)
	{
		glLoadIdentity();
		glTranslatef(gfMoveA_x, 0.0f, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_A();
	}
	
	if(gbFlag_Planes == TRUE)
	{
		//MIDDLE PLANE
		{
			glLoadIdentity();
			glTranslatef(-5.0f, 0.0f, 0.0f);
			glTranslatef(gfMovePlaneMiddle_x, 0.0f, -26.0f);
			amp_PlaneMiddle(array_white);
		}	
		
		//Translate to desired position (e.g right side x+)
		//Translate down
		//Rotate in position to desired angle
		//Translate back to desired postion (e.g left side x-)

		//UPPER PLANE
		if(gfMovePlaneMiddle_x > 17.0f)
		{
			glLoadIdentity();
			glTranslatef(-5.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.3f, 0.0f);
			glTranslatef(gfMovePlaneUpper_x, 0.0f, -26.0f);
			glRotatef(-gfAnglePlaneUpper, 0.0f, 0.f, -1.0f);
			glTranslatef(gfMovePlaneUpper_x - 0.004, 0.0f, 0.0f);
			amp_PlaneMiddle(array_saffron);
		}
		else
		{
			glLoadIdentity();
			glTranslatef(-5.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.3f, 0.0f);
			glTranslatef(gfMovePlaneUpper_x, 0.0f, -26.0f);
			glRotatef(gfAnglePlaneUpper, 0.0f, 0.f, -1.0f);
			glTranslatef(gfMovePlaneUpper_x - 0.004, 0.0f, 0.0f);
			amp_PlaneMiddle(array_saffron);
		}
		
		//LOWER PLANE
		if(gfMovePlaneMiddle_x > 17.0f)
		{
			glLoadIdentity();
			glTranslatef(-5.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -0.3f, 0.0f);
			glTranslatef(gfMovePlaneLower_x, 0.0f, -26.0f);
			glRotatef(gfAnglePlaneUpper, 0.0f, 0.f, -1.0f);
			glTranslatef(gfMovePlaneLower_x - 0.004, 0.0f, 0.0f);
			amp_PlaneMiddle(array_green);
		}
		else
		{
			glLoadIdentity();
			glTranslatef(-5.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -0.3f, 0.0f);
			glTranslatef(gfMovePlaneLower_x, 0.0f, -26.0f);
			glRotatef(-gfAnglePlaneUpper, 0.0f, 0.f, -1.0f);
			glTranslatef(gfMovePlaneLower_x - 0.004, 0.0f, 0.0f);
			amp_PlaneMiddle(array_green);
		}

		if(gfMovePlaneMiddle_x > 14.0f)
		{
			glLoadIdentity();
			glTranslatef(11.37f, 0.0f, -29.0f);
			glRotatef(90.0f, 0.0f, 0.f, -1.0f);
			
			glBegin(GL_QUADS);
			glColor3fv(array_saffron);
			glVertex3f(-0.10f, -0.1f, 0.f);
			glVertex3f(0.10f, -0.1f, 0.f);
			glVertex3f(0.10f, -1.7f, 0.f);
			glVertex3f(-0.10f, -1.7f, 0.f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3fv(array_white);
			glVertex3f(0.10f, -0.1f, 0.f);
			glVertex3f(0.30f, -0.1f, 0.f);
			glVertex3f(0.30f, -1.7f, 0.f);
			glVertex3f(0.10f, -1.7f, 0.f);
			glEnd();

			glBegin(GL_QUADS);
			glColor3fv(array_green);
			glVertex3f(0.30f, -0.1f, 0.f);
			glVertex3f(0.50f, -0.1f, 0.f);
			glVertex3f(0.50f, -1.7f, 0.f);
			glVertex3f(0.30f, -1.7f, 0.f);
			glEnd();
		}

	}
	
	SwapBuffers(ghdc);
}

void update(void)
{
	//code
	//translating letter I from left side of screen
	if(gbFlag_I == TRUE)
	{
		gfMoveI_x = gfMoveI_x + 0.002f;
		if(gfMoveI_x >= -11.0f)
		{
			gfMoveI_x = -11.0f;
			gbFlag_N = TRUE;
		}
	}

	//translating letter N from top side of screen
	if(gbFlag_N)
	{
		gfMoveN_y = gfMoveN_y - 0.002f;
		if(gfMoveN_y <= 0.0f)
		{
			gfMoveN_y = 0.0f;
			gbFlag_D = TRUE;
		}
			
	}
	
	//translating letter D from inside out of screen
	if(gbFlag_D == TRUE)
	{
		gfMoveD_z = gfMoveD_z + 0.008f;
		if(gfMoveD_z >= -28.0f)
		{
			gfMoveD_z = -28.0f;
			gbFlag_I2 = TRUE;
		}

		//1.0, 0.60, 0.20
		gfSaffColor_R = gfSaffColor_R + 0.0002;
		if(gfSaffColor_R >= 1.0f)
		{
			gfSaffColor_R = 1.0f;
		}
		gfSaffColor_G = gfSaffColor_G + 0.0002;
		if(gfSaffColor_G >= 0.60f)
		{
			gfSaffColor_G = 0.60f;
		}
		gfSaffColor_B = gfSaffColor_B + 0.0002;
		if(gfSaffColor_B >= 0.20f)
		{
			gfSaffColor_B = 0.20f;
		}

		//1.0, 1.0, 1.0
		gfWhiteColor_R = gfWhiteColor_R + 0.0002;
		if(gfWhiteColor_R >= 1.0f)
		{
			gfWhiteColor_R = 1.0f;
		}
		gfWhiteColor_G = gfWhiteColor_G + 0.0002;
		if(gfWhiteColor_G >= 1.0f)
		{
			gfWhiteColor_G = 1.0f;
		}
		gfWhiteColor_B = gfWhiteColor_B + 0.0002;
		if(gfWhiteColor_B >= 1.0f)
		{
			gfWhiteColor_B = 1.0f;
		}

		//0.19, 0.9, 0.08
		gfGreenColor_R = gfGreenColor_R + 0.0002;
		if(gfGreenColor_R >= 0.19f)
		{
			gfGreenColor_R = 0.19f;
		}
		gfGreenColor_G = gfGreenColor_G + 0.0002;
		if(gfGreenColor_G >= 0.9f)
		{
			gfGreenColor_G = 0.9f;
		}
		gfGreenColor_B = gfGreenColor_B + 0.0002;
		if(gfGreenColor_B >= 0.08f)
		{
			gfGreenColor_B = 0.08f;
		}
	}
	

	//translating letter N2 from bottom side of screen
	if(gbFlag_I2 == TRUE)
	{
		gfMoveI2_y = gfMoveI2_y + 0.002f;
		if(gfMoveI2_y >= 0.0f)
		{
			gfMoveI2_y = 0.0f;
			gbFlag_A = TRUE;
		}
			
	}

	//translating letter A from right side of screen
	if(gbFlag_A == TRUE)
	{
		gfMoveA_x = gfMoveA_x - 0.002f;
		if(gfMoveA_x <= 10.0f)
		{
			gfMoveA_x = 10.0f;
			gbFlag_Planes = TRUE;
		}
	}
	
	if(gbFlag_Planes == TRUE)
	{
		//moving plane in middle straight towards middle
		gfMovePlaneMiddle_x = gfMovePlaneMiddle_x + 0.002f;
		gfMovePlaneMiddle_y = gfMovePlaneMiddle_y + 0.002f;

		//translating plane from upper corner
		gfMovePlaneUpper_x = gfMovePlaneUpper_x + 0.001f;
		gfMovePlaneUpper_y = gfMovePlaneUpper_y - 0.002f;

		//translating plane from bottom corner towards middle
		gfMovePlaneLower_x = gfMovePlaneLower_x + 0.001f;
		gfMovePlaneLower_y = gfMovePlaneLower_y + 0.002f;

		//rotating planes
		if(gfMovePlaneMiddle_x > 17.0f)
		{
			gfAnglePlaneUpper = gfAnglePlaneUpper + 0.007f;
			if(gfAnglePlaneUpper > 60.0f)
			{
				gfAnglePlaneUpper = 0.0f;
			}
		}
		else
		{
			gfAnglePlaneUpper = gfAnglePlaneUpper - 0.010f;
		}

		if(gfAnglePlaneUpper < 0.0f)
		{
			gfAnglePlaneUpper = 0.0f;
		}
	}
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

	if (gpFile)
	{
		fprintf(gpFile, "Window Log file CLOSED successfully!\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

//func definition
void amp_I()
{
//vertical line of I 
	//top quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(0.2f, 1.0f, 0.f);
	glVertex3f(-0.2f, 1.0f, 0.f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(0.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.2f, 0.0f, 0.f);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(-0.2f, -1.0f, 0.f);
	glVertex3f(0.2f, -1.0f, 0.f);
	glEnd();

//upper horizontal line of I
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(.9f, 1.3f, 0.f);
	glVertex3f(-.9f, 1.3, 0.f);
	glVertex3f(-.9f, 1.0f, 0.f);
	glVertex3f(.9f, 1.0f, 0.f);
	glEnd();

//lower horizontal line of I
	glBegin(GL_QUADS);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(.9f, -1.3f, 0.f);
	glVertex3f(-.9f, -1.3f, 0.f);
	glVertex3f(-.9f, -1.0f, 0.f);
	glVertex3f(.9f, -1.0f, 0.f);
	glEnd();
}

void amp_N()
{
//vertical left line of N
	//top quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle diagonal line of N
	//top quad
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.3f, 0.f, 0.f);
	glVertex3f(-0.1f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.3f, 0.f, 0.f);
	glVertex3f(-0.1f, 0.0f, 0.f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();

//vertical right line of N
	//top quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(1.2f, 1.3f, 0.f);
	glVertex3f(0.8f, 1.3f, 0.f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();
}

void amp_D()
{
//vertical left line of D 
	//top quad
	glBegin(GL_QUADS);
	glColor3f(gfSaffColor_R, gfSaffColor_G, gfSaffColor_B);			//saffron
	glVertex3f(-0.4f, 1.0f, 0.f);
	glVertex3f(-0.8f, 1.0f, 0.f);
	glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white
	glVertex3f(-0.8f, 0.0f, 0.f);
	glVertex3f(-0.4f, 0.0f, 0.f);
	glEnd();
	

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white
	glVertex3f(-0.4f, 0.0f, 0.f);
	glVertex3f(-0.8f, 0.0f, 0.f);
	glColor3f(gfGreenColor_R, gfGreenColor_G, gfGreenColor_B);			//india green
	glVertex3f(-0.8f, -1.0f, 0.f);
	glVertex3f(-0.4f, -1.0f, 0.f);
	glEnd();

//vertical right line of D 
	//top quad
	glBegin(GL_QUADS);
	glColor3f(gfSaffColor_R, gfSaffColor_G, gfSaffColor_B);				//saffron
	glVertex3f(1.0f, 1.0f, 0.f);
	glVertex3f(0.6f, 1.0f, 0.f);
	glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white	
	glVertex3f(0.6f, 0.0f, 0.f);
	glVertex3f(1.0f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white
	glVertex3f(0.6f, 0.0f, 0.f);
	glVertex3f(1.0f, 0.0f, 0.f);
	glColor3f(gfGreenColor_R, gfGreenColor_G, gfGreenColor_B);			//india green
	glVertex3f(1.0f, -1.0f, 0.f);
	glVertex3f(0.6f, -1.0f, 0.f);
	glEnd();

//upper horizontal line of D
	glBegin(GL_QUADS);
	glColor3f(gfSaffColor_R, gfSaffColor_G, gfSaffColor_B);			//saffron
	glVertex3f(1.0f, 1.3f, 0.f);
	glVertex3f(-1.1f, 1.3, 0.f);
	glVertex3f(-1.1f, 1.0f, 0.f);
	glVertex3f(1.0f, 1.0f, 0.f);
	glEnd();

//lower horizontal line of D
	glBegin(GL_QUADS);
	glColor3f(gfGreenColor_R, gfGreenColor_G, gfGreenColor_B);			//india green
	glVertex3f(1.0f, -1.3f, 0.f);
	glVertex3f(-1.1f, -1.3f, 0.f);
	glVertex3f(-1.1f, -1.0f, 0.f);
	glVertex3f(1.0f, -1.0f, 0.f);
	glEnd();
}

void amp_A()
{
//3rd quad Center line -
	/*glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.7f, -0.4f, 0.0f);
	glVertex3f(0.7f, -0.4f, 0.0f);
	glEnd();*/

//First quad /
	//top quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.2f, 1.3f, 0.0f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(-1.0f, -1.3f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glEnd();

//2nd quad \
	//top quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.2f, 1.3f, 0.0f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(1.0f, -1.3f, 0.0f);
	glVertex3f(0.6f, -1.3f, 0.0f);
	glEnd();
}

void amp_M()
{
//1st left most quad of M / 
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.50f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.75f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.75f, -1.0f, 0.0f);
	glEnd();

//2nd quad \ 
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.25f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.50f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glEnd();

//3rd quad / M
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.50f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.25f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glEnd();

//4th right most quad \ M 
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.50f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.75f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.75f, -1.0f, 0.0f);
	glEnd();

//trapezium on left top side
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.30f, 1.1f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.739f, 1.1f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.75f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.25f, 1.0f, 0.0f);
	glEnd();

//trapezium on right top side
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.30f, 1.1f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.739f, 1.1f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.75f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.25f, 1.0f, 0.0f);
	glEnd();

//trapezium on bottom center
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 0.4f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.15f, 0.2f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.15f, 0.2f, 0.0f);
	glEnd();
}

void amp_P()
{
//2nd right most quad of P half circle
	glPointSize(5.0f);
	glColor3f(1.0f, 0.843f, 0.0f);
	glBegin(GL_POLYGON);

	GLfloat radius = 0.4f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
	}

	glEnd();

//3rd right most quad small of P inner half circle
	glPointSize(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);

	radius = 0.3f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
	}

	glEnd();

//1st left most quad of P
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.2f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.2f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();
}

void amp_PlaneMiddle(GLfloat smokeArray[3])
{
	//local func decl.
	void amp_I();
	void amp_A();
	void amp_F();

	//code
	glRotatef(90.0, 0.0f, 0.f, -1.0f);

	glColor3f(0.55, 0.57, 0.67);	//gray

	//front triagnle
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.8f, 0.f);
	glVertex3f(-0.15f, 1.3f, 0.f);
	glVertex3f(0.15f, 1.3f, 0.f);
	glEnd();
	
	//front log quad
	glBegin(GL_QUADS);
	glVertex3f(0.15f, 1.3f, 0.f);
	glVertex3f(-0.15f, 1.3f, 0.f);
	glVertex3f(-0.15f, 0.8f, 0.f);
	glVertex3f(0.15f, 0.8f, 0.f);
	glEnd();
	
	//main body triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(1.0f, 0.0f, 0.f);
	glEnd();

	//backside trapezium
	glBegin(GL_QUADS);
	glVertex3f(0.3f, 0.0f, 0.f);
	glVertex3f(-0.3f, 0.0f, 0.f);
	glVertex3f(-0.5f, -0.3f, 0.f);
	glVertex3f(0.5f, -0.3f, 0.f);
	glEnd();

	//smoke
	glBegin(GL_QUADS);
	//glColor3f(1.0, 0.60, 0.20);			//saffron
	glColor3fv(smokeArray);
	glVertex3f(0.15f, -0.3, 0.f);
	glVertex3f(-0.15f, -0.3, 0.f);

	glColor3f(0.0f, 0.0, 0.0);			//black
	glVertex3f(-0.15f, -1.2f, 0.f);
	glVertex3f(0.15f, -1.2f, 0.f);
	glEnd();

	//drawing A inside triangle
	glScalef(0.15, 0.15, 0.0);
	glTranslatef(0.0, 1.88, 0.0);
	amp_A();

	//drawing I inside triangle
	glScalef(0.90, 0.90, 0.0);
	glTranslatef(-2.5, 0.0, 0.0);
	amp_I();

	//drawing F inside triangle
	//glScalef(0.90, 0.90, 0.0);
	glTranslatef(5.2, 0.0, 0.0);
	amp_I();
}
