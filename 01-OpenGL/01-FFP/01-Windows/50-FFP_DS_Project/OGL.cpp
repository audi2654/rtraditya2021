//Date: 22/10/2022
//RTR2021 OGL FFP Data Structure Project with Linked List
//Deva Tujhe Kiti Sundar Akash

//for math.h
#define _USE_MATH_DEFINES

//header files
#include <windows.h>
#include <stdio.h>			//for file I/O functions
#include <stdlib.h>			//for exit()
#include <math.h>			//for sine & cosine

//OpenGL header files
#include <GL/gl.h>
#include <GL/glu.h>
#include "amp_fonts.h"		//for letters
#include "OGL.h"			//for icon

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//OpenGL libraries
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")			//for audio resource & PlaySound() API

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

//scene flags to toggle
BOOL gbScene1 = FALSE;
BOOL gbScene2 = FALSE;
BOOL gbScene3 = FALSE;
BOOL gbScene4 = FALSE;
BOOL gbScene5 = FALSE;
BOOL gbScene6 = FALSE;
BOOL gbScene7 = FALSE;

//for scene translations
//for moving sky
GLfloat gfMoveSky_x = 7.0f;
GLfloat gfMoveSky_y = 0.0f;
GLfloat gfMoveSky2_x = 7.0f;
GLfloat gfMoveSky2_y = 0.0f;
GLfloat gfMoveSky3_x = 7.0f;
GLfloat gfMoveSky3_y = 0.0f;

//for sun sphere & moving sun
GLUquadric *quadric = NULL;		//bowl to draw speheres into
GLfloat gfMoveSun_y = 0.0f;
GLfloat gfMoveSun_z = -100.0f;
GLfloat gfRotateSun;

//for moon
GLfloat gfMoveMoon_y = 0.0f;
GLfloat gfMoveMoon_z = -50.0f;

//for texture variables
GLuint texture_pakhre;
GLuint texture_mule;

//to change sky color from day to night
GLfloat gfColorSky_b;

GLfloat gfaAddamp_backgroundColor[] = {204.0f/256.0f, 1.0f, 1.0f};

//for timer
GLfloat timer = 0.0f;

//linked list var
//Linked List functions
struct Node{
	void (* ptrToFunc)()= NULL;
	struct Node *next;
} *head = NULL; //global head

struct Node *nodePtr1 = NULL;		//decl ptr var nodePtr1 of type struct Node

void ll_addAtBegin(void (*)());
void ll_printNodes();

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
		TEXT("AMP OGL FFP DS Project - Deva Tujhe Kiti Sundar Akash"),
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
	else if (iRetVal == -5)
	{
		fprintf(gpFile, "LoadGlTexture for Pakhre FAILED\n");
		uninitialize();
	}
	else if (iRetVal == -6)
	{
		fprintf(gpFile, "LoadGlTexture for Mule FAILED\n");
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
	case WM_CREATE:
		//PlaySound(MAKEINTRESOURCE(AMP_MYAUDIO), NULL, SND_RESOURCE | SND_ASYNC | SND_NODEFAULT);
		break;

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
		case VK_SPACE:
		    PlaySound(MAKEINTRESOURCE(AMP_MYAUDIO), NULL, SND_RESOURCE | SND_ASYNC | SND_NODEFAULT);
			gbScene1 = TRUE;
			break;

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
	BOOL LoadGlTexture(GLuint*, TCHAR[]);
	
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

	//texture related code
	if(LoadGlTexture(&texture_pakhre, MAKEINTRESOURCE(IDBITMAP_PAKHRE)) == FALSE)
	{
		return -5;
	}

	if(LoadGlTexture(&texture_mule, MAKEINTRESOURCE(IDBITMAP_MULE)) == FALSE)
	{
		return -6;
	}

	//enabling the texture
	glEnable(GL_TEXTURE_2D);
	
	//warm up resize call
	//without this maroon or brownish window comes first
	resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);
	//16 is border size 8-8 right & left size
	//39 is 8 top border, 23 menu bar, 8 bottom border of window
	//all funcs give window size including its border

	ToggleFullScreen();

	//start song
	//PlaySound(TEXT("audiofile.wav"), GetModuleHandle(NULL), SND_ASYNC | SND_NODEFAULT);
	//see WM_CREATE to see PlaySound with audio resource

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
	//function declarations
	void amp_StartScene1();
	void amp_StartScene2();
	void amp_StartScene3();
	void amp_StartScene4();
	void amp_StartScene5();
	void amp_StartScene6();
	void amp_StartScene7();
	
	//local variable declarations
	

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	//main 
	//scene 1
	if(gbScene1 == TRUE)
	{
		amp_StartScene1();
	}	
	
	if(gbScene2 == TRUE)
		amp_StartScene2();

	if(gbScene3 == TRUE)
		amp_StartScene3();

	if(gbScene4 == TRUE)
		amp_StartScene4();
	
	if(gbScene5 == TRUE)
		amp_StartScene5();

	if(gbScene6 == TRUE)
		amp_StartScene6();

	if(gbScene7 == TRUE)
		amp_StartScene7();

	SwapBuffers(ghdc);
}

