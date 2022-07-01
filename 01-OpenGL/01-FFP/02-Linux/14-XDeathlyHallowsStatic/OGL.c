//Date: 30/06/2022
//RTR2021 OGL XStatic Deathly Hallows

//cmd: gcc -o OGL OGL.c -lX11 -lGL -lGLU -lm

//standard header files
#include <stdio.h>                              //for std io
#include <stdlib.h>                             //for exit()
#include <memory.h>                       		//for memset()
#include <math.h>								//for sin cos

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
Display* amp_display = NULL;					//doot(ambassador) or visible represention of root window from XServer dedicated to our this window application or XClient
XVisualInfo *amp_visualInfo = NULL;
Colormap amp_colormap;
Window amp_window;									//similar to HWND hwnd in Windows

//for fullscreen
Bool amp_fullscreen = False;

//for active window
Bool amp_bActiveWindow = False;

//for file I/O
FILE *amp_gpFile = NULL;

//for OpenGL graphics context
GLXContext amp_glxContext;					//similar to GC gc in Win32

//for circle type flag
Bool amp_gbCirclePoints = False;
Bool amp_gbCircleLineLoop = False;

//for triangle side length & inscribed circle radius
GLfloat gfTriangleSideLength = 1.0f;

//entry point function
int main(int argc, char* argv[], char* envp[])
{
	//func. decl.
	void amp_toggleFullscreen(void);
	int amp_initialize(void);
	void amp_resize(int, int);
	void amp_draw(void);
	void amp_update(void);
	void amp_uninitialize(void);

	//local var. decl.
	int amp_defaultScreen;
	int amp_defaultDepth;																	//along with amp_defaultScreen we also get graphics card & its VRAM depth buffer & hence screen depth too
    XSetWindowAttributes amp_windowAttributes;					//similar to WNDCLASSEX struct in Win32 which stores window class information
	int amp_styleMask;																			//for window style
	Atom wm_delete_window_atom;
	XEvent amp_event;
	KeySym keySym;
	int screenWidth;
	int screenHeight;
	int retVal = 0;

	//for keyboard alphabet inputs
	char keys[26];

	//for fullscreen
	static int winWidth;
	static int winHeight;

	int amp_frameBufferAttributes[] =	/*analogous to PFD attributes*/         /*OpenGL change*/
						{
							GLX_DOUBLEBUFFER, True,
							GLX_RGBA,
							GLX_RED_SIZE, 8,
							GLX_GREEN_SIZE, 8,
							GLX_BLUE_SIZE, 8,
							GLX_ALPHA_SIZE, 8,
							/*GLX_DEPTH_SIZE, 24,*/
							None	/*Xlib convention to end every array with a terminating  character here 0 also works*/
						};

	Bool bDone = False;

	//code
	//file I/O to create logs
	amp_gpFile = fopen("XLog.txt", "w");
	if(amp_gpFile == NULL)
	{
		printf("fopen() File I/O error. Creation of XLog file failed. Exitting !");
		exit(0);
	}
	else
	{
		fprintf(amp_gpFile, "XWindow Log file CREATED successfully!\n");
	}

	//getting root window Display from XServer dedicated to our XClient Application
	amp_display = XOpenDisplay(NULL);
	if(amp_display == NULL)
	{
		printf("ERROR: XOpenDisplay() failed\n");
		amp_uninitialize();
		exit(1);
	}

	//getting primary monitor information in struct Screen using amp_display
	amp_defaultScreen = XDefaultScreen(amp_display);

	//getting default depth of current screen for graphics context
	amp_defaultDepth = XDefaultDepth(amp_display, amp_defaultScreen);

	//matching or choosing visual info of preferred window from a internal window class list for this XClient App
	amp_visualInfo = glXChooseVisual(amp_display, amp_defaultScreen, amp_frameBufferAttributes);
	if(amp_visualInfo == NULL)
	{
		fprintf(amp_gpFile, "ERROR: glXChooseVisual failed\n");
        amp_uninitialize();
        exit(1);
	}

	//filling/initializing struct XSetWindowAttributes by zeroing its members first
	memset(&amp_windowAttributes, 0, sizeof(XSetWindowAttributes));

	amp_windowAttributes.border_pixel = 0;
	amp_windowAttributes.background_pixel = XBlackPixel(amp_display, amp_defaultScreen);
	amp_windowAttributes.background_pixmap = 0;
	amp_windowAttributes.colormap = XCreateColormap(
																amp_display, 
																RootWindow(amp_display, amp_visualInfo->screen),
																amp_visualInfo->visual,
																AllocNone);
	amp_windowAttributes.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask | FocusChangeMask;

	//initliazing amp_colormap (i.e a table/map of range of colors) using Colormap created in amp_windowAttributes above
	amp_colormap = amp_windowAttributes.colormap;

	//initialize window style using StyleMask which will have attributes created in amp_windowAttributes above
	amp_styleMask = CWBorderPixel | CWBackPixel | CWColormap | CWEventMask;

	//creating window
	amp_window = XCreateWindow(amp_display, 
														RootWindow(amp_display, amp_visualInfo->screen),
														0,
														0,
														WIN_WIDTH,
														WIN_HEIGHT,
														0,
														amp_visualInfo->depth,
														InputOutput,
														amp_visualInfo->visual,
														amp_styleMask,
														&amp_windowAttributes);
	
	if(!amp_window)
	{
		fprintf(amp_gpFile, "ERROR: XCreateWindow() failed\n");
        amp_uninitialize();
        exit(1);
	}

	//naming window title/caption bar
	XStoreName(amp_display, amp_window, "AMP OGL XWindow");

	//creating Atom & setting/adding it in WindowManager's protocol for System Menu Close & Close button to work
	wm_delete_window_atom = XInternAtom(amp_display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(amp_display, amp_window, &wm_delete_window_atom, 1);

	//actually showing our window
	XMapWindow(amp_display, amp_window);

	//centering the window: moving immediately after showing it as above so as to respect position decided by WindowManager while creating it
	screenWidth = XWidthOfScreen(XScreenOfDisplay(amp_display, amp_defaultScreen));
	screenHeight = XHeightOfScreen(XScreenOfDisplay(amp_display, amp_defaultScreen));
	XMoveWindow(amp_display, amp_window, (screenWidth / 2) - (WIN_WIDTH / 2), (screenHeight / 2) - (WIN_HEIGHT / 2));

	//initializing the graphics properties
	retVal = amp_initialize();
	if(retVal == -1)
	{
		fprintf(amp_gpFile, "In amp_initialize(): glXCreateContext() FAILED\n");
		amp_uninitialize();
	}
	else if(retVal == -2)
	{
		fprintf(amp_gpFile, "In amp_initialize(): glXMakeCurrent() FAILED\n");
		amp_uninitialize();
	}
	else
	{
		fprintf(amp_gpFile, "amp_initialize() SUCCESSFULL\n");
	}

	//message loop
	while(bDone == False)
	{
		while(XPending(amp_display))								//XPending is analogous to PeekMessage() in Win32
		{
			XNextEvent(amp_display, &amp_event);					//XNextEvent() is analogous to GetMessage() in Win32

			//handling event messages
			switch(amp_event.type)
			{
				case MapNotify:										//WM_CREATE in Win32
				break;

				case FocusIn:											//WM_SETFOCUS in Win32
				amp_bActiveWindow = True;
				break;

				case FocusOut:										//WM_KILLFOCUS in Win32
				amp_bActiveWindow = False;
				break;

				case KeyPress:
				keySym = XkbKeycodeToKeysym(amp_display, amp_event.xkey.keycode, 0, 0);			//WM_KEYDOWN in Win32
				switch(keySym)
				{
					case XK_Escape:
					bDone = True;
					break;
				}

				XLookupString(&amp_event.xkey, keys, sizeof(keys), NULL, NULL);						//WM_CHAR in Win32
				switch(keys[0])
				{
					case 'F':
					case 'f':
						if(amp_fullscreen == False)
						{
							amp_toggleFullscreen();
							amp_fullscreen = True;
						}
						else
						{
							amp_toggleFullscreen();
							amp_fullscreen = False;
						}
						break;

					default:
						break;
				}
				break;

				case ConfigureNotify:							//WM_SIZE in Win32
				winWidth = amp_event.xconfigure.width;
				winHeight = amp_event.xconfigure.height;
				amp_resize(winWidth, winHeight);
				break;

				case 33:													  //for Escape key, code return by XServer after successfully registering wm_delete_window_atom
				bDone = True;
				break;
			}
		}

		//checking if our window is in focus or not
		if(amp_bActiveWindow == True)
		{
			amp_update();
			amp_draw();
		}
	}

	amp_uninitialize();

	return(0);
}

//function definitions
void amp_toggleFullscreen(void)
{
	//local var decl.
	Atom wm_current_state_atom;
	Atom wm_fullscreen_state_atom;
	XEvent amp_event;

	//code
	wm_current_state_atom = XInternAtom(amp_display, "_NET_WM_STATE", False);
	wm_fullscreen_state_atom = XInternAtom(amp_display, "_NET_WM_STATE_FULLSCREEN", False);

	memset(&amp_event, 0, sizeof(XEvent));

	amp_event.type = ClientMessage;
	amp_event.xclient.window = amp_window;
	amp_event.xclient.message_type = wm_current_state_atom;
	amp_event.xclient.format = 32;
	amp_event.xclient.data.l[0] = amp_fullscreen ? 0 : 1;
	amp_event.xclient.data.l[1] = wm_fullscreen_state_atom;

	XSendEvent(amp_display,
							RootWindow(amp_display, amp_visualInfo->screen),
							False,
							SubstructureNotifyMask,
							&amp_event);
}

int amp_initialize(void)
{
	//func decl.
	void amp_resize(int, int);

	//code
	amp_glxContext = glXCreateContext(amp_display, amp_visualInfo, NULL, True);					//create a new GLX rendering context
	if(amp_glxContext == 0)
	{
		return(-1);
	}

	if(glXMakeCurrent(amp_display, amp_window, amp_glxContext) == 0)									//wglMakeCurrent() in Win32
	{
		return(-2);
	}

	//here starts OpenGL code
	//clear the screen using black color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//light related changes

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		//above 3 lines are must, below 2 lines are optional
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//warm up resize call
	//without this maroon or brownish window comes first
	amp_resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);
	//16 is border size 8-8 right & left size
	//39 is 8 top border, 23 menu bar, 8 bottom border of window
	//all funcs give window size including its border

	return(0);
}

