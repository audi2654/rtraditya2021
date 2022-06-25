//Date: 24/06/2022
//RTR2021 OGL Simple XTriangle

//cmd: gcc -o OGL OGL.c -lX11 -lGL -lGLU

//standard header files
#include <stdio.h>                              //for std io
#include <stdlib.h>                             //for exit()
#include <memory.h>                       //for memset()

//X11 (XServer) headers
#include <X11/Xlib.h>                       //for XClient APIs, analogous to windows.h in MS Windows
#include <X11/Xutil.h>                      //for XVisualInfo()
#include <X11/XKBlib.h>                 //for keyboard inputs

//OpenGL header files
#include <GL/gl.h>                              //for OpenGL functionalities
#include <GL/glx.h>                            //for XWindows bridging APIs
#include <GL/glu.h>                            //for glu functions

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global function decl.

//global variable decl.
//for windowing
Display* display = NULL;					//doot(ambassador) or visible represention of root window from XServer dedicated to our this window application or XClient
XVisualInfo *visualInfo = NULL;
Colormap colormap;
Window window;									//similar to HWND hwnd in Windows

//for fullscreen
Bool fullscreen = False;

//for active window
Bool bActiveWindow = False;

//for file I/O
FILE *gpFile = NULL;

//for OpenGL graphics context
GLXContext glxContext;					//similar to GC gc in Win32

//entry point function
int main(int argc, char* argv[], char* envp[])
{
	//func. decl.
	void toggleFullscreen(void);
	int initialize(void);
	void resize(int, int);
	void draw(void);
	void uninitialize(void);

	//local var. decl.
	int defaultScreen;
	int defaultDepth;																	//along with defaultScreen we also get graphics card & its VRAM depth buffer & hence screen depth too
    XSetWindowAttributes windowAttributes;					//similar to WNDCLASSEX struct in Win32 which stores window class information
	int styleMask;																			//for window style
	Atom wm_delete_window_atom;
	XEvent event;
	KeySym keySym;
	int screenWidth;
	int screenHeight;

	//for keyboard alphabet inputs
	char keys[26];

	//for fullscreen
	static int winWidth;
	static int winHeight;

	int frameBufferAttributes[] =	/*analogous to PFD attributes*/         /*OpenGL change*/
						{
							GLX_DOUBLEBUFFER, True,
							GLX_RGBA,
							GLX_RED_SIZE, 8,
							GLX_GREEN_SIZE, 8,
							GLX_BLUE_SIZE, 8,
							GLX_ALPHA_SIZE, 8,
							GLX_DEPTH_SIZE, 24,
							None	/*Xlib convention to end every array with a terminating  character here 0 also works*/
						};

	Bool bDone = False;

	//code
	//file I/O
	gpFile = fopen("XLog.txt", "w");
	if(gpFile == NULL)
	{
		printf("fopen() File I/O error. Creation of XLog file failed. Exitting !");
		exit(0);
	}
	else
	{
		fprintf(gpFile, "XWindow Log file CREATED successfully!\n");
	}

	display = XOpenDisplay(NULL;)
	if(display == NULL)
	{
		fprintf("ERROR: XOpenDisplay() failed\n");
		uninitialize();
		exit(1);
	}
}