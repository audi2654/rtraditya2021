//Date: 30/06/2022
//RTR2021 OGL TwentyFour Spheres - Material

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

GLUquadric *quadric = NULL;		//bowl to draw spheres into

//for light
Bool gbLight = False;

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

					case 'L':
					case 'l':
						{
							if(gbLight == False)
							{
								glEnable(GL_LIGHTING);
								gbLight = True;
							}
							else
							{
								glDisable(GL_LIGHTING);
								gbLight = False;
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

void amp_draw(void)
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

	glXSwapBuffers(amp_display, amp_window);
}

void amp_update(void)
{
	//local var decl.

	//code
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