void amp_resize(int width, int height)
{
	//code
	if(height == 0)
	{
		height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls
	}

	if(width == 0)
	{
		width = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void amp_draw(void)
{
	//func signature
	void amp_DotInCentre();
	void amp_HorizontalLine(GLfloat r, GLfloat g, GLfloat b);
	void amp_VerticalLine(GLfloat r, GLfloat g, GLfloat b);
	void amp_ParallelHorizontalLines();
	void amp_ParallelVerticalLines();
	void amp_Triangle();
	void amp_Rectangle();
	void amp_CirclePoints();
	void amp_CircleLineLoop();
	void amp_ConcentricCircles();

	//local var decl.

	//code
	glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);

	glMatrixMode(GL_MODELVIEW);

	glLineWidth(3.0f);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.f);
	glScalef(1.1f, 1.f, 0.0f);
	amp_Triangle();

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.f);
	glBegin(GL_LINES);
		glColor3f(1.0f,1.f,1.f);
		glVertex3f(0.0f, 1.f, 0.0f);
		glVertex3f(0.0f, -1.f, 0.0f);
	glEnd();

	glLoadIdentity();
	glTranslatef(0.0f, -0.10f, -1.1f);
	amp_CircleLineLoop();

	glXSwapBuffers(amp_display, amp_window);
}

