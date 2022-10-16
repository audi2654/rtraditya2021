//Date: 16/10/2022
//RTR2021 OGL PP Render To Texture using FBO Frame Buffer Object
//with Per Vertex Per Fragment Three Rotating Lights on Static Sphere Toggled
//Use l, L to toggle switch for light, F for Fragment & V for Vertex, Q for fullscreen

//header files
#include <windows.h>
#include <stdio.h>			//for file I/O functions
#include <stdlib.h>			//for exit()
#include "OGL.h"			//for icon
#include "Sphere.h"			//for sphere model

//OpenGL header files
#include <GL/glew.h>		//this must be included above gl.h file
#include <GL/gl.h>
#include "vmath.h"
using namespace vmath;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define FBO_WIDTH 512
#define FBO_HEIGHT 512

//OpenGL libraries
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "Sphere.lib")

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

//for render to texture
int winWidth;
int winHeight;

//PP related global vars
GLuint shaderProgramObject;

enum
{
	AMP_ATTRIBUTE_POSITION = 0,
	AMP_ATTRIBUTE_COLOR,
	AMP_ATTRIBUTE_NORMAL,
	AMP_ATTRIBUTE_TEXTURE0,
};

GLuint vao_cube;
GLuint vbo_cube_position;
GLuint vbo_cube_texcoord;

GLfloat angleCube;

GLuint mvpMatrixUniform;
GLuint textureSamplerUniform;

mat4 perspectiveProjectionMatrix_cube;

//FBO related variables
GLuint fbo;						//frame buffer object
GLuint rbo;						//render buffer object
GLuint fbo_texture;
bool bFboResult = false;

//texture scene global variables
//sphere vars
GLuint shaderProgramObject_pv_sphere;					//shader object for per vertex lighting
GLuint shaderProgramObject_pf_sphere;					//shader object for per fragment lighting

//sphere related variables
float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];
unsigned int gNumVertices_sphere;
unsigned int gNumElements_sphere = 0; 

//vao & vbo variables for attributes
GLuint vao_sphere;									//vertex array object for sphere
GLuint vbo_sphere_position;							//vertex buffer object for position
GLuint vbo_sphere_normal;							//vertex buffer object for normals
GLuint vbo_sphere_element;							//vertex buffer object for elements

//for light rotation
GLfloat gfAngleLight_sphere = 0.0f;

//user defined uniform vars for MVP & different matrices in shaders
GLuint modelMatrixUniform_sphere;								//splitting single mvpMatrixUniform in 3 uniforms						
GLuint viewMatrixUniform_sphere;
GLuint projectionMatrixUniform_sphere;

//user defined uniform vars to do light calculations in shaders, array for lights
GLuint laUniform_sphere[3];							//light ambient
GLuint ldUniform_sphere[3];							//light diffuse
GLuint lsUniform_sphere[3];							//light specular
GLuint lightPositionUniform_sphere[3];				//light position

GLuint kaUniform_sphere;							//material ambient
GLuint kdUniform_sphere;							//material diffuse
GLuint ksUniform_sphere;							//material specular
GLuint materialShininessUniform_sphere;				//material shininess

//var for toggling between on/off of light
GLuint lightingEnabledUniform_sphere;		//used in Shader
BOOL bLight = FALSE; 						//used in WNDPROC to handle case for 'L'
char chosenShader_sphere = 'v';

//vars for values to use in light calculation
//using struct to declare 4 components/values of a light
//& declaring array of struct for lights with arrays/vectors of 4 values each to store ADSP 4 components
struct Light
{
	vmath::vec4 lightAmbient;
	vec4 lightDiffuse;
	vec4 lightSpecular;
	vec4 lightPosition;
};

Light gsLights_sphere[3];

