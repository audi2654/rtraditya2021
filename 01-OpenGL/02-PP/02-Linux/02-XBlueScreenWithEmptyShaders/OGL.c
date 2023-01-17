//Date: 24/06/2022
//RTR2021 OGL XBlue Screen with Empty Passthrough Shaders
//Template used FFP XSimple Triangle

//cmd: gcc -o OGL OGL.c -lX11 -lGL -lGLU -lGLEW

//-lX11 means file in /lib/x86_64-linux-gnu/libX11.so (shared object)
//-lGL is libGL.so 
//while linking through cmd remove lib & .so from library file name
//hello there gcc compiler give me output with name XWindow by taking Window.c file & linking with X11 library

//standard header files
#include <stdio.h>                              //for std io
#include <stdlib.h>                             //for exit()
#include <memory.h>                       		//for memset()

//X11 (XServer) headers
#include <X11/Xlib.h>                       	//for XClient APIs, analogous to windows.h in MS Windows
#include <X11/Xutil.h>                      	//for XVisualInfo()
#include <X11/XKBlib.h>                 		//for keyboard inputs

//OpenGL header files
#include <GL/glew.h>		                	//this must be included above gl.h file, for glew
#include <GL/gl.h>                              //for OpenGL functionalities
#include <GL/glx.h>                            	//for XWindows bridging APIs

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global function decl.

//global variable decl.
//for windowing
Display* display = NULL;						//doot(ambassador) or visible represention of root window from XServer dedicated to our this window application or XClient
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
GLXContext glxContext;							//similar to GC gc in Win32

//PP related global vars
GLuint shaderProgramObject;

//entry point function
int main(int argc, char* argv[], char* envp[])
{
	//func. decl.
	void toggleFullscreen(void);
	int initialize(void);
	void resize(int, int);
	void draw(void);
	void update(void);
	void uninitialize(void);

	//local var. decl.
	int defaultScreen;
	int defaultDepth;										//along with defaultScreen we also get graphics card & its VRAM depth buffer & hence screen depth too
    XSetWindowAttributes windowAttributes;					//similar to WNDCLASSEX struct in Win32 which stores window class information
	int styleMask;											//for window style
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
	//file I/O to create logs
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

	//getting root window Display from XServer dedicated to our XClient Application
	display = XOpenDisplay(NULL);
	if(display == NULL)
	{
		printf("ERROR: XOpenDisplay() failed\n");
		uninitialize();
		exit(1);
	}

	//getting primary monitor information in struct Screen using display
	defaultScreen = XDefaultScreen(display);

	//getting default depth of current screen for graphics context
	defaultDepth = XDefaultDepth(display, defaultScreen);

	//matching or choosing visual info of preferred window from a internal window class list for this XClient App
	visualInfo = glXChooseVisual(display, defaultScreen, frameBufferAttributes);
	if(visualInfo == NULL)
	{
		fprintf(gpFile, "ERROR: glXChooseVisual failed\n");
        uninitialize();
        exit(1);
	}

	//filling/initializing struct XSetWindowAttributes by zeroing its members first
	memset(&windowAttributes, 0, sizeof(XSetWindowAttributes));

	windowAttributes.border_pixel = 0;
	windowAttributes.background_pixel = XBlackPixel(display, defaultScreen);
	windowAttributes.background_pixmap = 0;
	windowAttributes.colormap = XCreateColormap(
																display, 
																RootWindow(display, visualInfo->screen),
																visualInfo->visual,
																AllocNone);
	windowAttributes.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask | FocusChangeMask;

	//initliazing colormap (i.e a table/map of range of colors) using Colormap created in windowAttributes above
	colormap = windowAttributes.colormap;

	//initialize window style using StyleMask which will have attributes created in windowAttributes above
	styleMask = CWBorderPixel | CWBackPixel | CWColormap | CWEventMask;

	//creating window
	window = XCreateWindow(display, 
		RootWindow(display, visualInfo->screen),
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		0,
		visualInfo->depth,
		InputOutput,
		visualInfo->visual,
		styleMask,
		&windowAttributes);
	
	if(!window)
	{
		fprintf(gpFile, "ERROR: XCreateWindow() failed\n");
        uninitialize();
        exit(1);
	}

	//naming window title/caption bar
	XStoreName(display, window, "AMP OGL XWindow");

	//creating Atom & setting/adding it in WindowManager's protocol for System Menu Close & Close button to work
	wm_delete_window_atom = XInternAtom(display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(display, window, &wm_delete_window_atom, 1);

	//actually showing our window
	XMapWindow(display, window);

	//centering the window: moving immediately after showing it as above so as to respect position decided by WindowManager while creating it
	screenWidth = XWidthOfScreen(XScreenOfDisplay(display, defaultScreen));
	screenHeight = XHeightOfScreen(XScreenOfDisplay(display, defaultScreen));
	XMoveWindow(display, window, (screenWidth / 2) - (WIN_WIDTH / 2), (screenHeight / 2) - (WIN_HEIGHT / 2));

	//initializing the graphics properties
	initialize();
	
	//message loop
	while(bDone == False)
	{
		while(XPending(display))								//XPending is analogous to PeekMessage() in Win32
		{
			XNextEvent(display, &event);						//XNextEvent() is analogous to GetMessage() in Win32

			//handling event messages
			switch(event.type)
			{
				case MapNotify:									//WM_CREATE in Win32
				break;

				case FocusIn:									//WM_SETFOCUS in Win32
				bActiveWindow = True;
				break;

				case FocusOut:									//WM_KILLFOCUS in Win32
				bActiveWindow = False;
				break;

				case KeyPress:
				keySym = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);			//WM_KEYDOWN in Win32
				switch(keySym)
				{
					case XK_Escape:
					bDone = True;
					break;
				}

				XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);				//WM_CHAR in Win32
				switch(keys[0])
				{
					case 'F':
					case 'f':
					if(fullscreen == False)
					{
						toggleFullscreen();
						fullscreen = True;
					}
					else
					{
						toggleFullscreen();
						fullscreen = False;
					}
					break;
				}
				break;

				case ConfigureNotify:							//WM_SIZE in Win32
				winWidth = event.xconfigure.width;
				winHeight = event.xconfigure.height;
				resize(winWidth, winHeight);
				break;

				case 33:										//for Escape key, code return by XServer after successfully registering wm_delete_window_atom
				bDone = True;
				break;
			}
		}

		//checking if our window is in focus or not
		if(bActiveWindow == True)
		{
			update();
			draw();
		}
	}

	uninitialize();

	return(0);
}

