//Date: 09/11/2022
//RTR2021 OGL PP Triangle, Square, Circle on Graph Paper

//header files
#include <windows.h>
#include <stdio.h>			//for file I/O functions
#include <stdlib.h>			//for exit()
#include "OGL.h"			//for icon

//OpenGL header files
#include <GL/glew.h>		//this must be included above gl.h file
#include <GL/gl.h>
#include "vmath.h"
using namespace vmath;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//OpenGL libraries
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

//global func decl.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global var decl.
//for fullscreen
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;	//handle to OpenGL Rendering Context
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

//PP related global vars
GLuint shaderProgramObject;

enum
{
	AMP_ATTRIBUTE_POSITION = 0,
	AMP_ATTRIBUTE_COLOR,
	AMP_ATTRIBUTE_NORMAL,
	AMP_ATTRIBUTE_TEXTURE0,
};

//triangle
GLuint vao_triangle;									//vertex array object for triangle shape
GLuint vbo_triangle_position;							//vertex buffer object for position
GLuint vbo_triangle_color;								//vertex buffer object for color

//square
GLuint vao_square;
GLuint vbo_square_position;
GLuint vbo_square_color;

//circle
GLuint vao_circle;
GLuint vbo_circle_position;
GLuint vbo_circle_color;
GLfloat amp_circle_points_array[1024];
void amp_CirclePoints();

//dot in centre
GLuint vao_dot;
GLuint vbo_dot_position;

//horizontal line
GLuint vao_horizontal_line;
GLuint vbo_hori_line_position;
GLuint vbo_hori_line_color;

//vertical line
GLuint vao_vertical_line;
GLuint vbo_verti_line_position;
GLuint vbo_verti_line_color;

//parallel horizontal lines
GLuint vao_para_hori_lines;
GLuint vbo_para_hori_lines_position;
GLuint vbo_para_hori_lines_color;

//vertical horizontal lines
GLuint vao_verti_hori_lines;
GLuint vbo_verti_hori_lines_position;
GLuint vbo_verti_hori_lines_color;

//user defined uniform vars
GLuint mvpMatrixUniform;
GLuint colorChangerUniform;				//to change color just before drawing geometry

