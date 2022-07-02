//Date: 30/06/2022
//RTR2021 OGL XIndia Dynamic with audio

//cmd: gcc -o OGL OGL.c -lX11 -lGL -lGLU

//standard header files
#include <stdio.h>                              //for std io
#include <stdlib.h>                             //for exit()
#include <memory.h>                       		//for memset()
#include <math.h>								//for PI, sin, cos

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
Bool gbFlag_I = True;
Bool gbFlag_N = False;
Bool gbFlag_D = False;
Bool gbFlag_I2 = False;
Bool gbFlag_A = False;
Bool gbFlag_Planes = False;

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
							GLX_DEPTH_SIZE, 24,
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

	//for alpha in glColor4f()
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);

	//warm up resize call
	//without this maroon or brownish window comes first
	amp_resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);
	//16 is border size 8-8 right & left size
	//39 is 8 top border, 23 menu bar, 8 bottom border of window
	//all funcs give window size including its border

	//toggleFullScreen();	//to start program in fullscreen

	//start song or in MapNotify

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
	//func decl.
	void amp_I();
	void amp_N();
	void amp_D();
	void amp_A();
	void amp_F();
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

	if(gbFlag_I == True)
	{
		glLoadIdentity();
		glTranslatef(gfMoveI_x, gfMoveI_y, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_I();
	}
	

	if(gbFlag_N == True)
	{
		glLoadIdentity();
		glTranslatef(-6.0, gfMoveN_y, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_N();
	}
	
	if(gbFlag_D == True)
	{
		glLoadIdentity();
		glTranslatef(-0.0f, 0.0f, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_D();
	}
	
	if(gbFlag_I2 == True)
	{
		glLoadIdentity();
		glTranslatef(5.1f, gfMoveI2_y, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_I();
	}
	
	if(gbFlag_A == True)
	{
		glLoadIdentity();
		glTranslatef(gfMoveA_x, 0.0f, -28.0f);
		glScalef(2.3,2.3,2.3);
		amp_A();
	}
	
	if(gbFlag_Planes == True)
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
	
	glXSwapBuffers(amp_display, amp_window);
}

void amp_update(void)
{
	//local var decl.

	//code
	//translating letter I from left side of screen
	if(gbFlag_I == True)
	{
		gfMoveI_x = gfMoveI_x + 0.02f;
		if(gfMoveI_x >= -11.0f)
		{
			gfMoveI_x = -11.0f;
			gbFlag_N = True;
		}
	}

	//translating letter N from top side of screen
	if(gbFlag_N)
	{
		gfMoveN_y = gfMoveN_y - 0.02f;
		if(gfMoveN_y <= 0.0f)
		{
			gfMoveN_y = 0.0f;
			gbFlag_D = True;
		}
			
	}
	
	//translating letter D from inside out of screen
	if(gbFlag_D == True)
	{
		gfMoveD_z = gfMoveD_z + 0.08f;
		if(gfMoveD_z >= -28.0f)
		{
			gfMoveD_z = -28.0f;
			gbFlag_I2 = True;
		}

		//1.0, 0.60, 0.20
		gfSaffColor_R = gfSaffColor_R + 0.002;
		if(gfSaffColor_R >= 1.0f)
		{
			gfSaffColor_R = 1.0f;
		}
		gfSaffColor_G = gfSaffColor_G + 0.002;
		if(gfSaffColor_G >= 0.60f)
		{
			gfSaffColor_G = 0.60f;
		}
		gfSaffColor_B = gfSaffColor_B + 0.002;
		if(gfSaffColor_B >= 0.20f)
		{
			gfSaffColor_B = 0.20f;
		}

		//1.0, 1.0, 1.0
		gfWhiteColor_R = gfWhiteColor_R + 0.002;
		if(gfWhiteColor_R >= 1.0f)
		{
			gfWhiteColor_R = 1.0f;
		}
		gfWhiteColor_G = gfWhiteColor_G + 0.002;
		if(gfWhiteColor_G >= 1.0f)
		{
			gfWhiteColor_G = 1.0f;
		}
		gfWhiteColor_B = gfWhiteColor_B + 0.002;
		if(gfWhiteColor_B >= 1.0f)
		{
			gfWhiteColor_B = 1.0f;
		}

		//0.19, 0.9, 0.08
		gfGreenColor_R = gfGreenColor_R + 0.002;
		if(gfGreenColor_R >= 0.19f)
		{
			gfGreenColor_R = 0.19f;
		}
		gfGreenColor_G = gfGreenColor_G + 0.002;
		if(gfGreenColor_G >= 0.9f)
		{
			gfGreenColor_G = 0.9f;
		}
		gfGreenColor_B = gfGreenColor_B + 0.002;
		if(gfGreenColor_B >= 0.08f)
		{
			gfGreenColor_B = 0.08f;
		}
	}
	

	//translating letter N2 from bottom side of screen
	if(gbFlag_I2 == True)
	{
		gfMoveI2_y = gfMoveI2_y + 0.02f;
		if(gfMoveI2_y >= 0.0f)
		{
			gfMoveI2_y = 0.0f;
			gbFlag_A = True;
		}
			
	}

	//translating letter A from right side of screen
	if(gbFlag_A == True)
	{
		gfMoveA_x = gfMoveA_x - 0.02f;
		if(gfMoveA_x <= 10.0f)
		{
			gfMoveA_x = 10.0f;
			gbFlag_Planes = True;
		}
	}
	
	if(gbFlag_Planes == True)
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

void amp_F()
{
//vertical line of F 
	//top quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(-0.5f, 1.0f, 0.f);
	glVertex3f(-0.9f, 1.0f, 0.f);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-0.9f, 0.0f, 0.f);
	glVertex3f(-0.5f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(-0.5f, 0.0f, 0.f);
	glVertex3f(-0.9f, 0.0f, 0.f);
	glColor3f(0.19, 0.9, 0.08);			//india green
	glVertex3f(-0.9f, -1.0f, 0.f);
	glVertex3f(-0.5f, -1.0f, 0.f);
	glEnd();

//upper horizontal line of F
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.60, 0.20);			//saffron
	glVertex3f(.9f, 1.3f, 0.f);
	glVertex3f(-.9f, 1.3, 0.f);
	glVertex3f(-.9f, 1.0f, 0.f);
	glVertex3f(.9f, 1.0f, 0.f);
	glEnd();

//lower horizontal line of F
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);			//white
	glVertex3f(0.5f, 0.4f, 0.f);
	glVertex3f(-.9f, 0.4f, 0.f);
	glVertex3f(-.9f, 0.1f, 0.f);
	glVertex3f(.5f, 0.1f, 0.f);
	
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
	amp_F();
}