void amp_update(void)
{
	//local var decl.

	//code
}

void amp_uninitialize(void)
{
	//local var decl.

	//code
	//safe release: destroy in reverse order of variable created
	GLXContext currentContext = glXGetCurrentContext();
	if(currentContext && (currentContext == amp_glxContext))
	{
		glXMakeCurrent(amp_display, 0, 0);
	}

	if(amp_glxContext)
	{
		glXDestroyContext(amp_display, amp_glxContext);
		amp_glxContext = NULL;
	}

	if(amp_fullscreen == True)
	{
		amp_toggleFullscreen();		//window should not die in Fullscreen mode
		amp_fullscreen = False;
	}

	if(amp_visualInfo)
	{
		free(amp_visualInfo);
		amp_visualInfo = NULL;
	}

	if(amp_window)
	{
		XDestroyWindow(amp_display, amp_window);
	}

	if(amp_colormap)
	{
		XFreeColormap(amp_display, amp_colormap);
	}

	if(amp_display)
	{
		XCloseDisplay(amp_display);
		amp_display = NULL;
	}

	if(amp_gpFile)
	{
		fprintf(amp_gpFile, "XWindow Log file CLOSED successfully!\n");
		fclose(amp_gpFile);
		amp_gpFile = NULL;
	}
}