//material is always for an object & here since object is 1 i.e pyramid, hence material is also 1
GLfloat gfMaterialAmbient_sphere[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gfMaterialDiffuse_sphere[] = {1.0f, 1.0f, 1.0f, 1.0f};				//u_kd white color
GLfloat gfMaterialSpecular_sphere[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfMaterialShininess_sphere = 128.0f;

//albedo material
// GLfloat gfMaterialAmbient_sphere[] = {0.0f, 0.0f, 0.0f, 1.0f};
// GLfloat gfMaterialDiffuse_sphere[] = {0.5f, 0.2f, 0.7f, 1.0f};
// GLfloat gfMaterialSpecular_sphere[] = {0.7f, 0.7f, 0.7f, 1.0f};
// GLfloat gfMaterialShininess_sphere = 128.0f;

mat4 perspectiveProjectionMatrix_sphere;

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
		TEXT("AMP RTR PP - Render To Texture (FBO)"),
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
	else if (iRetVal == -6)
	{
		fprintf(gpFile, "createFBO() FAILED\n");
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
		{
			chosenShader_sphere = 'f';
		}
		break;

		case 'L':
		case 'l':
		{
			if (bLight == FALSE)
			{
				bLight = TRUE;
			}
			else
			{
				bLight = FALSE;
			}
		}
		break;

		case 'V':
		case 'v':
		{
			chosenShader_sphere = 'v';
		}
		break;

		case 'Q':
		case 'q':
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
	bool createFBO(GLint, GLint);
	int initialize_sphere(int, int);
	
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

	//vertex shader code
	const GLchar* vertexShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec2 a_texcoord;" \
		"uniform mat4 u_mvpMatrix;" \
		"out vec2 a_texcoord_out;" \
		"void main(void)" \
		"{" \
			"gl_Position = u_mvpMatrix * a_position;" \
			"a_texcoord_out = a_texcoord;" \
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
	//sampler2D is a datatype
	const GLchar* fragmentShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"in vec2 a_texcoord_out;" \
		"uniform sampler2D u_textureSampler;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
			"FragColor = texture(u_textureSampler, a_texcoord_out);" \
		"}";

	//texture return type is vec4
	//GLSL function texture() basically samples the colors from texture (textures & lights are nothing but a different kind of colors) 
	//which you gave by u_textureSampler textureSamplerUniform at location glGetUniformLocation on line 514 
	//& maps them on coordicates given by a_texcoord_out variable
	
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
	glBindAttribLocation(shaderProgramObject, AMP_ATTRIBUTE_TEXTURE0, "a_texcoord");

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
	textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "u_textureSampler");

	//here starts OpenGL code
	//declaration of vertex data arrays
	//ORDER of PCNT position, color, texcoord & normals for faces of shapes is important
	//i.e if in 1st array first 3 values are for front face then all 3 arrays should have first 3 values for front face

	const GLfloat cubePosition[] =
	{
		// top
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

        // bottom
        1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,

        // front
        1.0f, 1.0f, 1.0f,
       -1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        // back
        1.0f, 1.0f, -1.0f,
       -1.0f, 1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        // right
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,

        // left
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 
		-1.0f, -1.0f, -1.0f, 
		-1.0f, -1.0f, 1.0f
	};

	const GLfloat cubeTexcoords[] =
	{
		0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
	};

	//vao for CUBE
	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);

	//vbo for position
	glGenBuffers(1, &vbo_cube_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePosition), cubePosition, GL_STATIC_DRAW);
	glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//vbo for texture
	glGenBuffers(1, &vbo_cube_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTexcoords), cubeTexcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(AMP_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);		//2 is vec2 of textcoords
	glEnableVertexAttribArray(AMP_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);					//unbinding vertex array object vao for cube

	//clear the screen using color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//enabling the texture
	glEnable(GL_TEXTURE_2D);

	//intializing perspective projection matrix
	perspectiveProjectionMatrix_cube = mat4::identity();

	//warm up resize call
	resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);

	//FBO code for Render to Texture
	bFboResult = createFBO(FBO_WIDTH, FBO_HEIGHT);
	int iRetVal_sphere;
	if (bFboResult == true)
	{
		iRetVal_sphere = initialize_sphere(FBO_WIDTH, FBO_HEIGHT);
	}
	else
	{
		fprintf(gpFile, "bFboResult is returned as false : createFBO() FAILED\n");
		return(-6);
	}
	//add here error checking for initialize_sphere() like you do in WinMain() if any

	return(0);
}

void resize(int width, int height)
{
	//code
	winWidth = width;
	winHeight = height;

	if (height == 0)
		height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls

	glViewport(0, 0, GLsizei(width), GLsizei(height));

	perspectiveProjectionMatrix_cube = vmath::perspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
}