void update(void)
{
	//code
	//blue sky comes
	if(gbScene1 == TRUE)
	{
		gfMoveSky_x = gfMoveSky_x - 0.05f;
		if(gfMoveSky_x <= 0.0f)
		{
			gfMoveSky_x = 0.0f;
			gbScene2 = TRUE;
		}
	}

	//sun comes
	if(gbScene2 == TRUE)
	{
		/*gfMoveSun_y = gfMoveSun_y - 0.008f;
		if(gfMoveSun_y <= 0.0f)
		{
			gfMoveSun_y = 0.0f;
		}*/

		gfMoveSun_z = gfMoveSun_z + 0.6f;
		if(gfMoveSun_z >= -3.0f)
		{
			gfMoveSun_z = -3.0f;
			gbScene3 = TRUE;
		}

		/*gfRotateSun = gfRotateSun + 0.5f;
		if(gfRotateSun >= 360.0f)
		{
			gfRotateSun = 0.0f;
		}*/
	}
	
	//gray sky comes
	if(gbScene3 == TRUE)
	{
		gfMoveSky2_x = gfMoveSky2_x - 0.08f;
		if(gfMoveSky2_x <= 0.0f)
		{
			gfMoveSky2_x = 0.0f;
			gbScene4 = TRUE;
		}
	}

	//moon comes
	if(gbScene4 == TRUE)
	{
		gbScene2 = FALSE;
		gfMoveMoon_z = gfMoveMoon_z + 0.9f;
		if(gfMoveMoon_z >= -3.0f)
		{
			gfMoveMoon_z = -3.0f;
			gbScene5 = TRUE;
		}
	}

	//blue green screen with trees & birds come, texture_pakhre
	if(gbScene5 == TRUE)
	{
		//code
		gbScene1 = FALSE;
		gbScene2 = FALSE;
		gbScene3 = FALSE;
		gbScene4 = FALSE;

		gfMoveSky3_x = gfMoveSky3_x - 0.05f;
		if(gfMoveSky3_x <= 0.0f)
		{
			gfMoveSky3_x = 0.0f;
		}

		timer = timer + 0.01f;
		if(timer >= 10.0f)
		{
			gbScene6 = TRUE;
			timer = 0.0f;
		}
	}

	//blue green screen with trees & birds come
	if(gbScene6 == TRUE)
	{
		//code
		gbScene1 = FALSE;
		gbScene2 = FALSE;
		gbScene3 = FALSE;
		gbScene4 = FALSE;
		gbScene5 = FALSE;

		gfMoveSky3_x = gfMoveSky3_x - 0.05f;
		if(gfMoveSky3_x <= 0.0f)
		{
			gfMoveSky3_x = 0.0f;
		}

		timer = timer + 0.01f;
		if(timer >= 5.0f)
		{
			gbScene7 = TRUE;
			timer = 0.0f;
		}
	}

	if(gbScene7 == TRUE)
	{
		//code
		gbScene1 = FALSE;
		gbScene2 = FALSE;
		gbScene3 = FALSE;
		gbScene4 = FALSE;
		gbScene5 = FALSE;
		gbScene6 = FALSE;
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

	//linked list pointers
	free(head);

	//for texture variables
	if(texture_pakhre)
	{
		glDeleteTextures(1, &texture_pakhre);
		texture_pakhre = 0;
	}

	if(texture_mule)
	{
		glDeleteTextures(1, &texture_mule);
		texture_mule = 0;
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

//user defined function definitions
BOOL LoadGlTexture(GLuint* texture, TCHAR ImageResourceID[])
{
	//local var decl.
	HBITMAP hbitmap = NULL;
	BITMAP bmp;
	BOOL bResult = FALSE;

	//code
	hbitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), ImageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	//LR_CREATEDIBSECTION == returns a device independent bitmap section

	if(hbitmap)
	{
		bResult = TRUE;

		GetObject(hbitmap, sizeof(BITMAP), &bmp);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		//here we tell to unpack the pixels & arrange them in aligned manner of rows of 4 bits
		//4 types that is RGBA

		glGenTextures(1, texture);		//5th step

		glBindTexture(GL_TEXTURE_2D, *texture);		//6th step

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //7th step
		//when texture is near to viewer we tell OGL to draw it with magnified/maximum details

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //7th step
		//when texture is far from viewer we tell OGL to draw it with minimum details
		//for less load on OGL machine & increase performance

		//creating the actual texture
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		//not avaiable in OGL PP, wrapper function for glTextImage2D() & glGenerateMipMaps()

		glBindTexture(GL_TEXTURE_2D, 0);	//8th step

		DeleteObject(hbitmap);		//9th step
	}

	return(bResult);
}

void amp_background(GLfloat *color_array, GLfloat *color_array2, GLfloat bg_translate_x)
{
	glLoadIdentity();
	glTranslatef(bg_translate_x, 0.0f, -20.0f);
	glBegin(GL_QUADS);
	{
		glColor3fv(color_array);
		//glColor3f(0.0f, 0.5f, 0.8f); 				//azure blue for sky
		//glColor3f(204.0f/256.0f, 1.0f, 1.0f);
		glVertex3f(-15.0f, 9.0f, 0.0f);
		glVertex3f(-15.0f, -5.0f, 0.0f);
		glVertex3f(15.0f, -5.0f, 0.0f);
		glVertex3f(15.0f, 9.0f, 0.0f);

		glColor3fv(color_array2);		
		glVertex3f(-15.0f, -5.0f, 0.0f);
		glVertex3f(-15.0f, -11.0f, 0.0f);
		glVertex3f(15.0f, -11.0f, 0.0f);
		glVertex3f(15.0f, -5.0f, 0.0f);

	}
	glEnd();
}

void amp_StartScene1()
{
	//function declarations
	void amp_background(GLfloat *color_array, GLfloat *color_array2, GLfloat bg_translate_x);
	void amp_sky();
	void amp_sun();

	//code
	//amp_background(gfaColor_blue_azure, gfaColor_blue_azure, gfMoveSky_x);

	glLoadIdentity();
	
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();

	glTranslatef(gfMoveSky_x, gfMoveSky_y, 0.0f);
	amp_sky();
}

void amp_StartScene2()
{
	//function declarations
	void amp_background(GLfloat *color_array, GLfloat *color_array2, GLfloat bg_translate_x);
	void amp_sun();

	//code
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, gfMoveSun_z);
	amp_sun();
}

void amp_StartScene3()
{
	//function declarations
	void amp_background(GLfloat *color_array, GLfloat *color_array2, GLfloat bg_translate_x);
	void amp_sky2();

	//code
	//amp_background(gfaColor_black, gfaColor_black, gfMoveSky2_x);

	glLoadIdentity();
	
	/*glBegin(GL_QUADS);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();*/

	glTranslatef(gfMoveSky2_x, gfMoveSky2_y, 0.0f);
	amp_sky2();
}

void amp_StartScene4()
{
	//function declarations
	void amp_background(GLfloat *color_array, GLfloat *color_array2, GLfloat bg_translate_x);
	void amp_moon();

	//code
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, gfMoveMoon_z);
	amp_moon();
}

