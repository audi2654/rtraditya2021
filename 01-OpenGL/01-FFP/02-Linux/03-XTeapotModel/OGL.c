//Date: 11/06/2022
//RTR2021 XWindows OpenGL Utah Teapot Texture by Model Loading

//cmd to use: gcc -o OGL OGL.c -lX11 -lGL -lGLU -lSOIL
//-lX11 means file in /lib/x86_64-linux-gnu/libX11.so (shared object)
//-lGL is libGL.so 
//while linking through cmd remove lib & .so from library file name
//hello there gcc compiler give me output with name XWindow by taking Window.c file & linking with X11 library

//to install Simple OpenGL Image Library: sudo apt-get install libsoil-dev

//standard header files
#include <stdio.h>  						 //for std io
#include <stdlib.h>    					 	 //for exit()
#include <memory.h> 				            //for memset()

//X11 (XServer) headers
#include <X11/Xlib.h>					   //for XClient APIs, analogous to windows.h in MS Windows
#include <X11/Xutil.h>					  //for XVisualInfo()
#include <X11/XKBlib.h>				       //for Keyboard inputs

//OpenGL header files
#include <GL/gl.h>					      //for OpenGL functionalities
#include <GL/glx.h>					    //for XWindows bridging APIs
#include <GL/glu.h>                     //for glu functions

//texture library headers
#include <SOIL/SOIL.h>

//model library headers
#include "OGL.h"                         //for teapot

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global variable decl.
//for windowing
Display *display = NULL;				               //77 member struct, doot or visible represention of root window from XServer dedicated to our this window application or XClient
XVisualInfo *visualInfo = NULL;	               //syntactical change
Colormap colormap;
Window window;						                     //similar to HWND hwnd in Windows

//for fullscreen
Bool fullscreen = False;

//for active window
Bool bActiveWindow = False;

//for file I/O
FILE* gpFile = NULL;

//for OpenGL graphics context
GLXContext glxContext;                          //GC gc

//for texture variables
GLuint texture_marble;
GLfloat angle;
Bool gbTexture = False;

//for diffused light
GLfloat gfLightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gfLightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfLightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};
Bool gbLight = False;