void resize_sphere(int width, int height)
{
	//code
	if (height == 0)
		height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls

	glViewport(0, 0, GLsizei(width), GLsizei(height));

	perspectiveProjectionMatrix_sphere = vmath::perspective(45.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
}

void display(void)
{
	//code
	//func prototype
	void display_sphere(GLint, GLint);
	void update_sphere(void);

	if (bFboResult == true)
	{
		display_sphere(FBO_WIDTH, FBO_HEIGHT);
		update_sphere();
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	resize(winWidth, winHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	//use shadeProgramObject
	glUseProgram(shaderProgramObject);

	//CUBE
	//transformations related code
	mat4 translationMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();
	mat4 rotationMatrix_x = mat4::identity();
	mat4 rotationMatrix_y = mat4::identity();
	mat4 rotationMatrix_z = mat4::identity();
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	translationMatrix = vmath::translate(0.0f, 0.0f, -5.0f);
	scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);
	rotationMatrix_x = vmath::rotate(angleCube, 1.0f, 0.0f, 0.0f);
	rotationMatrix_y = vmath::rotate(angleCube, 0.0f, 1.0f, 0.0f);
	rotationMatrix_z = vmath::rotate(angleCube, 0.0f, 0.0f, 1.0f);
	rotationMatrix = rotationMatrix_x * rotationMatrix_y * rotationMatrix_z;
	modelViewMatrix = translationMatrix * scaleMatrix * rotationMatrix;						//here order of multiplication is very important & '*' is overloaded to multiply matrices in vmath.h
	modelViewProjectionMatrix = perspectiveProjectionMatrix_cube * modelViewMatrix;

	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	//for texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glUniform1i(textureSamplerUniform, 0);			//0 here is for active texture GL_TEXTURE0

	glBindVertexArray(vao_cube);
	//1 call to glDrawArrays draw 1 square, for cube there are 6 different squares, so calling glDrawArrays 6 times
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);			//there are no QUADS in PP, every geometry has to made using GL_TRIANGLES or GL_TRIANGLES_FAN or GL_TRIANGLES_STRIP
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
	//above param numbers basically tells that consider cubePosition[] array to draw squares &
	//for 1st square, consider vertices position from 0th index of array till 4 next elements
	//for 2nd square, consider vertices position from 4th index of array till 4 next elements
	//for 3rd square, consider vertices position from 8th index of array till 4 next elements
	//& likewise for other square vertices positions, till 24 vertices of 6 square are covered
	//to form a cube
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);			//unbinding fbo_texture - optional

	//unuse the shaderProgramObject
	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	//code - used in animation
	angleCube = angleCube + 1.0f;
	if (angleCube >= 360.f)
	{
		angleCube = angleCube - 360.0f;
	}
}

