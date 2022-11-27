//Date: 27/11/2022
//RTR2021 HPP OpenCL-OpenGL Interop SineWave Application

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

//OpenCL headers
#include <CL\opencl.h>                                                                              //single compulsory file for OpenCL
#include <C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.7\include\CL\cl.h>                 //optional - added on for intellisense
#include "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.7\include\CL\cl_platform.h"        //optional - added on for intellisense

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//OpenGL libraries
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "opencl.lib")			//OpenCL lib

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

GLuint vao;									//vertex array object
GLuint vbo;									//vertex buffer object
GLuint mvpMatrixUniform;					//Model View Projection Matrix Uniform

mat4 perspectiveProjectionMatrix;

//sine wave related variables
const unsigned int meshWidth = 1024;			//these 2 needs to be const so because pos array needs const size values below
const unsigned int meshHeight = 1024;

#define MY_ARRAY_SIZE meshWidth * meshHeight * 4

float pos[meshWidth][meshHeight][4];
GLuint vbo_gpu;

float animationTime = 0.0f;

bool onGPU = false;

//OpenCL variables
cl_int oclResult;

cl_mem graphicsResource = NULL;				//cl_mem is already internally a memory pointer

cl_context oclContext;
cl_command_queue oclCommandQueue;

cl_program oclProgram;
cl_kernel oclKernel;

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
		TEXT("AMP OpenCL-OGL Interop Sine Wave : Press C for CPU & G for GPU"),
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
		case 'C':
		case 'c':
			onGPU = false;
			break;

		case 'G':
		case 'g':
			onGPU = true;
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
	void uninitialize(void);
	void printGLInfo(void);
	
	//local variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	//OCL local vars
	cl_platform_id oclPlatformID;
	unsigned int dev_count = 0;
	cl_device_id* oclDeviceIDs = NULL;			//array
	cl_device_id oclDeviceID;

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

	//OpenCL initialization
	//step-1 : get OpenCL supporting GPU platform's IDs
	oclResult = clGetPlatformIDs(1, &oclPlatformID, NULL);					//platform can be any OpenCL supporting CPU , GPU, Accelerator boards platform
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clGetPlatformIDs() failed : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//step-2: get OpenCL supporting GPU device's ID from selected platform 'oclPlatformID'
	//a. get total GPU device count 'dev_count'
	oclResult = clGetDeviceIDs(oclPlatformID, CL_DEVICE_TYPE_GPU, 0, NULL, &dev_count);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clGetDeviceIDs() failed to get GPU device count: %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}
	else if (dev_count == 0)
	{
		fprintf(gpFile, "GPU device count is 0 : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//b. create memory for the array of device IDs 'oclDeviceIDs' to store device IDs of 'dev_count' number of GPU devices
	oclDeviceIDs = (cl_device_id*)malloc(sizeof(cl_device_id) * dev_count);
	if (oclDeviceIDs == NULL)
	{
		fprintf(gpFile, "malloc for oclDeviceIDs failed", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//c. fill the array of oclDeviceIDs with device IDs
	oclResult = clGetDeviceIDs(oclPlatformID, CL_DEVICE_TYPE_GPU, dev_count, oclDeviceIDs, NULL);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clGetDeviceIDs() failed : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//d. selecting the 0th supported device from oclDeviceIDs[] array of platform 'oclPlatformID'
	oclDeviceID = oclDeviceIDs[0];

	//e. free allocated memory for oclDeviceIDs[] array
	free(oclDeviceIDs);

	//step-3: create OpenCL compute context for selected 0th device
	//a. create context properties array
	cl_context_properties oclContextProperties[] =
	{
		CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),		/*internally this is cl_gl_sharing extension to enable interop*/
		CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)oclPlatformID,
		0
	};

	//b. create actual OpenCL compute context
	oclContext = clCreateContext(oclContextProperties, 1, &oclDeviceID, NULL, NULL, &oclResult);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clCreateContext() failed : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//step-4 : create command queue
	//if old graphics card & not supported to OpenCL 2.0, use clCreateCommandQueue()
	//for OpenCL 2.0, use clCreateCommandQueueWithProperties()
	oclCommandQueue = clCreateCommandQueueWithProperties(oclContext, oclDeviceID, 0, &oclResult);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clCreateCommandQueueWithProperties() failed : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//step-5 : create OpenCL program from openCL kernel source code .cl
	//a. write openCL kernel source code
	//OpenCL kernel function
	const char* oclSourceCode =
		"__kernel void sineWaveKernel(__global float4* position, unsigned int width, unsigned int height, float time)" \
		"{" \
			"unsigned int i = get_global_id(0);" \
			"unsigned int j = get_global_id(1);" \
			"float u = (float)i / (float)width;" \
			"float v = (float)j / (float)height;" \
			"u = u * 2.0f - 1.0f;" \
			"v = v * 2.0f - 1.0f;" \
			"float frequency = 4.0f;" \
			"float w = sin(u * frequency + time) * cos(v * frequency + time) * 0.5f;" \
			"position[j * width + i] = (float4)(u, w, v, 1.0f);" \
		"}";

	//b. create actual OpenCL program from above source code
	oclProgram = clCreateProgramWithSource(oclContext, 1, (const char**)&oclSourceCode, NULL, &oclResult);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clCreateProgramWithSource() failed : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//step-6 : build the above OpenCL program
	oclResult = clBuildProgram(oclProgram, 0, NULL, "-cl-fast-relaxed-math", NULL, NULL);
	if (oclResult != CL_SUCCESS)
	{
		size_t len;
		char buffer[2048];
		clGetProgramBuildInfo(oclProgram, oclDeviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		fprintf(gpFile, "Program build log on line %d : %s\n", __LINE__, buffer);
		fprintf(gpFile, "clBuildProgram() failed on line %d : %d \n", __LINE__, oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//step-7 : create OpenCL kernel by passing kernel function name that we used
	oclKernel = clCreateKernel(oclProgram, "sineWaveKernel", &oclResult);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clCreateKernel() failed : %d\n", oclResult);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//OpenCL initializing ends

	//step-8 : memory allocation for arrays on GPU device


	//prinf OpenGL information
	printGLInfo();

	//vertex shader code
	const GLchar* vertexShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"uniform mat4 u_mvpMatrix;" \
		"void main(void)" \
		"{" \
			"gl_Position = u_mvpMatrix * a_position;" \
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
	const GLchar* fragmentShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
			"FragColor = vec4(1.0, 0.5, 0.0, 1.0);" \
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

	//here starts OpenGL code
	//declaration of vertex data arrays
	//initialize pos var with 0.0f
	for (unsigned int i = 0; i < meshWidth; i++)
	{
		for (unsigned int j = 0; j < meshHeight; j++)
		{
			for (unsigned int k = 0; k < 4; k++)
			{
				pos[i][j][k] = 0.0f;
			}
		}
	}

	//vertex vao & vbo related code
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);		

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (MY_ARRAY_SIZE * sizeof(float)), NULL, GL_DYNAMIC_DRAW);
	//since we are dynamically drawing & giving position on runtime, we write below 2 lines in display
	//immediately after binding vao
	//glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);		//unbinding vertex array buffer

	//vbo on GPU
	glGenBuffers(1, &vbo_gpu);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_gpu);
	glBufferData(GL_ARRAY_BUFFER, (MY_ARRAY_SIZE * sizeof(float)), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);		//unbinding gpu vbo

	glBindVertexArray(0);					//unbinding vertex array object

	//create OpenCL-OpenGL Interoperability resource
	graphicsResource = clCreateFromGLBuffer(oclContext, CL_MEM_WRITE_ONLY, vbo_gpu, &oclResult);
	if (oclResult != CL_SUCCESS)
	{
		fprintf(gpFile, "clCreateFromGLBuffer() failed : %d on line %d \n ", oclResult, __LINE__);
		uninitialize();
		exit(EXIT_FAILURE);
	}

	//clear the screen using color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

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
	//func declarations
	void SineWave(unsigned int, unsigned int, float);
	void uninitialize(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//here actual clearing happens with color which was set in initialize(), framebuffer/colorbuffer in VRAM

	//use shadeProgramObject
	glUseProgram(shaderProgramObject);

	//transformations related code
	mat4 translationMatrix = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, 0.0f);	//glTranslatef() is replaced by this line
	modelViewMatrix = translationMatrix;
	modelViewProjectionMatrix = perspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(vao);		//binding here vao means running cassette & running all lines of vbo written in initialize() between bind & unbind of vao

	if (onGPU == true)
	{
		//openCL related code
		//step-1 : set openCL kernel arguments i.e position, width, height & time
		//set 0th argument of kernel i.e position (graphicsResource)
		oclResult = clSetKernelArg(oclKernel, 0, sizeof(cl_mem), (void*)&graphicsResource);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clSetKernelArg() failed for 0th arg : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//set 1st argument of kernel i.e width
		oclResult = clSetKernelArg(oclKernel, 1, sizeof(unsigned int), (void*)&meshWidth);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clSetKernelArg() failed for 1st arg : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//set 2nd argument of kernel i.e height
		oclResult = clSetKernelArg(oclKernel, 2, sizeof(unsigned int), (void*)&meshHeight);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clSetKernelArg() failed for 2nd arg : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//set 3rd argument of kernel i.e time
		oclResult = clSetKernelArg(oclKernel, 3, sizeof(float), (void*)&animationTime);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clSetKernelArg() failed for 3rd arg : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//step-2 - write above 4 input args to device memory by sending to pipe using created command queue
		//enqueue graphics resource into command queue
		oclResult = clEnqueueAcquireGLObjects(oclCommandQueue, 1, &graphicsResource, 0, NULL, NULL);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clEnqueueAcquireGLObjects() failed for graphicsResource : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//kernel configuration
		size_t globalWorkSize[2];	//1D 2 element operation

		//step-3 : run OpenCL kernel
		globalWorkSize[0] = meshWidth;
		globalWorkSize[1] = meshHeight;

		//in ND, N stands for n dimension or times, here we are doing meshWidth * meshHeight, so 2D workload
		oclResult = clEnqueueNDRangeKernel(oclCommandQueue, oclKernel, 2, NULL, globalWorkSize, NULL, 0, NULL, NULL);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clEnqueueNDRangeKernel() failed : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//step-4 : release graphics resource from kernel
		oclResult = clEnqueueReleaseGLObjects(oclCommandQueue, 1, &graphicsResource, 0, NULL, NULL);
		if (oclResult != CL_SUCCESS)
		{
			fprintf(gpFile, "clEnqueueReleaseGLObjects() failed for graphicsResource : %d on line %d \n ", oclResult, __LINE__);
			uninitialize();
			exit(EXIT_FAILURE);
		}

		//step-5 : finish OpenCL command queue
		clFinish(oclCommandQueue);

		//GPU vbo related code
		glBindBuffer(GL_ARRAY_BUFFER, vbo_gpu);
		//as OpenCL did all job internally no need of glBufferData(), glVertexAttribPointer(), glEnableVertexAttribArray() here
	}
	else
	{
		//cpu related code
		//initializing pos array & points
		SineWave(meshWidth, meshHeight, animationTime);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, MY_ARRAY_SIZE * sizeof(float), pos, GL_DYNAMIC_DRAW);
	}

	glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);

	//here there should be drawing code
	glDrawArrays(GL_POINTS, 0, meshWidth * meshHeight);

	glBindVertexArray(0);

	//unuse the shaderProgramObject
	glUseProgram(0);

	animationTime = animationTime + 0.01f;

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

	if (oclKernel)
	{
		clReleaseKernel(oclKernel);
		oclKernel = NULL;
	}

	if (oclProgram)
	{
		clReleaseProgram(oclProgram);
		oclProgram = NULL;
	}

	if (oclCommandQueue)
	{
		clReleaseCommandQueue(oclCommandQueue);
		oclCommandQueue = NULL;
	}

	if (oclContext)
	{
		clReleaseContext(oclContext);
		oclContext = NULL;
	}

	//deletion/uninitialization of vbo
	if (vbo_gpu)
	{
		//uninitialization cuda graphicsResource
		if (graphicsResource)
		{
			clReleaseMemObject(graphicsResource);
			graphicsResource = NULL;
		}
		glDeleteBuffers(1, &vbo_gpu);
		vbo_gpu = 0;
	}

	if (vbo)
	{
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	//deletion/uninitialization of vao
	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
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

void SineWave(unsigned int width, unsigned int height, float time)
{
	//code
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			for (unsigned int k = 0; k < 4; k++)
			{
				float u = (float)i / (float)width;
				float v = (float)j / (float)height;

				u = u * 2.0f - 1.0f;
				v = v * 2.0f - 1.0f;

				float frequency = 4.0f;
				float w = sinf(u * frequency + time) * cosf(v * frequency + time) * 0.5f;	//0.5f is for amplitude and wavelength adjustment

				//x,y,z,w of homogeneous coordinate system for sine wave postion
				if (k == 0)
					pos[i][j][k] = u;		//x

				if (k == 1)
					pos[i][j][k] = w;		//y

				if (k == 2)
					pos[i][j][k] = v;		//z

				if (k == 3)
					pos[i][j][k] = 1.0f;	//w
			}
		}
	}
}
