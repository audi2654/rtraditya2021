//Date: 05/06/2022
//RTR2021 XWindows OpenGL Blue Screen

//cmd to use: gcc -o OGL OGL.c -lX11 -lGL
//-lX11 means file in /lib/x86_64-linux-gnu/libX11.so (shared object)
//-lGL is libGL.so 
//while linking through cmd remove lib & .so from library file name
//hello there gcc compiler give me output with name XWindow by taking Window.c file & linking with X11 library

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

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global variable decl.
Display *display = NULL;				
//77 member struct, doot or visible represention of root window from XServer dedicated to our this window application or XClient

XVisualInfo *visualInfo = NULL;	               //syntactical change

Colormap colormap;
Window window;						//similar to HWND hwnd in Windows

//for fullscreen
Bool fullscreen = False;

//for OpenGL
GLXContext glxContext;                          //GC gc

Bool bActiveWindow = False;

//entry point function
int main(void)
{
    //func. decl.
    void toggleFullscreen(void);
    void initialize(void);
    void resize(int, int);
    void draw(void);
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
                            None /*Xlib convention to end every array with a terminating  character here 0 also works*/
                        } ;
    
    Bool bDone = False;	
    
    //code
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
        	//update()
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

void initialize(void)
{
	//func decl.
	void uninitialize(void);
	
	//code
	glxContext = glXCreateContext(display, visualInfo, NULL, True);
	//3rd para is pointer to a already existing graphics context if you have multiple graphic cards & their multiple GCs 
	//then since Xlib is network compliant you can share the contexts
	//between each other or create a new one using it, here we don't have any so give NULL
	
	//4th para here as True means you ask Xlib to give native graphics card supported hardware rendering
	//False means asking for software rendering with VESA virtual drivers like gallium for intel, noah for nvidia
	
	glXMakeCurrent(display, window, glxContext);							//analogous to wglMakeCurrent() in win32
	
	//here starts OpenGL functionality
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
	//code
	glClear(GL_COLOR_BUFFER_BIT);
	
	glXSwapBuffers(display, window);
}

void uninitialize(void)
{
    //code
    //safe release: destroy in reverse order of variable created
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
}