void display_sphere(GLint texture_width, GLint texture_height)
{
	//code
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	resize_sphere(texture_width, texture_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//use shadeProgramObject
	if (chosenShader_sphere == 'v')
	{
		glUseProgram(shaderProgramObject_pv_sphere);
	}

	if (chosenShader_sphere == 'f')
	{
		glUseProgram(shaderProgramObject_pf_sphere);
	}

	//SPHERE
	//transformations related code
	//declaring TRS & MVP identity matrices
	mat4 translationMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	//initializing matrices with values or doing calculation
	translationMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
	rotationMatrix = rotate(gfAngleLight_sphere, 0.0f, 1.0f, 0.0f);

	modelMatrix = translationMatrix * rotationMatrix;		//here order of multiplication is very important & '*' is overloaded to multiply matrices in vmath.h

	//now passing/pushing above matrices with updated/calculated values to shader using uniform type variables
	glUniformMatrix4fv(modelMatrixUniform_sphere, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform_sphere, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform_sphere, 1, GL_FALSE, perspectiveProjectionMatrix_sphere);

	if (bLight == TRUE)
	{
		glUniform1i(lightingEnabledUniform_sphere, 1);

		for (int i = 0; i < 3; i++)
		{
			//now passing/pushing arrays/vectors with updated/calculated values of LIGHT to shader using uniform type variables
			glUniform3fv(laUniform_sphere[i], 1, gsLights_sphere[i].lightAmbient);
			glUniform3fv(ldUniform_sphere[i], 1, gsLights_sphere[i].lightDiffuse);
			glUniform3fv(lsUniform_sphere[i], 1, gsLights_sphere[i].lightSpecular);
			glUniform4fv(lightPositionUniform_sphere[i], 1, gsLights_sphere[i].lightPosition);
		}

		//now passing/pushing arrays/vectors with updated/calculated values of MATERIAL to shader using uniform type variables
		glUniform3fv(kaUniform_sphere, 1, gfMaterialAmbient_sphere);
		glUniform3fv(kdUniform_sphere, 1, gfMaterialDiffuse_sphere);
		glUniform3fv(ksUniform_sphere, 1, gfMaterialSpecular_sphere);
		glUniform1f(materialShininessUniform_sphere, gfMaterialShininess_sphere);
	}
	else
	{
		glUniform1i(lightingEnabledUniform_sphere, 0);
	}

	glBindVertexArray(vao_sphere);												//binding vao of sphere
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_sphere_element);					//binding vbo of sphere
	glDrawElements(GL_TRIANGLES, gNumElements_sphere, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);											//unbinding vbo of sphere
	glBindVertexArray(0);														//unbinding vao of sphere

	glUseProgram(0);															//unuse the shaderProgramObject

	//SwapBuffers(ghdc);		//this is not needed in display_sphere() swapbuffer already in host's display()
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void update_sphere(void)
{
	//code - used in animation
	gfAngleLight_sphere = gfAngleLight_sphere + 0.05f;
	if (gfAngleLight_sphere >= 360.f)
	{
		gfAngleLight_sphere = gfAngleLight_sphere - 360.0f;
	}

	/*gsLights_sphere[0].lightPosition = vec4(0.0f, sin(gfAngleLight_sphere), 0.0f, 1.0f);
	gsLights_sphere[1].lightPosition = vec4(0.0f, cos(gfAngleLight_sphere), 0.0f, 1.0f);
	gsLights_sphere[2].lightPosition = vec4(0.0f, -cos(gfAngleLight_sphere), 0.0f, 1.0f);*/

	gsLights_sphere[0].lightPosition = vec4(0.0f, sin(gfAngleLight_sphere), cos(gfAngleLight_sphere), 1.0f);
	gsLights_sphere[1].lightPosition = vec4(sin(gfAngleLight_sphere), 0.0f, cos(gfAngleLight_sphere), 1.0f);
	gsLights_sphere[2].lightPosition = vec4(sin(gfAngleLight_sphere), cos(gfAngleLight_sphere), 0.0f, 1.0f);
}

void uninitialize(void)
{
	//function declarations
	void ToggleFullScreen(void);
	void uninitialize_sphere(void);

	//code
	if (gbFullScreen)
	{
		ToggleFullScreen();		//window should not die in Fullscreen mode
	}

	//uninitializing everything of sphere
	uninitialize_sphere();

	//deletion/uninitialization of vbo
	if (vbo_cube_position)
	{
		glDeleteBuffers(1, &vbo_cube_position);
		vbo_cube_position = 0;
	}

	if(vbo_cube_texcoord)
	{
		glDeleteBuffers(1, &vbo_cube_texcoord);
		vbo_cube_texcoord = 0;
	}

	if (vao_cube)
	{
		glDeleteVertexArrays(1, &vao_cube);
		vao_cube = 0;
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
		wglMakeCurrent(NULL, NULL);		//this call with NULL,NULL tells that take away rendering charge from ghrc
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

void uninitialize_sphere(void)
{
	//function declarations
	void ToggleFullScreen(void);

	//code
	//deletion/uninitialization of vbo
	if (vbo_sphere_normal)
	{
		glDeleteBuffers(1, &vbo_sphere_normal);
		vbo_sphere_normal = 0;
	}

	if (vbo_sphere_position)
	{
		glDeleteBuffers(1, &vbo_sphere_position);
		vbo_sphere_position = 0;
	}

	if (vao_sphere)
	{
		glDeleteVertexArrays(1, &vao_sphere);
		vao_sphere = 0;
	}

	//shader uninitialization
	if (shaderProgramObject_pv_sphere)
	{
		glUseProgram(shaderProgramObject_pv_sphere);

		GLsizei numAttachedShaders = 0;
		glGetProgramiv(shaderProgramObject_pv_sphere, GL_ATTACHED_SHADERS, &numAttachedShaders);

		GLuint* shaderObjects = NULL;
		shaderObjects = (GLuint*)malloc(numAttachedShaders * sizeof(GLuint));

		glGetAttachedShaders(shaderProgramObject_pv_sphere, numAttachedShaders, &numAttachedShaders, shaderObjects);

		for (GLsizei i = 0; i < numAttachedShaders; i++)
		{
			glDetachShader(shaderProgramObject_pv_sphere, shaderObjects[i]);
			glDeleteShader(shaderObjects[i]);	//deleting shader obj from OGL memory
			shaderObjects[i] = 0;
		}

		free(shaderObjects);	//freeing malloc() memory
		shaderObjects = NULL;

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject_pv_sphere);
		shaderProgramObject_pv_sphere = 0;
	}

	if (shaderProgramObject_pf_sphere)
	{
		glUseProgram(shaderProgramObject_pf_sphere);

		GLsizei numAttachedShaders = 0;
		glGetProgramiv(shaderProgramObject_pf_sphere, GL_ATTACHED_SHADERS, &numAttachedShaders);

		GLuint* shaderObjects = NULL;
		shaderObjects = (GLuint*)malloc(numAttachedShaders * sizeof(GLuint));

		glGetAttachedShaders(shaderProgramObject_pf_sphere, numAttachedShaders, &numAttachedShaders, shaderObjects);

		for (GLsizei i = 0; i < numAttachedShaders; i++)
		{
			glDetachShader(shaderProgramObject_pf_sphere, shaderObjects[i]);
			glDeleteShader(shaderObjects[i]);	//deleting shader obj from OGL memory
			shaderObjects[i] = 0;
		}

		free(shaderObjects);	//freeing malloc() memory
		shaderObjects = NULL;

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject_pf_sphere);
		shaderProgramObject_pf_sphere = 0;
	}
}

//user defined func definition
//render to texture function
bool createFBO(GLint textureWidth, GLint textureHeight)
{
	//code
	//steps for render to texture
	//step-1 : check available renderbuffer size
	//var declaration
	int maxRenderbufferSize;

	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);

	if(maxRenderbufferSize < textureWidth || maxRenderbufferSize < textureHeight)
	{
		fprintf(gpFile, "Insufficient Renderbuffer Size\n");
		return(false);
	}

	//step-2 : create frame buffer object
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//step-3 : create render buffer object
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	//step-4 : state where to keep this render buffer & in which format
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, textureWidth, textureHeight);
	
	//in GL_DEPTH_COMPONENT16 parameter, depth has nothing to do here, but the only macro that 16 bit size format
	//has name this->GL_DEPTH_COMPONENT16, hence it is used here, other parameter that can be used
	//is GL_DEPTH_COMPONENT24 but on mobile only 16 bit size format works

	//step-5 : create empty texture to fill the target scene that has to be rendered
	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);	//empty full window texture

	//step-6 : give above texture to FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);

	//step-7 : now give RBO to FBO (important step listen audio for concept)
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	//step-8 : check if FBO is created successfully or not
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (result != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(gpFile, "Framebuffer is not Complete\n");
		return(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);  //when FBO gets unbind, internally the attached RBO & texture also gets unbind

	return(true);
}