//definition of user defined functions
void amp_DotInCentre()
{
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

void amp_HorizontalLine(GLfloat r, GLfloat g, GLfloat b)
{
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3f(r, g, b);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
}

void amp_VerticalLine(GLfloat r, GLfloat g, GLfloat b)
{
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glColor3f(r, g, b);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
}

void amp_ParallelHorizontalLines()
{
	//local var decl.
	GLfloat i = 1.0f;

	//code
	for(i; i > 0.0f; i = i - (0.05))
	{
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, i, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, i, 0.0f);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -i, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -i, 0.0f);
		glEnd();
	}
}

void amp_ParallelVerticalLines()
{
	//local var decl.
	GLfloat i = 1.0f;

	//code
	for(i; i > 0.0f; i = i - (0.05))
	{
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, 1.0, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(i, -1.0f, 0.0f);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-i, 1.0, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-i, -1.0f, 0.0f);
		glEnd();
	}
}

void amp_Triangle()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, gfTriangleSideLength, 0.0f);
	glVertex3f(-gfTriangleSideLength, -gfTriangleSideLength, 0.0f);
	glVertex3f(gfTriangleSideLength, -gfTriangleSideLength, 0.0f);
	glEnd();
}

void amp_Rectangle()
{
	//code
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glEnd();
}

void amp_CirclePoints()
{
	//local var decl.
	GLfloat incre = 1.0f;
	GLfloat radius = 0.3f;
	
	//code
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 1.0f);
	for(GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate, Y_coordinate);
	}
	glEnd();
}

void amp_CircleLineLoop()
{
	//local var decl.
	GLfloat incre = 1.0f;
	//GLfloat radius = 0.47f;
	GLfloat radius = cbrt(gfTriangleSideLength)/6;
	
	//code
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for(GLfloat i = 0; i < 360; i = i + incre)
	{
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		glVertex2f(X_coordinate, Y_coordinate);
	}
	glEnd();
}

void amp_ConcentricCircles()
{
	//func signature decl.
	void amp_CirclePoints();

	//local var decl.
	GLfloat i = 0.3;
	GLfloat increment = 0.3;
	GLfloat numberOfSquares = 10.0f;
	GLfloat maxSquares = increment * numberOfSquares;
	GLfloat translateUp = -1.0;

	//code
	for(i; i <= maxSquares; i += increment)
	{
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);
		glScalef(i, i, 0.0f);

		if(amp_gbCirclePoints == True)
		{
			
			amp_CirclePoints();
		}
		else if(amp_gbCircleLineLoop == True)
		{
			amp_CircleLineLoop();
		}
		translateUp += 0.1;
	}
}