void amp_StartScene5()
{
	//func decl.
	void amp_cloudCircle();
	BOOL LoadGlTexture(GLuint*, TCHAR[]);

	//code
	//setting camera for the frame scene
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	//clouds from left side of screen
	//background
	/*glPushMatrix();
	{
		glTranslatef(gfMoveSky3_x, 0.0f, -15.0f);
		glBegin(GL_QUADS);
		{
			//glColor3fv(gfaColor_blue_aqua);
			glColor3f(0.47f, 0.71f, 1.0f); 				//french blue for sky
			//glColor3f(204.0f/256.0f, 1.0f, 1.0f);
			glVertex3f(-15.0f, 9.0f, 0.0f);
			glVertex3f(-15.0f, -5.0f, 0.0f);
			glVertex3f(15.0f, -5.0f, 0.0f);
			glVertex3f(15.0f, 9.0f, 0.0f);

			glColor3fv(gfaColor_green);		
			glVertex3f(-15.0f, -5.0f, 0.0f);
			glVertex3f(-15.0f, -11.0f, 0.0f);
			glVertex3f(15.0f, -11.0f, 0.0f);
			glVertex3f(15.0f, -5.0f, 0.0f);

			glColor3fv(gfaColor_white);
		}
		glEnd();
	}
	glPopMatrix();*/

	//background
	glPushMatrix();
	{
		amp_background(gfaColor_black, gfaColor_black, 0.0f);
	}
	glPopMatrix();

	glColor3fv(gfaColor_white);

	//cloud 1
	/*glPushMatrix();
	{
		glTranslatef(-6.0f + gfMoveSky_x, 3.5f, 0.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 2
	glPushMatrix();
	{
		glTranslatef(-4.5f + gfMoveSky_x, 1.4f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 3
	glPushMatrix();
	{
		glTranslatef(-2.5f + gfMoveSky_x, 2.8f, 2.0f);
		amp_cloudCircle();
	}
	glPopMatrix();*/

	//texture
	glPushMatrix();
	{
		//texture related code
		glBindTexture(GL_TEXTURE_2D, texture_pakhre);

		//full smiley face
		glTranslatef(0.0f, 0.0f, -5.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(11.0f, 6.2f, -5.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-11.0f, 6.2f, -5.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-11.0f, -6.2f, -5.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(11.0f, -6.2f, -5.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glPopMatrix();
	
}

void amp_StartScene6()
{
	//func decl.
	void amp_cloudCircle();
	BOOL LoadGlTexture(GLuint*, TCHAR[]);

	//code
	//setting camera for the frame scene
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	
	//background
	glPushMatrix();
	{
		amp_background(gfaColor_black, gfaColor_black, 0.0f);
	}
	glPopMatrix();

	glColor3fv(gfaColor_white);

	//texture
	glPushMatrix();
	{
		//texture related code
		glBindTexture(GL_TEXTURE_2D, texture_mule);

		//full smiley face
		glTranslatef(0.0f, 0.0f, -5.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(11.0f, 6.2f, -5.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-11.0f, 6.2f, -5.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-11.0f, -6.2f, -5.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(11.0f, -6.2f, -5.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glPopMatrix();
	
}

void amp_StartScene7()
{
	//func decl.
	void amp_CODED();
	void amp_WITH();
	void amp_LOVE();
	void amp_BY_ADITYA();

	//code
	ll_addAtBegin(amp_CODED);
	ll_addAtBegin(amp_WITH);
	ll_addAtBegin(amp_LOVE);
	ll_addAtBegin(amp_BY_ADITYA);

	ll_printNodes();
}

void amp_cloudCircle()
{
	//local var decl.
	GLfloat incre = 0.1f;
	GLfloat radius = 0.5f;

	//code
	glTranslatef(0.0f, 0.0f, -5.0f);

	//Upper 3 Circles - Left Circle
	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate - 0.5f, Y_coordinate - 0.2f);
	}
	glEnd();

	//Upper 3 Circles - Centre Circle
	radius = 0.45f;

	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate, Y_coordinate);
	}
	glEnd();

	//Upper 3 Circles - Right Circle
	radius = 0.4f;

	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate + 0.5f, Y_coordinate - 0.2f);
	}
	glEnd();

	//Lower 3 Circles - Left Circle
	radius = 0.35f;
	
	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate - 0.6f, Y_coordinate - 0.6f);
	}
	glEnd();

	//Lower 3 Circles - Centre Circle
	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate, Y_coordinate - 0.7f);
	}
	glEnd();

	//Lower 3 Circles - Right Circle
	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate + 0.5f, Y_coordinate - 0.6f);
	}
	glEnd();
}