//SPHERE code
int initialize_sphere(int width, int height)
{
	//function declarations
	void resize_sphere(int, int);
	void uninitialize_sphere(void);

	//PFD to glewInit() code removed because it is already above

	//vertex shader code for PER VERTEX Lighting
	const GLchar* vertexShaderSourceCode_pv_sphere =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec3 a_normal;" \
		"uniform mat4 u_modelMatrix;" \
		"uniform mat4 u_viewMatrix;" \
		"uniform mat4 u_projectionMatrix;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
		"uniform vec4 u_lightPosition[3];" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_materialShininess;" \
		"uniform int u_lightingEnabled;" \
		"out vec3 phong_ads_light;" \
		"void main(void)" \
		"{" \
		"if(u_lightingEnabled == 1)" \
		"{" \
		"vec4 eyeCoordinates = u_viewMatrix * u_modelMatrix * a_position;" \
		"mat3 normalMatrix = mat3(u_viewMatrix * u_modelMatrix);" \
		"vec3 transformedNormals = normalize(normalMatrix * a_normal);" \
		"vec3 viewerVector = normalize(-eyeCoordinates.xyz);" \
		"vec3 ambient[3];"	\
		"vec3 lightDirection[3];"	\
		"vec3 diffuse[3];"	\
		"vec3 reflectionVector[3];"	\
		"vec3 specular[3];"	\
		"for(int i = 0; i < 3; i++)" \
		"{" \
		"ambient[i] = u_la[i] * u_ka;" \
		"lightDirection[i] = normalize(vec3(u_lightPosition[i]) - eyeCoordinates.xyz);" \
		"diffuse[i] = u_ld[i] * u_kd * max(dot(lightDirection[i], transformedNormals), 0.0);" \
		"reflectionVector[i] = reflect(-lightDirection[i], transformedNormals);" \
		"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflectionVector[i], viewerVector), 0.0), u_materialShininess);" \
		"phong_ads_light = phong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
		"}" \
		"}" \
		"else" \
		"{" \
		"phong_ads_light = vec3(0.5f, 1.0, 1.0);" \
		"}" \
		"gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;" \
		"}";

	GLuint vertexShaderObject_pv_sphere = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderObject_pv_sphere, 1, (const GLchar**)&vertexShaderSourceCode_pv_sphere, NULL);

	glCompileShader(vertexShaderObject_pv_sphere);	//inline shader compiler

	//error checking for vertex shader
	GLint status = 0;
	GLint infoLogLength = 0;
	char* log = NULL;

	glGetShaderiv(vertexShaderObject_pv_sphere, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject_pv_sphere, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(vertexShaderObject_pv_sphere, infoLogLength, &written, log);
				fprintf(gpFile, "\nFor Sphere - Vertex Shader for PV Compilation Log: %s\n", log);
				free(log);
				uninitialize_sphere();
			}
		}
	}

	//fragment shader code for PER VERTEX Lighting
	const GLchar* fragmentShaderSourceCode_pv_sphere =
		"#version 460 core" \
		"\n" \
		"in vec3 phong_ads_light;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(phong_ads_light, 1.0);" \
		"}";

	GLuint fragmentShaderObject_pv_sphere = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderObject_pv_sphere, 1, (const GLchar**)&fragmentShaderSourceCode_pv_sphere, NULL);

	glCompileShader(fragmentShaderObject_pv_sphere);	//inline shader compiler

	//error checking for fragment shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(fragmentShaderObject_pv_sphere, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject_pv_sphere, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(fragmentShaderObject_pv_sphere, infoLogLength, &written, log);
				fprintf(gpFile, "\nFor Sphere - Fragment Shader for PV Light Compilation Log: %s\n", log);
				free(log);
				uninitialize_sphere();
			}
		}
	}

	//vertex shader code for PER FRAGMENT Lighting
	const GLchar* vertexShaderSourceCode_pf_sphere =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec3 a_normal;" \
		"uniform mat4 u_modelMatrix;" \
		"uniform mat4 u_viewMatrix;" \
		"uniform mat4 u_projectionMatrix;" \
		"uniform vec4 u_lightPosition[3];" \
		"uniform int u_lightingEnabled;" \
		"out vec3 transformedNormal;" \
		"out vec3 lightDirection[3];" \
		"out vec3 viewerVector;" \
		"void main(void)" \
		"{" \
		"if(u_lightingEnabled == 1)" \
		"{" \
		"vec4 eyeCoordinates = u_viewMatrix * u_modelMatrix * a_position;" \
		"mat3 normalMatrix = mat3(u_viewMatrix * u_modelMatrix);" \
		"transformedNormal = normalMatrix * a_normal;" \
		"viewerVector = (-eyeCoordinates.xyz);" \
		"for(int i = 0; i < 3; i++)" \
		"{" \
		"lightDirection[i] = vec3(u_lightPosition[i]) - eyeCoordinates.xyz;" \
		"}" \
		"}" \
		"gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;" \
		"}";

	GLuint vertexShaderObject_pf_sphere = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderObject_pf_sphere, 1, (const GLchar**)&vertexShaderSourceCode_pf_sphere, NULL);

	glCompileShader(vertexShaderObject_pf_sphere);	//inline shader compiler

	//error checking for vertex shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(vertexShaderObject_pf_sphere, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject_pf_sphere, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(vertexShaderObject_pf_sphere, infoLogLength, &written, log);
				fprintf(gpFile, "\nFor Sphere - Vertex Shader for PF Light Compilation Log: %s\n", log);
				free(log);
				uninitialize_sphere();
			}
		}
	}

	//fragment shader code for PER FRAGMENT Lighting
	const GLchar* fragmentShaderSourceCode_pf_sphere =
		"#version 460 core" \
		"\n" \
		"in vec3 transformedNormal;" \
		"in vec3 lightDirection[3];" \
		"in vec3 viewerVector;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_materialShininess;" \
		"uniform int u_lightingEnabled;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"vec3 phong_ads_light;" \
		"if(u_lightingEnabled == 1)" \
		"{" \
		"vec3 normalized_transformed_normal = normalize(transformedNormal);" \
		"vec3 normalized_viewer_vector = normalize(viewerVector);" \
		"vec3 ambient[3];" \
		"vec3 normalized_light_direction[3];" \
		"vec3 diffuse[3];" \
		"vec3 reflectionVector[3];" \
		"vec3 specular[3];" \
		"for(int i = 0; i < 3; i++)" \
		"{" \
		"ambient[i] = u_la[i] * u_ka;" \
		"normalized_light_direction[i] = normalize(lightDirection[i]);" \
		"diffuse[i] = u_ld[i] * u_kd * max(dot(normalized_light_direction[i], normalized_transformed_normal), 0.0);" \
		"reflectionVector[i] = reflect(-normalized_light_direction[i], normalized_transformed_normal);" \
		"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflectionVector[i], normalized_viewer_vector), 0.0), u_materialShininess);" \
		"phong_ads_light = phong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
		"}" \
		"}" \
		"else" \
		"{" \
		"phong_ads_light = vec3(0.5f, 1.0, 1.0);" \
		"}" \
		"FragColor = vec4(phong_ads_light, 1.0);" \
		"}";

	GLuint fragmentShaderObject_pf_sphere = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderObject_pf_sphere, 1, (const GLchar**)&fragmentShaderSourceCode_pf_sphere, NULL);

	glCompileShader(fragmentShaderObject_pf_sphere);	//inline shader compiler

	//error checking for fragment shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(fragmentShaderObject_pf_sphere, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject_pf_sphere, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(fragmentShaderObject_pf_sphere, infoLogLength, &written, log);
				fprintf(gpFile, "\nFor Sphere - Fragment Shader for PF Light Compilation Log: %s\n", log);
				free(log);
				uninitialize_sphere();
			}
		}
	}

	//attaching shaderObject with shaders of PER VERTEX Lighting
	shaderProgramObject_pv_sphere = glCreateProgram();
	glAttachShader(shaderProgramObject_pv_sphere, vertexShaderObject_pv_sphere);
	glAttachShader(shaderProgramObject_pv_sphere, fragmentShaderObject_pv_sphere);

	//attaching shaderObject with shaders of PER FRAGMENT Lighting
	shaderProgramObject_pf_sphere = glCreateProgram();
	glAttachShader(shaderProgramObject_pf_sphere, vertexShaderObject_pf_sphere);
	glAttachShader(shaderProgramObject_pf_sphere, fragmentShaderObject_pf_sphere);

	//prelinking & binding of shader program object with vertex attributes for PER VERTEX Lighting
	glBindAttribLocation(shaderProgramObject_pv_sphere, AMP_ATTRIBUTE_POSITION, "a_position");			//viable place for andhar
	glBindAttribLocation(shaderProgramObject_pv_sphere, AMP_ATTRIBUTE_NORMAL, "a_normal");

	//prelinking & binding of shader program object with vertex attributes for PER FRAGMENT Lighting
	glBindAttribLocation(shaderProgramObject_pf_sphere, AMP_ATTRIBUTE_POSITION, "a_position");			//viable place for andhar
	glBindAttribLocation(shaderProgramObject_pf_sphere, AMP_ATTRIBUTE_NORMAL, "a_normal");

	glLinkProgram(shaderProgramObject_pv_sphere);			//inline shader linker
	glLinkProgram(shaderProgramObject_pf_sphere);			//inline shader linker

	//error checking for shader program for PER VERTEX Lighting
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetProgramiv(shaderProgramObject_pv_sphere, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject_pv_sphere, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(shaderProgramObject_pv_sphere, infoLogLength, &written, log);
				fprintf(gpFile, "\nFor Sphere - Shader Program Compilation for PER VERTEX Light Log: %s\n", log);
				free(log);
				uninitialize_sphere();
			}
		}
	}

	//error checking for shader program for PER FRAGMENT Lighting
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetProgramiv(shaderProgramObject_pf_sphere, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject_pf_sphere, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(shaderProgramObject_pf_sphere, infoLogLength, &written, log);
				fprintf(gpFile, "\nFor Sphere - Shader Program Compilation for PER FRAGMENT Light Log: %s\n", log);
				free(log);
				uninitialize_sphere();
			}
		}
	}

	//For PER VERTEX Lighting
	//post linking retrieving uniformed locations of user defined uniform type variables from shaderProgramObject
	modelMatrixUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_modelMatrix");				//viable place for andhar			
	viewMatrixUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_viewMatrix");
	projectionMatrixUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_projectionMatrix");

	//retrieving uniformed locations of light ADS uniform vars
	//for light 0 - red light
	laUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_la[0]");						//light ambient
	ldUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ld[0]");						//light diffuse
	lsUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ls[0]");						//light specular
	lightPositionUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_lightPosition[0]");

	//for light 1 - green light
	laUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_la[1]");						//light ambient
	ldUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ld[1]");						//light diffuse
	lsUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ls[1]");						//light specular
	lightPositionUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_lightPosition[1]");

	//for light 2 - blue light
	laUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_la[2]");						//light ambient
	ldUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ld[2]");						//light diffuse
	lsUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ls[2]");						//light specular
	lightPositionUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_lightPosition[2]");

	//retrieving uniformed locations of material ADS uniform vars
	kaUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ka");								//material ambient
	kdUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_kd");								//material diffuse
	ksUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_ks");								//material specular
	materialShininessUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_materialShininess");

	//retrieving uniformed locations of var for toggling between on/off of light
	lightingEnabledUniform_sphere = glGetUniformLocation(shaderProgramObject_pv_sphere, "u_lightingEnabled");

	//For PER FRAGMENT Lighting
	//post linking retrieving uniformed locations of user defined uniform type variables from shaderProgramObject
	modelMatrixUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_modelMatrix");				//viable place for andhar			
	viewMatrixUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_viewMatrix");
	projectionMatrixUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_projectionMatrix");

	//for light 0 - red light
	laUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_la[0]");						//light ambient
	ldUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ld[0]");						//light diffuse
	lsUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ls[0]");						//light specular
	lightPositionUniform_sphere[0] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_lightPosition[0]");

	//for light 1 - green light
	laUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_la[1]");						//light ambient
	ldUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ld[1]");						//light diffuse
	lsUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ls[1]");						//light specular
	lightPositionUniform_sphere[1] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_lightPosition[1]");

	//for light 2 - blue light
	laUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_la[2]");						//light ambient
	ldUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ld[2]");						//light diffuse
	lsUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ls[2]");						//light specular
	lightPositionUniform_sphere[2] = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_lightPosition[2]");

	//retrieving uniformed locations of material ADS uniform vars
	kaUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ka");						//material ambient
	kdUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_kd");						//material diffuse
	ksUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_ks");						//material specular
	materialShininessUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_materialShininess");

	//retrieving uniformed locations of var for toggling between on/off of light
	lightingEnabledUniform_sphere = glGetUniformLocation(shaderProgramObject_pf_sphere, "u_lightingEnabled");

	//here starts OpenGL code
	//declaration of vertex data arrays
	//ORDER of position, texcoord & normals for faces of shapes is important
	//i.e if in 1st array first 3 values are for front face then all 3 arrays should have first 3 values for front face

	getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
	gNumVertices_sphere = getNumberOfSphereVertices();
	gNumElements_sphere = getNumberOfSphereElements();

	//vao for sphere
	glGenVertexArrays(1, &vao_sphere);
	glBindVertexArray(vao_sphere);				//binding sphere vao	

	//vbo for sphere position vertices
	glGenBuffers(1, &vbo_sphere_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//vbo for sphere normals
	glGenBuffers(1, &vbo_sphere_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(AMP_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMP_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//vbo for sphere elements
	glGenBuffers(1, &vbo_sphere_element);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_sphere_element);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//the enum AMP_ATTRIBUTE_ELEMENT for element's vbo is not needed

	glBindVertexArray(0);					//unbinding vertex array object vao for pyramid

	//clear the screen using black color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//light related changes
	//initializing ADSP values
	//light 0 - red light
	gsLights_sphere[0].lightAmbient = vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f);		//4th value 1.0f or 0.0f doesn't matter because here we don't consider blending
	gsLights_sphere[0].lightDiffuse = vec4(1.0f, 0.0f, 0.0f, 1.0f);				//red
	gsLights_sphere[0].lightSpecular = vec4(1.0f, 0.0f, 0.0f, 1.0f);			//red
	gsLights_sphere[0].lightPosition = vec4(0.0f, 2.0f, 0.0f, 1.0f);			//4th value here tells type of light 1.0f for positional light & 0.0f for directional light

	//light 1 - green light
	gsLights_sphere[1].lightAmbient = vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gsLights_sphere[1].lightDiffuse = vec4(0.0f, 1.0f, 0.0f, 1.0f);				//green
	gsLights_sphere[1].lightSpecular = vec4(0.0f, 1.0f, 0.0f, 1.0f);			//green
	gsLights_sphere[1].lightPosition = vec4(-2.0f, 0.0f, 0.0f, 1.0f);

	//light 2 - blue light
	gsLights_sphere[2].lightAmbient = vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gsLights_sphere[2].lightDiffuse = vec4(0.0f, 0.0f, 1.0f, 1.0f);				//blue
	gsLights_sphere[2].lightSpecular = vec4(0.0f, 0.0f, 1.0f, 1.0f);			//blue
	gsLights_sphere[2].lightPosition = vec4(2.0f, 0.0f, 0.0f, 1.0f);

	//intializing perspective projection matrix
	perspectiveProjectionMatrix_sphere = mat4::identity();

	//warm up resize call
	resize_sphere(FBO_WIDTH, FBO_HEIGHT);		//check for 16 & 39

	return(0);
}
