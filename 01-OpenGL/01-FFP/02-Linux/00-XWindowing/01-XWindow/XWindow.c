//Date: 31/05/2022
//RTR2021 XWindows First Windowing Program

//cmd to use: gcc -o XWindow XWindow.c -lX11
//hello there gcc compiler give me output with name XWindow by taking Window.c file & linking with X11 library

//standard header files
#include <stdio.h>  		//for std io
#include <stdlib.h>    		//for exit()
#include <memory.h> 	//for memset()

//X11 (XServer) headers
#include <X11/Xlib.h>			//for XClient APIs, analogous to windows.h in MS Windows
#include <X11/Xutil.h>		//for XVisualInfo()
#include <X11/XKBlib.h>		//for Keyboard inputs

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global variable decl.
Display *display = NULL;		//77 member struct, doot / visible represention of root window from XServer dedicated to our this window application or XClient
								//so display is the first parameter of almost all APIs that start with X letter
XVisualInfo visualInfo;			//10 member struct, inside which it has 'visual' member which is a non-OpenGL, non-RTR 8 member struct 
								//analogous to PixelFormatDescriptor PFD  in Win32 which is non-OpenGL
Colormap colormap;
Window window;				//similar to HWND hwnd in Windows

//entry point function
int main(void)
{
	//func. decl.
	void uninitialize(void);
	
	//local var.
	int defaultScreen;								//primary monitor (with adapter) in HMONITORINFO in Win32 fullscreen code is defaultScreen in XWindows
													//use cmd to see it's integer, echo $DISPLAY o/p -> :1, internally it initializes a 'Screen' struct & 
													//this integer is a unique number representating that struct (like a Atom, analogous to return type of RegisterWindow in Win32)
	int defaultDepth;								//along with defaultScreen we also get graphics card & its VRAM depth buffer & hence screen depth too
	Status status;
	XSetWindowAttributes windowAttributes;	//similar to WNDCLASSEX struct in Win32 which stores window class information
	int styleMask;									//for window style
	Atom wm_delete_window_atom;
	XEvent event;
	KeySym keySym;
	
	//steps to create a XWindow
	//STEP-1: open Display struct
	//STEP-2: get default screen using display
	//STEP-3: get default depth using display & default screen
	//STEP-4: get visualInfo using XMatchVisualInfo() & do error checking
	//STEP-5: fill/initialize struct XSetWindowAttributes & along with that also state the colormap & eventmap
	//STEP-6: initialize global colormap using Colormap created in windowAttributes above
	//STEP-7: initialize window styles using StyleMask which will have attributes created in windowAttributes above
	//STEP-8: create window using XCreateWindow() Xlib API
	//STEP-9: give name to your window in title/caption bar
	//STEP-10: prepare our window to
			//a) closing by clicking on close button
			//b) closing by clicking on close button option in system menu
			//by creating & setting Window Manager / Desktop Environment protocol atom in 2 sub steps
	//STEP-11: actually show our window using XMapWindow() (ShowWindow() in Win32)
	//STEP-12: create message loop by
			//a) getting next event using XNextEvent() API
			//b) by handling keypress of Escape key
			//c) by handling message 33
	//STEP-13: after closing message loop call uninitilaize() & return
	
	//code
	//STEP-1: open Display struct
	display = XOpenDisplay(NULL);		//1st Xlib API call
	
	if(display == NULL)
	{
		printf("ERROR: XOpenDisplay() failed\n");
		uninitialize();
		exit(1);
	}
	
	//STEP-2: get default screen using display
	defaultScreen = XDefaultScreen(display);			//2nd Xlib API call
	//struct Display fills a struct Screen which all the primary monitor information & returns an integer representing the struct Screen 
	
	//when we get defaultScreen i.e monitor with adapter we also get graphics card along with it, 
	//hence we get VRAM & the frame buffers & its color, stencil, depth buffers too & hence below we are getting screen depth
	//this formulation for getting depth is only in RTR context & not in XServer's context	
	
	//STEP-3: get default depth using display & default screen
	defaultDepth = XDefaultDepth(display, defaultScreen);		//3rd Xlib API call
	
	//since XServer don't understand frame buffers or any other visual graphics properties RTR context
	//so XServer calls all the frame buffer, VRAM & graphics card related information & properties as 'visual' a 8 member struct
	 //which is inside 'visualInfo'
	//analogous to Win32 calling PFD for this graphics info & properties
	
	//STEP-4: get visualInfo using XMatchVisualInfo() & do error checking
	status = XMatchVisualInfo(display, defaultScreen, defaultDepth, TrueColor, &visualInfo);		//4th Xlib API call
	//matching or choosing visual info of preferred window from a internal window class list for this XClient App
	//TrueColor, DirectColor, StaticColor are predefined window color class & is analogous to you choosing/matching the type in PFB(PixelFormatDescriptor in Win32) 
	//from already created list in Win32 library but here from XServer's visuals list hence the name XMatchVisualInfo
	
	if(status == 0)
	{
		printf("ERROR: XMatchVisualInfo() failed\n");
		uninitialize();
		exit(1);
	}
	
	//STEP-5: fill/initialize struct XSetWindowAttributes & along with that also state the colormap & eventmap
	//XSetWindowAttributes has many attribute fields we are setting only 5 below
	
	memset(&windowAttributes, 0, sizeof(XSetWindowAttributes));					//similar to ZeroMemory() used in PFD in Win32, zeroing variable before using it
	
	windowAttributes.border_pixel = 0;												//0 here means default
	windowAttributes.background_pixel = XBlackPixel(display, defaultScreen);		//5th Xlib API call, similar to GetStockObject HBR_BACKGROUND Black Brush
	windowAttributes.background_pixmap = 0;										//pixmap is if you want a picture in the background or not
	windowAttributes.colormap = XCreateColormap(display,	/*6th Xlib API call*/
												RootWindow(display, visualInfo.screen), 	/*7th Xlib API call*/
												/*instead of visualInfo, defaultScreen would have also worked but its colormap may not be what we asked for in our case here TrueColor, */
												/*but visualInfo will give proper screen with TrueColor colormap because we ask for it in XMatchVisualInfo() above*/
												/*RootWindow is invisible, analogous to DefWndProc in Win32*/
												 visualInfo.visual,
												 AllocNone); 	/*AllocNone is for whether we want to allocate a new memory for colormap created here or not*/
	windowAttributes.event_mask = ExposureMask | KeyPressMask;		//event mask is the member which decides which msgs our wnd should respond to & which it should not, 
	//analogous to GetMessage() 3rd 4th para where range of msgs to receive can be defined
	
	//Colormap here is like elements periodic table kinda color table so TrueColor is a table/map of 2^32 individual colors called as color cells
	//& using XCreateColormap you create a colormap for your window visual to map to colors of TrueColor visual
	//ExposureMask here means WM_PAINT in Win32 
	//KeyPressMask here means WM_CHAR/WM_KEYDOWN in Win32
	
	//STEP-6: initialize global colormap using Colormap created in windowAttributes above
	colormap = windowAttributes.colormap;
	
	//STEP-7: initialize window styles using StyleMask which will have attributes created in windowAttributes above
	styleMask = CWBorderPixel | CWBackPixel | CWColormap | CWEventMask;
	
	//STEP-8: create window using XCreateWindow() Xlib API
	//XCreateWindow() in Xlib, CreateWindow() in Win32
	window = XCreateWindow(display,		/*8th Xlib API call*/
					   RootWindow(display, visualInfo.screen),
					   /* below paras are x (0) & y (500) coordinates for window position but adding them here is of no use,*/
					   /*because Window Manager has control over this in Linux*/
					   0,
					   500,
					    WIN_WIDTH,
					    WIN_HEIGHT,
					    0,
					    visualInfo.depth,
					    InputOutput,
					    visualInfo.visual,
					    styleMask,
					    &windowAttributes);
					    
	if (!window)
	{
		printf("ERROR: XCreateWindow() failed\n");
		uninitialize();
		exit(1);
	}
	
	//STEP-9: give name to your window in title/caption bar
	//unlike Win32 where we give name to our window inside CreateWindow(), 
	//in XWindows we have to call a seperate function if we want our wnd to have a name
	XStoreName(display, window, "AMP First XWindow");	//9th Xlib API call
	
	//STEP-10: prepare our window to
		//a) closing by clicking on close button
		//b) closing by clicking on close button option in system menu
	
	//by creating & setting Window Manager / Desktop Environment protocol atom in 2 sub steps
	
	//we have to do this because close button & window system menu are not in control of Xlib but in control of Window Manager(WM/DE)
	//because WM/DE give options to set close button on right or left top side of window, or wnd name in middle or left/right side
	
	//creating Atom
	wm_delete_window_atom = XInternAtom(display, "WM_DELETE_WINDOW", True);		//10th Xlib API callWM here is Window Manager
	//setting or adding Atom in WM's Protocol
	XSetWMProtocols(display, window, &wm_delete_window_atom, 1);						//11th Xlib API call
	
	//STEP-11: actually show our window using XMapWindow() (ShowWindow() in Win32)
	XMapWindow(display, window);															//12th Xlib API call
	
	//Message Loop
	//STEP-12: create message loop by
		//a) getting next event using XNextEvent() API
		//b) by handling keypress of Escape key
		//c) by handling message 33
		
	while(1)
	{
		XNextEvent(display, &event);															//13th Xlib API call
		
		switch(event.type)
		{
		//MapNotify in Xlib is analogous to WM_CREATE in Win32, it always comes whether we mention it in 
		//windowAttributes.event_mask or not & specifically handle it or not
		case MapNotify: 
			break;
			
		case KeyPress:
			keySym = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);				//14th Xlib API call
			//here we tell to XServer keyboard to convert our key code into key symbol
			//3rd para tells, will you be pressing only your keycode or a keycode group, so 0 here tells it will be a simple key code & not multiple keys e.g Alt+Ctrl+A
			//4th para tells, will you be pressinf Shift key with your key or not, 0 tells your key will be pressed without Shift
			
			switch(keySym)
			{
				case XK_Escape:
					uninitialize();
					exit(0);
					break;
			}
			
			break;
			
		case 33:
			uninitialize();
			exit(0);
			break;
		//33 is analogous to wm_delete_window_atom & is the number given by XServer after successfully 
		//registering atom in XSetWMProtocols in STEP-10
		}
	} 
	
	//STEP-13: after closing message loop call uninitilaize() & return
	uninitialize();
		    
	return(0);
}

//func definition
void uninitialize(void)
{
	//code
	//here we uninitialize, free or destroy everything that we create using Xlib
	//we don't free visualInfo because we do not create it, we are only matching it with already internally created visual list using XMatchVisualInfo()
	//safe release: destroy in reverse order of variable created
	if(window)
	{
		XDestroyWindow(display, window);				//15th Xlib API call
	}
	
	if(colormap)
	{
		XFreeColormap(display, colormap);				//16th Xlib API call
	}
	
	if(display)
	{
		XCloseDisplay(display);							//17th Xlib API call
		display = NULL; 
	}
}