//entry point function
int main(void)
{
    //func. decl.
    void toggleFullscreen(void);
    int initialize(void);
    void resize(int, int);
    void draw(void);
    void update(void);
    void uninitialize(void);
    
    //local var.
    int defaultScreen;								
    int defaultDepth;											    //along with defaultScreen we also get graphics card & its VRAM depth buffer & hence screen depth too
    XSetWindowAttributes windowAttributes;					//similar to WNDCLASSEX struct in Win32 which stores window class information
    int styleMask;												//for window style
    Atom wm_delete_window_atom;
    XEvent event;
    KeySym keySym;
    int screenWidth;
    int screenHeight;
    
    //for fullscreen
	char keys[26];

	static int winWidth;
    static int winHeight;
    
    int frameBufferAttributes[] = 	/*analogous to PFD attributes*/         /*OpenGL change*/
                        {
                        	GLX_DOUBLEBUFFER, True,
                            GLX_RGBA,
                            GLX_RED_SIZE, 8,
                            GLX_GREEN_SIZE, 8,
                            GLX_BLUE_SIZE, 8,
                            GLX_ALPHA_SIZE, 8,
                            GLX_DEPTH_SIZE, 24,
                            None /*Xlib convention to end every array with a terminating  character here 0 also works*/
                        } ;
    
    Bool bDone = False;	
    
    //code
    //file IO
    gpFile = fopen("XLog.txt", "w");       //return value or type ptr for the file opened or created = fopen("name of file to open or create / path of file to read/write", reason to open file "r", "w", "a", "r+", etc)
	if (gpFile == NULL)
	{
		printf("Creation of XLog file failed. Exitting! fopen() File I/O Error");
		exit(0);
	}
	else
	{
		fprintf(gpFile, "XWindow Log file CREATED successfully!\n");
	}

    display = XOpenDisplay(NULL);
    
    if(display == NULL)
    {
        printf("ERROR: XOpenDisplay() failed\n");
        uninitialize();
        exit(1);
    }
    
    defaultScreen = XDefaultScreen(display);
    
    defaultDepth = XDefaultDepth(display, defaultScreen);
    
    visualInfo = glXChooseVisual(display, defaultScreen, frameBufferAttributes);                        //OpenGL change
    //now here we choose visualInfo instead of matching & visualInfo is now pointer so we'll have to use arrow to access its elements
    
    if(visualInfo == NULL)
    {
        printf("ERROR: glXChooseVisual failed\n");
        uninitialize();
        exit(1);
    }
    
    memset(&windowAttributes, 0, sizeof(XSetWindowAttributes));
    
    windowAttributes.border_pixel = 0;                          		
    windowAttributes.background_pixel = XBlackPixel(display, defaultScreen);
    windowAttributes.background_pixmap = 0;
    windowAttributes.colormap = XCreateColormap(display,
                                                RootWindow(display, visualInfo->screen),
                                                 visualInfo->visual,
                                                 AllocNone); 
    windowAttributes.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask | FocusChangeMask;

    colormap = windowAttributes.colormap;
    
    styleMask = CWBorderPixel | CWBackPixel | CWColormap | CWEventMask;

    window = XCreateWindow(display,		
                       RootWindow(display, visualInfo->screen),
                       0,
                       500,
                        WIN_WIDTH,
                        WIN_HEIGHT,
                        0,
                        visualInfo->depth,
                        InputOutput,
                        visualInfo->visual,
                        styleMask,
                        &windowAttributes);
                        
    if (!window)
    {
        printf("ERROR: XCreateWindow() failed\n");
        uninitialize();
        exit(1);
    }
    
    XStoreName(display, window, "AMP XWindow OGL");
    
    //creating Atom
    wm_delete_window_atom = XInternAtom(display, "WM_DELETE_WINDOW", True);
    //setting or adding Atom in WM's Protocol
    XSetWMProtocols(display, window, &wm_delete_window_atom, 1);

    XMapWindow(display, window);
    
    //centering of window
    screenWidth = XWidthOfScreen(XScreenOfDisplay(display, defaultScreen));
    screenHeight = XHeightOfScreen(XScreenOfDisplay(display, defaultScreen));
    XMoveWindow(display, window, (screenWidth / 2) - (WIN_WIDTH / 2), (screenHeight / 2) - (WIN_HEIGHT / 2)); 

    initialize();

    //message Loop
    while(bDone == False)
    {
        while(XPending(display))								//XPending is analogous to PeekMessage() in Win32
        {
			XNextEvent(display, &event);					//XNextEvent() is analogous to GetMessage() in Win32
			
			switch(event.type)
			{
			case MapNotify: 
			break;

			case FocusIn:													//WM_SETFOCUS in Win32
			bActiveWindow = True;
			break;

			case FocusOut:												//WM_KILLFOCUS in Win32
			bActiveWindow = False;
			break;
			
			case KeyPress:
			keySym = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);
			
			switch(keySym)
			{
				case XK_Escape:
				bDone = True;
				break;
			}
			
			XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
			
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

                case 'T':
                case 't':
                {
                    if(gbTexture == False)
                    {
                        glEnable(GL_TEXTURE_2D);
                        gbTexture = True;
                    }
                    else
                    {
                        glDisable(GL_TEXTURE_2D);
                        gbTexture = False;
                    }
                }
                break;
			}
			break;

			case ConfigureNotify:
				winWidth = event.xconfigure.width;
				winHeight = event.xconfigure.height;
				resize(winWidth, winHeight);
			break;
			
			case 33:
				bDone = True;
				break;
			}
        }
        
//confirm this position -----------------------------------------------------
        if(bActiveWindow == True)
        {
        	update();
        	draw();
        }
    }
    
    uninitialize();
            
    return(0);
}