//function definitions
void toggleFullscreen(void)
{
	//local var decl.
	Atom wm_current_state_atom;
	Atom wm_fullscreen_state_atom;
	XEvent event;

	//code
	wm_current_state_atom = XInternAtom(display, "_NET_WM_STATE", False);
	wm_fullscreen_state_atom = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

	memset(&event, 0, sizeof(XEvent));

	event.type = ClientMessage;
	event.xclient.window = window;
	event.xclient.message_type = wm_current_state_atom;
	event.xclient.format = 32;
	event.xclient.data.l[0] = fullscreen ? 0 : 1;			//if else using ternary operators
	event.xclient.data.l[1] = wm_fullscreen_state_atom;

	XSendEvent(display,
							RootWindow(display, visualInfo->screen),
							False,
							SubstructureNotifyMask,
							&event);
}

int initialize(void)
{
	//func decl.
    void uninitialize();
    void printGLInfo();
	void resize(int, int);

	//code
	glxContext = glXCreateContext(display, visualInfo, NULL, True);					//create a new GLX rendering context

	glXMakeCurrent(display, window, glxContext);									//wglMakeCurrent() in Win32

	//glew initialization
	if (glewInit() != GLEW_OK)
	{
        printf("ERROR: glewInit() failed\n");
        uninitialize();
        exit(1);
    }

	//prinf OpenGL information
	printGLInfo();

	//vertex shader code
	const GLchar* vertexShaderSourceCode =
		"#version 450 core" \
		"\n" \
		"void main(void)" \
		"{" \
		"}";

	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

	glCompileShader(vertexShaderObject);			//inline shader compiler

	//error checking for vertex shader
	GLint status = 0;
	GLint infoLogLength = 0;
	char* log = NULL;

	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(vertexShaderObject, infoLogLength, &written, log);
				fprintf(gpFile, "\nVertex Shader Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//fragment shader code
	const GLchar* fragmentShaderSourceCode =
		"#version 450 core" \
		"\n" \
		"void main(void)" \
		"{" \
		"}";
	
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderObject, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);

	glCompileShader(fragmentShaderObject);			//inline shader compiler

	//error checking for fragment shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(fragmentShaderObject, infoLogLength, &written, log);
				fprintf(gpFile, "\nFragment Shader Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	shaderProgramObject = glCreateProgram();

	glAttachShader(shaderProgramObject, vertexShaderObject);
	glAttachShader(shaderProgramObject, fragmentShaderObject);

	glLinkProgram(shaderProgramObject);			//inline shader linker

	//error checking for shader program
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(shaderProgramObject, infoLogLength, &written, log);
				fprintf(gpFile, "\nShader Program Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//here starts OpenGL code
	//clear the screen using blue color
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//light related changes

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//above 3 lines are must, below 2 lines are for FFP & do not work in PP because they are deprecated, although there is no error given for them
	//glShadeModel(GL_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

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
	if(height == 0)
	{
		height = 100;
	}

	if(width == 0)
	{
		width = 100;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void draw(void)
{
	//local var decl.

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//here actual clearing happens with color which was set in initialize(), framebuffer/colorbuffer in VRAM

	//use shadeProgramObject
	glUseProgram(shaderProgramObject);

	//here there should be drawing code


	//unuse the shaderProgramObject
	glUseProgram(0);

	glXSwapBuffers(display, window);
}

void update(void)
{
	//local var decl.

	//code
}

void uninitialize(void)
{
	//local var decl.

	//code
	//safe release: destroy in reverse order of variable created
	GLXContext currentContext = glXGetCurrentContext();
	if(currentContext && (currentContext == glxContext))
	{
		glXMakeCurrent(display, 0, 0);
	}

	if(glxContext)
	{
		glXDestroyContext(display, glxContext);
		glxContext = NULL;
	}

	if(fullscreen == True)
	{
		toggleFullscreen();
		fullscreen = False;
	}

	if(visualInfo)
	{
		free(visualInfo);
		visualInfo = NULL;
	}

	if(window)
	{
		XDestroyWindow(display, window);
	}

	if(colormap)
	{
		XFreeColormap(display, colormap);
	}

	if(display)
	{
		XCloseDisplay(display);
		display = NULL;
	}

	if(gpFile)
	{
		fprintf(gpFile, "XWindow Log file CLOSED successfully!\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

//definition of user defined functions
void printGLInfo(void)
{
	//local var decl.
	GLint numExtensions = 0;

	//code
	fprintf(gpFile, "\nOpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(gpFile, "GLSL Version: %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));	//GLSL - Graphics Library Shading Language

	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);		//gives number of extensions

	fprintf(gpFile, "Number of supported extensions: %d\n", numExtensions);

	for (int i = 0; i < numExtensions; i++)
	{
		fprintf(gpFile, "%s\n", glGetStringi(GL_EXTENSIONS, i));
	}
	fprintf(gpFile, "\n");
}