mat4 perspectiveProjectionMatrix;

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
		TEXT("AMP RTR PP Window"),
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
		fprintf(gpFile, "glewInit() FAILED\n");
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
	void uninitialize(void);
	void printGLInfo(void);
	
	//variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	//code
	//zeroing/initializing all member of pfd to 0
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));	//similar to memset((void*)&pfd, NULL, sizeof(PIXELFORMATDESCRIPTOR));

	//initializing pfd struct
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;	
	//PFD_SUPPORT_OPENGL tells OS that we are not using WM_PAINT so no BeginPaint DC & its pixel, give us OpenGL wala DC pixel/painter/specialist
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

	//glew initialization
	if (glewInit() != GLEW_OK)
		return(-5);

	//prinf OpenGL information
	printGLInfo();

	//vertex shader code
	//we do not out the position because it is job of only vertex & not of fragments
	//we send this to fragment shader because coloring of fragments
	const GLchar* vertexShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec4 a_color;"
		"uniform mat4 u_mvpMatrix;" \
		"out vec4 a_color_out;" \
		"void main(void)" \
		"{" \
			"gl_Position = u_mvpMatrix * a_position;" \
			"a_color_out = a_color;"
		"}";

	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

	glCompileShader(vertexShaderObject);	//inline shader compiler

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
	//this should be exactly same as out vector in a_color_out in vertex shader above, coloring is job of fragments & position is of vertex
	const GLchar* fragmentShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"in vec4 a_color_out;"
		"uniform vec4 ua_color_changer;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
			"FragColor = ua_color_changer;" \
		"}";
	
	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderObject, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);

	glCompileShader(fragmentShaderObject);	//inline shader compiler

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

	//prelinking & binding of shader program object with vertex attributes 
	glBindAttribLocation(shaderProgramObject, AMP_ATTRIBUTE_POSITION, "a_position");			//viable place for andhar
	glBindAttribLocation(shaderProgramObject, AMP_ATTRIBUTE_COLOR, "a_color");

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

	//post linking retrieving uniformed location from shaderProgramObject
	mvpMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_mvpMatrix");				//viable place for andhar			
	colorChangerUniform = glGetUniformLocation(shaderProgramObject, "ua_color_changer");

	//here starts OpenGL code
	//declaration of vertex data arrays
	const GLfloat trianglePosition[] =
	{
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	const GLfloat triangleColor[] =
	{
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	const GLfloat squarePosition[] =
	{
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	const GLfloat squareColor[] =
	{
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};

	//to get circle position vertices
	amp_CirclePoints();

	const GLfloat dotPosition[] = 
	{
		0.0f, 0.0f
	};

	const GLfloat horiLinePosition[] = {
		-1.0f, 0.0f,
		1.0f, 0.0f
	};

	const GLfloat horiLineColor[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	const GLfloat vertiLinePosition[] = {
		0.0f, 1.0f,
		0.0f, -1.0f
	};

	const GLfloat vertiLineColor[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	//vao for TRIANGLE
	{
		glGenVertexArrays(1, &vao_triangle);
		glBindVertexArray(vao_triangle);
		
		//vbo for position
		glGenBuffers(1, &vbo_triangle_position);														//here vbo returns with a memory mapped I/O address from GPU VRAM, i.e watching GPU memory(khidki) from CPU memory(khidki)
		glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_position);											//binding vbo to a target point of type of GL_ARRAY_BUFFER means, this vbo addr will hold array buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(trianglePosition), trianglePosition, GL_STATIC_DRAW);		//putting trianglePosition array in vbo in VRAM; GL_STATIC_DRAW means to fill buffer data now or on runtime, for runtime use GL_DYNAMIC_DRAW
		glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);					//this function tells the way & how to see the data stored in vbo
		glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);												//enabling the buffer array at position AMP_ATTRIBUTE_POSITION for further vertex processing
		glBindBuffer(GL_ARRAY_BUFFER, 0);																//unbinding vertex array buffer

		//vbo for color
		glGenBuffers(1, &vbo_triangle_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColor), triangleColor, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);					//unbinding vertex array object vao for triangle
	}	

	//vao for SQUARE
	{
		glGenVertexArrays(1, &vao_square);
		glBindVertexArray(vao_square);

		//vbo for position
		glGenBuffers(1, &vbo_square_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_square_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squarePosition), squarePosition, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//vbo for color
		glGenBuffers(1, &vbo_square_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_square_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareColor), squareColor, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);					//unbinding vertex array object vao for square
	}

	//vao for CIRCLE
	{
		glGenVertexArrays(1, &vao_circle);
		glBindVertexArray(vao_circle);

		//vbo for position
		glGenBuffers(1, &vbo_circle_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_circle_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(amp_circle_points_array), amp_circle_points_array, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		/*
		//vbo for color
		glGenBuffers(1, &vbo_circle_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_circle_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(circleColor), circleColor, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);*/

		glBindVertexArray(0);					//unbinding vertex array object vao for circle
	}

	//vao for DOT IN CENTRE
	{
		glGenVertexArrays(1, &vao_dot);
		glBindVertexArray(vao_dot);

		//vbo for position
		glGenBuffers(1, &vbo_dot_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_dot_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(dotPosition), dotPosition, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	//vao for HORIZONTAL LINE
	{
		glGenVertexArrays(1, &vao_horizontal_line);
		glBindVertexArray(vao_horizontal_line);

		//vbo for line position
		glGenBuffers(1, &vbo_hori_line_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_hori_line_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(horiLinePosition), horiLinePosition, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		//vbo for color
		glGenBuffers(1, &vbo_hori_line_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_hori_line_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(horiLineColor), horiLineColor, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindVertexArray(0);					//unbinding vertex array object vao for circle
	}

	//vao for PARALLEL HORIZONTAL LINE
		//used vao for SINGLE HORIZONTAL LINE

	//vao for VERTICAL LINE
	{
		glGenVertexArrays(1, &vao_vertical_line);
		glBindVertexArray(vao_vertical_line);

		//vbo for line position
		glGenBuffers(1, &vbo_verti_line_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_verti_line_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertiLinePosition), vertiLinePosition, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		//vbo for color
		glGenBuffers(1, &vbo_verti_line_color);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_verti_line_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertiLineColor), vertiLineColor, GL_STATIC_DRAW);
		glVertexAttribPointer(AMP_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(AMP_ATTRIBUTE_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glBindVertexArray(0);					//unbinding vertex array object vao for circle
	}

	//clear the screen using color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//intializing perspective projection matrix
	perspectiveProjectionMatrix = mat4::identity();

	//warm up resize call
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
		height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls

	glViewport(0, 0, GLsizei(width), GLsizei(height));

	perspectiveProjectionMatrix = vmath::perspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
}

void display(void)
{
	//func decl.
	void amp_DotInCentre();
	void amp_HorizontalLine();
	void amp_VerticalLine(GLfloat tx, GLfloat ty, GLfloat tz, vec4 color, GLfloat line_width);
	void amp_ParallelHorizontalLines();
	void amp_ParallelVerticalLines();
	void amp_Triangle();
	void amp_Square();
	void amp_Circle();

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//here actual clearing happens with color which was set in initialize(), framebuffer/colorbuffer in VRAM

	//use shadeProgramObject
	glUseProgram(shaderProgramObject);

	//PARALLEL HORIZONTAL LINES
	amp_ParallelHorizontalLines();

	//PARALLEL VERTICAL LINES
	amp_ParallelVerticalLines();

	//SINGLE HORIZONTAL LINE
	amp_HorizontalLine();

	//SINGLE VERTICAL LINE
	amp_VerticalLine(0.0f, 0.0f, -1.0f, vec4(0.0f, 1.0f, 0.0f, 1.0f), 3.0f);

	//DOT IN CENTRE
	amp_DotInCentre();

	//TRIANGLE
	amp_Triangle();

	//SQUARE
	amp_Square();

	//CIRLCE
	amp_Circle();

	//unuse the shaderProgramObject
	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	//code - used in animation

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

	//deletion/uninitialization of vbo
	if (vbo_circle_position)
	{
		glDeleteBuffers(1, &vbo_circle_position);
		vbo_circle_position = 0;
	}

	if (vao_circle)
	{
		glDeleteVertexArrays(1, &vao_circle);
		vao_circle = 0;
	}

	if (vbo_square_position)
	{
		glDeleteBuffers(1, &vbo_square_position);
		vbo_square_position = 0;
	}

	if (vao_square)
	{
		glDeleteVertexArrays(1, &vao_square);
		vao_square = 0;
	}

	if (vbo_triangle_color)
	{
		glDeleteBuffers(1, &vbo_triangle_color);
		vbo_triangle_color = 0;
	}

	if (vbo_triangle_position)
	{
		glDeleteBuffers(1, &vbo_triangle_position);
		vbo_triangle_position = 0;
	}

	if (vao_triangle)
	{
		glDeleteVertexArrays(1, &vao_triangle);
		vao_triangle = 0;
	}

	//shader uninitialization
	if (shaderProgramObject)
	{
		glUseProgram(shaderProgramObject);
		
		GLsizei numAttachedShaders = 0;
		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numAttachedShaders);

		GLuint* shaderObjects = NULL;
		shaderObjects = (GLuint*)malloc(numAttachedShaders * sizeof(GLuint));

		glGetAttachedShaders(shaderProgramObject, numAttachedShaders, &numAttachedShaders, shaderObjects);

		for (GLsizei i = 0; i < numAttachedShaders; i++)
		{
			glDetachShader(shaderProgramObject, shaderObjects[i]);
			glDeleteShader(shaderObjects[i]);	//deleting shader obj from OGL memory
			shaderObjects[i] = 0;
		}

		free(shaderObjects);	//freeing malloc() memory
		shaderObjects = NULL;

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject);
		shaderProgramObject = 0;
	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);		//this call with NULL,NULL tells that takeaway rendering charge from ghrc
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);		//rendering charges are taken away, so delete & clean ghrc
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

//user defined func definition
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

void amp_Triangle(){
	//transformations related code
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, -7.0f);
	modelViewMatrix = translationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniform4fv(colorChangerUniform, 1, vec4(1.0f, 1.0f, 1.0f, 1.0f));					//white color

	glBindVertexArray(vao_triangle);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glBindVertexArray(0);
}

void amp_Square(){
	//transformations related code
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	modelViewMatrix = translationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniform4fv(colorChangerUniform, 1, vec4(1.0f, 1.0f, 1.0f, 1.0f));					//white color

	glBindVertexArray(vao_square);
	glDrawArrays(GL_LINE_LOOP, 0, 4);			//there are no QUADS in PP, every geometry has to made using GL_TRIANGLES or GL_TRIANGLES_FAN or GL_TRIANGLES_STRIP
	glBindVertexArray(0);
}

void amp_Circle(){
	//transformations related code
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	modelViewMatrix = translationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniform4fv(colorChangerUniform, 1, vec4(1.0f, 1.0f, 1.0f, 1.0f));					//white color
	
	glBindVertexArray(vao_circle);
	glDrawArrays(GL_LINE_LOOP, 0, 360);
	glBindVertexArray(0);
}

//generating circle coordinates
void amp_CirclePoints(){
	//local var decl.
	GLfloat incre = 1.0f;
	GLfloat radius = 0.3f;
	GLuint j = 0;
	
	//code		
	for(GLfloat i = 0; i < 360; i = i + incre)
	{	
		GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
		GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
		amp_circle_points_array[j] = X_coordinate;
		amp_circle_points_array[++j] = Y_coordinate;
		j++;
	}
}

void amp_DotInCentre(){
	//transformations related code
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	modelViewMatrix = translationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniform4fv(colorChangerUniform, 1, vec4(1.0f, 1.0f, 0.0f, 1.0f));					//yellow color
	
	glPointSize(10.f);
	glBindVertexArray(vao_dot);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void amp_HorizontalLine(){
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, -1.0f);
	modelViewMatrix = translationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniform4fv(colorChangerUniform, 1, vec4(1.0f, 0.0f, 0.0f, 1.0f));					//red color

	glLineWidth(3.0f);
	glBindVertexArray(vao_horizontal_line);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glLineWidth(1.0f);
}

void amp_VerticalLine(GLfloat tx, GLfloat ty, GLfloat tz, vec4 color, GLfloat line_width){
	mat4 translationMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(tx, ty, tz);
	scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);
	modelViewMatrix = translationMatrix * scaleMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
	glUniform4fv(colorChangerUniform, 1, color);					//green color

	glLineWidth(line_width);
	glBindVertexArray(vao_vertical_line);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glLineWidth(1.0f);
}

void amp_ParallelHorizontalLines(){
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	for(GLfloat i = 1.0f; i > 0.0f; i = i - 0.02f){
		//for +y axis lines
		translationMatrix = vmath::translate(0.0f, i, -1.0f);
		modelViewMatrix = translationMatrix;
		modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

		glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
		glUniform4fv(colorChangerUniform, 1, vec4(0.0f, 0.0f, 1.0f, 1.0f));					//blue color

		glBindVertexArray(vao_horizontal_line);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);

		//for -y axis lines
		translationMatrix = vmath::translate(0.0f, -i, -1.0f);
		modelViewMatrix = translationMatrix;
		modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

		glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
		glUniform4fv(colorChangerUniform, 1, vec4(0.0f, 0.0f, 1.0f, 1.0f));					//blue color

		glBindVertexArray(vao_horizontal_line);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
	}	
}

void amp_ParallelVerticalLines(){
	glLineWidth(1.0f);

	for(GLfloat i = 1.0f; i > 0.0f; i = i - 0.02f){
		//for +x axis lines
		amp_VerticalLine(i, 0.0f, -1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), 1.0f);

		//for -x axis lines
		amp_VerticalLine(-i, 0.0f, -1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), 1.0f);
	}
}