void amp_sky()
{
	//func decl.
	void amp_cloudCircle();

	//code
	//setting camera for the frame scene
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	//clouds from left side of screen
	//background
	glPushMatrix();
	{
		glTranslatef(gfMoveSky_x, 0.0f, -15.0f);
		glBegin(GL_QUADS);
		{
			//glColor3fv(color_array);
			glColor3f(0.0f, 0.5f, 0.8f); 				//azure blue for sky
			//glColor3f(204.0f/256.0f, 1.0f, 1.0f);
			glVertex3f(-15.0f, 9.0f, 0.0f);
			glVertex3f(-15.0f, -5.0f, 0.0f);
			glVertex3f(15.0f, -5.0f, 0.0f);
			glVertex3f(15.0f, 9.0f, 0.0f);

			glColor3f(0.0f, 0.5f, 0.8f);		
			glVertex3f(-15.0f, -5.0f, 0.0f);
			glVertex3f(-15.0f, -11.0f, 0.0f);
			glVertex3f(15.0f, -11.0f, 0.0f);
			glVertex3f(15.0f, -5.0f, 0.0f);

			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glEnd();
	}
	glPopMatrix();

	//cloud 1
	glPushMatrix();
	{
		glTranslatef(-6.0f + gfMoveSky_x, 3.5f, 0.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 2
	glPushMatrix();
	{
		glTranslatef(-4.5f + gfMoveSky_x, 1.4f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 3
	glPushMatrix();
	{
		glTranslatef(-2.5f + gfMoveSky_x, 2.8f, 2.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 4
	glPushMatrix();
	{
		glTranslatef(-1.3f + gfMoveSky_x, 1.4f, 1.0f);
		glScalef(1.5f, 1.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 5
	glPushMatrix();
	{
		glTranslatef(-0.1f + gfMoveSky_x, 1.1f, 1.0f);
		glScalef(1.5f, 1.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 6
	glPushMatrix();
	{
		glTranslatef(1.0f + gfMoveSky_x, 3.0f, 1.0f);
		glScalef(0.9f, 0.9f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 7
	glPushMatrix();
	{
		glTranslatef(2.0f + gfMoveSky_x, 2.8f, 1.0f);
		glScalef(1.1f, 1.1f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 8
	glPushMatrix();
	{
		glTranslatef(3.2f + gfMoveSky_x, 0.8f, 2.5f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 9
	glPushMatrix();
	{
		glTranslatef(4.3f + gfMoveSky_x, 0.3f, 2.5f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.8f, 0.8f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 10
	glPushMatrix();
	{
		glTranslatef(4.0f + gfMoveSky_x, 2.5f, 2.5f);
		glScalef(0.6f, 0.6f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 11
	glPushMatrix();
	{
		glTranslatef(4.4f + gfMoveSky_x, 2.5f, 2.5f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//lower clouds from left side
	//cloud 1
	glPushMatrix();
	{
		glTranslatef(-6.0f + gfMoveSky_x, -3.0f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 2
	glPushMatrix();
	{
		glTranslatef(-5.0f + gfMoveSky_x, -3.0f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.7f, 0.7f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 3
	glPushMatrix();
	{
		glTranslatef(-5.8f + gfMoveSky_x, -1.5f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.75f, 0.75f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 4
	glPushMatrix();
	{
		glTranslatef(-2.8f + gfMoveSky_x, -1.5f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.98f, 0.98f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 5
	glPushMatrix();
	{
		glTranslatef(-1.8f + gfMoveSky_x, -1.3f, 1.0f);
		glScalef(0.68f, 0.68f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 6
	glPushMatrix();
	{
		glTranslatef(-2.5f + gfMoveSky_x, -2.5f, 1.0f);
		glScalef(0.7f, 0.7f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 7
	glPushMatrix();
	{
		glTranslatef(0.5f + gfMoveSky_x, -1.8f, 1.0f);
		glScalef(1.1f, 1.1f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 8
	glPushMatrix();
	{
		glTranslatef(2.7f + gfMoveSky_x, -1.0f, 1.0f);
		glScalef(0.8f, 0.8f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 9
	glPushMatrix();
	{
		glTranslatef(2.5f + gfMoveSky_x, -2.7f, 2.5f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.6f, 0.6f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 10
	glPushMatrix();
	{
		glTranslatef(4.0f + gfMoveSky_x, -1.3f, 2.5f);
		glScalef(0.7f, 0.7f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 11
	glPushMatrix();
	{
		glTranslatef(4.6f + gfMoveSky_x, -1.3f, 2.5f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 12
	glPushMatrix();
	{
		glTranslatef(4.6f + gfMoveSky_x, -2.5f, 2.5f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();
}

void amp_sky2()
{
	//func decl.
	void amp_cloudCircle();

	//code
	//setting camera for the frame scene
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	//clouds from left side of screen
	//background
	glPushMatrix();
	{
		glTranslatef(gfMoveSky2_x, 0.0f, -15.0f);
		glBegin(GL_QUADS);
		{
			glColor3fv(gfaColor_black);
			//glColor3f(0.5f, 0.5f, 0.5f); 				//gray for sky
			//glColor3f(204.0f/256.0f, 1.0f, 1.0f);
			glVertex3f(-15.0f, 9.0f, 0.0f);
			glVertex3f(-15.0f, -5.0f, 0.0f);
			glVertex3f(15.0f, -5.0f, 0.0f);
			glVertex3f(15.0f, 9.0f, 0.0f);

			glColor3fv(gfaColor_black);		
			glVertex3f(-15.0f, -5.0f, 0.0f);
			glVertex3f(-15.0f, -11.0f, 0.0f);
			glVertex3f(15.0f, -11.0f, 0.0f);
			glVertex3f(15.0f, -5.0f, 0.0f);

			glColor3fv(gfaColor_gray);
		}
		glEnd();
	}
	glPopMatrix();

	//cloud 1
	glPushMatrix();
	{
		glTranslatef(-6.0f + gfMoveSky_x, 3.5f, 0.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 2
	glPushMatrix();
	{
		glTranslatef(-4.5f + gfMoveSky_x, 1.4f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 3
	glPushMatrix();
	{
		glTranslatef(-2.5f + gfMoveSky_x, 2.8f, 2.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 4
	glPushMatrix();
	{
		glTranslatef(-1.3f + gfMoveSky_x, 1.4f, 1.0f);
		glScalef(1.5f, 1.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 5
	glPushMatrix();
	{
		glTranslatef(-0.1f + gfMoveSky_x, 1.1f, 1.0f);
		glScalef(1.5f, 1.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 6
	glPushMatrix();
	{
		glTranslatef(1.0f + gfMoveSky_x, 3.0f, 1.0f);
		glScalef(0.9f, 0.9f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 7
	glPushMatrix();
	{
		glTranslatef(2.0f + gfMoveSky_x, 2.8f, 1.0f);
		glScalef(1.1f, 1.1f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 8
	glPushMatrix();
	{
		glTranslatef(3.2f + gfMoveSky_x, 0.8f, 2.5f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 9
	glPushMatrix();
	{
		glTranslatef(4.3f + gfMoveSky_x, 0.3f, 2.5f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.8f, 0.8f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 10
	glPushMatrix();
	{
		glTranslatef(4.0f + gfMoveSky_x, 2.5f, 2.5f);
		glScalef(0.6f, 0.6f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 11
	glPushMatrix();
	{
		glTranslatef(4.4f + gfMoveSky_x, 2.5f, 2.5f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//lower clouds from left side
	//cloud 1
	glPushMatrix();
	{
		glTranslatef(-6.0f + gfMoveSky_x, -3.0f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 2
	glPushMatrix();
	{
		glTranslatef(-5.0f + gfMoveSky_x, -3.0f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.7f, 0.7f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 3
	glPushMatrix();
	{
		glTranslatef(-5.8f + gfMoveSky_x, -1.5f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.75f, 0.75f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 4
	glPushMatrix();
	{
		glTranslatef(-2.8f + gfMoveSky_x, -1.5f, 1.0f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.98f, 0.98f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 5
	glPushMatrix();
	{
		glTranslatef(-1.8f + gfMoveSky_x, -1.3f, 1.0f);
		glScalef(0.68f, 0.68f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 6
	glPushMatrix();
	{
		glTranslatef(-2.5f + gfMoveSky_x, -2.5f, 1.0f);
		glScalef(0.7f, 0.7f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 7
	glPushMatrix();
	{
		glTranslatef(0.5f + gfMoveSky_x, -1.8f, 1.0f);
		glScalef(1.1f, 1.1f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 8
	glPushMatrix();
	{
		glTranslatef(2.7f + gfMoveSky_x, -1.0f, 1.0f);
		glScalef(0.8f, 0.8f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 9
	glPushMatrix();
	{
		glTranslatef(2.5f + gfMoveSky_x, -2.7f, 2.5f);
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.6f, 0.6f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 10
	glPushMatrix();
	{
		glTranslatef(4.0f + gfMoveSky_x, -1.3f, 2.5f);
		glScalef(0.7f, 0.7f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 11
	glPushMatrix();
	{
		glTranslatef(4.6f + gfMoveSky_x, -1.3f, 2.5f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();

	//cloud 12
	glPushMatrix();
	{
		glTranslatef(4.6f + gfMoveSky_x, -2.5f, 2.5f);
		glScalef(0.5f, 0.5f, 1.0f);
		amp_cloudCircle();
	}
	glPopMatrix();
}

void amp_sun()
{
	//local var decl.
	GLfloat incre = 0.1f;
	GLfloat radius = 1.0f;

	//code
	glTranslatef(0.0f, 0.0f, gfMoveSun_z);

	glColor3f(0.99f, 0.93f, 0.0f);

	//Upper 3 Circles - Left Circle
	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate - 0.5f, Y_coordinate - 0.2f);
	}
	glEnd();
}

void amp_moon()
{
	//local var decl.
	GLfloat incre = 0.1f;
	GLfloat radius = 1.0f;

	//code
	glTranslatef(0.0f, 0.0f, gfMoveSun_z);

	glColor3f(1.0f, 1.0f, 1.0f);

	//Upper 3 Circles - Left Circle
	glBegin(GL_POLYGON);
	for (GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate - 0.5f, Y_coordinate - 0.2f);
	}
	glEnd();
}

void amp_CODED()
{
	glLoadIdentity();
	glTranslatef(-2.8f, 0.0f, -7.0f);
	glScalef(0.15f, 0.15f, 0.0f);

	glTranslatef(2.8f, 0.0f, 0.0f);
	amp_chevron_left(gfaColor_green);

	glTranslatef(2.3f, 0.0f, 0.0f);
	amp_slash_forward(gfaColor_green);

	glTranslatef(1.5f, 0.0f, 0.0f);
	amp_chevron_right(gfaColor_green);
}

void amp_WITH()
{
	glLoadIdentity();
	glTranslatef(-0.6f, 0.0f, -7.0f);
	glScalef(0.09f, 0.09f, 0.0f);

	glTranslatef(-9.0f, 0.0f, 0.0f);
	amp_W(gfaColor_blue2);

	glTranslatef(2.1f, 0.0f, 0.0f);
	amp_I(gfaColor_blue2);

	glTranslatef(2.6f, 0.0f, 0.0f);
	amp_T(gfaColor_blue2);

	glTranslatef(2.8f, 0.0f, 0.0f);
	amp_H(gfaColor_blue2);
}

void amp_LOVE()
{
	glLoadIdentity();
	glTranslatef(0.0f, -0.1f, -7.0f);
	glScalef(0.25f, 0.25f, 0.25f);

	glBegin(GL_TRIANGLES);
		glColor3fv(gfaColor_red);
		glVertex3f(1.1f, 1.0f, 0.0f);
		glVertex3f(-1.1f, 1.0f, 0.0f);
		glVertex3f(0.0f, -0.6f, 0.0f);
	glEnd();

	glTranslatef(-0.5f, 0.99f, 0.0f);
	glScalef(0.50f, 0.50f, 0.50f);
	amp_heart_half_circle(gfaColor_red);

	glTranslatef(0.499f * 4 , 0.0, 0.0f);
	amp_heart_half_circle(gfaColor_red);
}

void amp_BY_ADITYA()
{
	glLoadIdentity();
	glTranslatef(1.4f, 0.0f, -7.0f);
	glScalef(0.09f, 0.09f, 0.0f);

	glTranslatef(-9.0f, 0.0f, 0.0f);
	amp_B(gfaColor_blue2, gfaColor_black);

	glTranslatef(2.3f, 0.0f, 0.0f);
	amp_Y(gfaColor_blue2);

	glScalef(1.2f, 1.2f, 1.2f);
	glTranslatef(4.1f, 0.0f, 0.0f);
	amp_A(gfaColor_yellow);

	glTranslatef(2.6f, 0.0f, 0.0f);
	amp_D(gfaColor_yellow);

	glTranslatef(2.6f, 0.0f, 0.0f);
	amp_I(gfaColor_yellow);

	glTranslatef(2.6f, 0.0f, 0.0f);
	amp_T(gfaColor_yellow);

	glTranslatef(2.6f, 0.0f, 0.0f);
	amp_Y(gfaColor_yellow);

	glTranslatef(2.2f, 0.0f, 0.0f);
	amp_A(gfaColor_yellow);
}

//linked list function definition
void ll_addAtBegin(void (*tempPtrToFunc)()){
	struct Node *tempNode = (struct Node *)malloc(sizeof(struct Node));
	tempNode->ptrToFunc = tempPtrToFunc;
	tempNode->next = head;

	head = tempNode;

	tempNode = NULL;

	free(tempNode);
}

void ll_printNodes(){
	struct Node *tempNode = head;

	while(tempNode != NULL){
		if(tempNode != NULL){
			tempNode->ptrToFunc();
		}
		tempNode = tempNode->next;
	}

	tempNode = NULL;
	free(tempNode);
}