//func definition
void toggleFullscreen(void)
{
    //local var. decl
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
    void resize(int, int);
	Bool loadGlTexture(GLuint*, const char*);
	
	//code
	glxContext = glXCreateContext(display, visualInfo, NULL, True);
	//3rd para is pointer to a already existing graphics context if you have multiple graphic cards & their multiple GCs 
	//then since Xlib is network compliant you can share the contexts
	//between each other or create a new one using it, here we don't have any so give NULL
	
	//4th para here as True means you ask Xlib to give native graphics card supported hardware rendering
	//False means asking for software rendering with VESA virtual drivers like gallium for intel, noah for nvidia
	
	glXMakeCurrent(display, window, glxContext);							//analogous to wglMakeCurrent() in win32
	
	//here starts OpenGL functionality
	//clear the screen using blue color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA

    //diffused light related changes
	//setting up various properties of LIGHT1
	glLightfv(GL_LIGHT1, GL_AMBIENT, gfLightAmbient);		//glLightfv(which light, property of light to modify, values to modify with)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, gfLightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, gfLightPosition);
	glEnable(GL_LIGHT1);

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		//above 3 lines are must, below 2 lines are optional
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//texture related code
	if(loadGlTexture(&texture_marble, "marble.bmp") == False)
	{
		return -5;
	}
	
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
    {
		height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls
    }

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//Perspective Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void draw(void)
{
    //local var decl.
    int vi, ni, ti;         //vertex index, normal index, texture index
    int i, j;

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.5f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

	//texture related code
    if(gbTexture == True)
    {
	    glBindTexture(GL_TEXTURE_2D, texture_marble);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //texture coordinates are image manipulator library & OS specific
    //when SOIL lib is used for linux tex coords are exactly inverted to that of Windows because image is processed in inverted manner

	glBegin(GL_TRIANGLES);
	for(i = 0; i < sizeof(face_indices) / sizeof(face_indices[0]); i++)
    {
        for(j = 0; j < 3; j++)
        {
            vi = face_indices[i][j];
            ni = face_indices[i][j + 3];
            ti = face_indices[i][j + 6];

            glNormal3f(normals[ni][0], normals[ni][1], normals[ni][2]);
            glTexCoord2f(textures[ti][0], textures[ti][1]);
            glVertex3f(vertices[vi][0], vertices[vi][1], vertices[vi][2]);
        }
    }
	glEnd();
	
	glXSwapBuffers(display, window);
}

void update(void)
{
    //code
    angle = angle + 1.0f;
    if(angle >= 360.0f)
    {
        angle = 0.0f;
    }
}

void uninitialize(void)
{
    //code
    //safe release: destroy in reverse order of variable created
    if(texture_marble)
    {
        glDeleteTextures(1, &texture_marble);
        texture_marble = 0;
    }

    GLXContext currentContext = glXGetCurrentContext();
    if(currentContext && currentContext == glxContext)
    {
    	glXMakeCurrent(display, 0, 0);
    }
    
    if(glxContext)
    {
    	glXDestroyContext(display, glxContext);
    	glxContext = NULL;
    }
    
    if(visualInfo)
    {
    	free(visualInfo);
    	visualInfo = NULL;
    }
    
    if(fullscreen == True)
    {
        toggleFullscreen();
        fullscreen = False;
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

    if (gpFile)
	{
		fprintf(gpFile, "XWindow Log file CLOSED successfully!\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

//definition for user defined function
Bool loadGlTexture(GLuint* texture, const char* path)
{
    //local var decl.
    int width, height;
    unsigned char* imageData = NULL;

    //code
    imageData = SOIL_load_image(path, &width, &height, NULL, SOIL_LOAD_RGB);
    if(imageData == NULL)
        return (False);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    //here we tell to unpack the pixels & arrange them in aligned manner of rows of 4 bits
    //4 types that is RGBA

    glGenTextures(1, texture);		//5th step

    glBindTexture(GL_TEXTURE_2D, *texture);		//6th step - binding texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //7th step
    //when texture is near to viewer we tell OGL to draw it with magnified/maximum details

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //7th step
    //when texture is far from viewer we tell OGL to draw it with minimum details
    //for less load on OGL machine & increase performance

    //creating the actual texture
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    //not avaiable in OGL PP, wrapper function for glTextImage2D() & glGenerateMipMaps()

    glBindTexture(GL_TEXTURE_2D, 0);	//8th step - unbinding texture

    SOIL_free_image_data(imageData);

    return(True);
}
