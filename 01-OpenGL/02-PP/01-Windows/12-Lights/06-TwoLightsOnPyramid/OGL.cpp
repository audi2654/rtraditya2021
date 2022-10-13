//Date: 31/07/2022
//RTR2021 OGL PP Two Wing Stand Lights on Spinning Pyramid with Per Vertex Lighting
//Press L, l to see effects

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

//vao & vbo variables for attributes
GLuint vao_pyramid;										//vertex array object for pyramid shape
GLuint vbo_pyramid_position;							//vertex buffer object for position
GLuint vbo_pyramid_normal;								//vertex buffer object for normals

//for animation 2D rotation
GLfloat anglePyramid = 0.0f;

//user defined uniform vars for MVP & different matrices in shaders
GLuint modelMatrixUniform;								//splitting single mvpMatrixUniform in 3 uniforms						
GLuint viewMatrixUniform;
GLuint projectionMatrixUniform;

//user defined uniform vars to do light calculations in shaders, array for 2 lights
GLuint laUniform[2];						//light ambient
GLuint ldUniform[2];						//light diffuse
GLuint lsUniform[2];						//light specular
GLuint lightPositionUniform[2];				//light position

GLuint kaUniform;							//material ambient
GLuint kdUniform;							//material diffuse
GLuint ksUniform;							//material specular
GLuint materialShininessUniform;			//material shininess

//var for toggling between on/off of light
GLuint lightingEnabledUniform;			//used in Shader
BOOL bLight = FALSE; 					//used in WNDPROC to handle case for 'L'

//vars for values to use in light calculation
//using struct to declare 4 components/values of a light
//& declaring array of struct for 2 lights with arrays/vectors of 4 values each to store ADSP 4 components
struct Light
{
	vmath::vec4 lightAmbient;
	vec4 lightDiffuse;
	vec4 lightSpecular;
	vec4 lightPosition;
} gsLightOne;

struct Light gsLightTwo;
Light gsLights[2];

//material is always for an object & here since object is 1 i.e pyramid, hence material is also 1
GLfloat gfMaterialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gfMaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfMaterialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfMaterialShininess = 50.0f;

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

		case 'L':
		case 'l':
			{
				if(bLight == FALSE)
				{
					bLight = TRUE;
				}
				else
				{
					bLight = FALSE;
				}
			}
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
	const GLchar* vertexShaderSourceCode =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec3 a_normal;" \
		"uniform mat4 u_modelMatrix;" \
		"uniform mat4 u_viewMatrix;" \
		"uniform mat4 u_projectionMatrix;" \
		"uniform vec3 u_la[2];" \
		"uniform vec3 u_ld[2];" \
		"uniform vec3 u_ls[2];" \
		"uniform vec4 u_lightPosition[2];" \
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
				"vec3 ambient[2];"	\
				"vec3 lightDirection[2];"	\
				"vec3 diffuse[2];"	\
				"vec3 reflectionVector[2];"	\
				"vec3 specular[2];"	\
				"for(int i = 0; i < 2; i++)" \
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

	//in this program we calculate whole light components in Vertex Shader hence this is Per Vertex Lighting

	//instead of glLightfv() & glMaterialfv() in FFP, we calculate whole light & material ADS components in PP through shaders using maths
	//phong_ads_light = AMBIENT + DIFFUSE + SPECULAR; 		//final light is summation of ADS
		//AMBIENT component is multiplication of 2 things : lightAmbient (u_la) & materialAmbient (u_kd)

		//DIFFUSE component is multiplication of 3 things : lightDiffuse (u_ld) & materialDiffuse (u_kd) & dot product of lightDirection & transformedNormals (S.N)
			//4 things are needed to be calculated in shader for diffuse light/component
				//1.eyeCoordinates -> for lightDirection (S), for viewerVector (to use in SPECULAR compo.)
				//2.normalMatrix -> for transformedNormals (N)
				//3.transformedNormals -> for reflectionVector (to use in SPECULAR compo.)
				//4.source lightDirection -> for reflectionVector (to use in SPECULAR compo.)

		//SPECULAR component is multiplication of 3 things : lightSpecular (u_ls) & materialSpecular (u_ks) & dot product of reflection & viewer vector in power of u_materialShininess
			//2 things are needed to be calculated in shader for specular light/component
				//1.reflectionVector
				//2.viewerVector

	//eyeCoordinates.xyz -> here we use swizzling to get 3 components out of x, y, z & w from a component based vector eyeCoordinates

	//during matrix multiplication order matters
	/* gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;*/
	//this order is very important wherever you use these matrices -> projection, view, model, position

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
		"in vec3 phong_ads_light;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
			"FragColor = vec4(phong_ads_light, 1.0);" \
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
	glBindAttribLocation(shaderProgramObject, AMP_ATTRIBUTE_NORMAL, "a_normal");

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
	modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_modelMatrix");				//viable place for andhar			
	viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_viewMatrix");
	projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_projectionMatrix");

	//retrieving uniformed locations of light ADS uniform vars
	//for light 0 - red light
	laUniform[0] = glGetUniformLocation(shaderProgramObject, "u_la[0]");							//light ambient
	ldUniform[0] = glGetUniformLocation(shaderProgramObject, "u_ld[0]");							//light diffuse
	lsUniform[0] = glGetUniformLocation(shaderProgramObject, "u_ls[0]");							//light specular
	lightPositionUniform[0] = glGetUniformLocation(shaderProgramObject, "u_lightPosition[0]");

	//for light 1 - blue light
	laUniform[1] = glGetUniformLocation(shaderProgramObject, "u_la[1]");							//light ambient
	ldUniform[1] = glGetUniformLocation(shaderProgramObject, "u_ld[1]");							//light diffuse
	lsUniform[1] = glGetUniformLocation(shaderProgramObject, "u_ls[1]");							//light specular
	lightPositionUniform[1] = glGetUniformLocation(shaderProgramObject, "u_lightPosition[1]");

	//retrieving uniformed locations of material ADS uniform vars
	kaUniform = glGetUniformLocation(shaderProgramObject, "u_ka");									//material ambient
	kdUniform = glGetUniformLocation(shaderProgramObject, "u_kd");									//material diffuse
	ksUniform = glGetUniformLocation(shaderProgramObject, "u_ks");									//material specular
	materialShininessUniform = glGetUniformLocation(shaderProgramObject, "u_materialShininess");

	//retrieving uniformed locations of var for toggling between on/off of light
	lightingEnabledUniform = glGetUniformLocation(shaderProgramObject, "u_lightingEnabled");

	//here starts OpenGL code
	//declaration of vertex data arrays
	const GLfloat pyramidPosition[] =
	{
		// front
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		// right
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

		// back
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		// left
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f
	};

	const GLfloat pyramidNormal[] =
	{
		0.0f, 0.447214f, 0.894427f,	// front-top
        0.0f, 0.447214f, 0.894427f,	// front-left
        0.0f, 0.447214f, 0.894427f,	// front-right

        0.894427f, 0.447214f, 0.0f, // right-top
        0.894427f, 0.447214f, 0.0f, // right-left
        0.894427f, 0.447214f, 0.0f, // right-right

        0.0f, 0.447214f, -0.894427f, // back-top
        0.0f, 0.447214f, -0.894427f, // back-left
        0.0f, 0.447214f, -0.894427f, // back-right

        -0.894427f, 0.447214f, 0.0f, // left-top
        -0.894427f, 0.447214f, 0.0f, // left-left
        -0.894427f, 0.447214f, 0.0f // left-right
	};

	//vao for PYRAMID
	glGenVertexArrays(1, &vao_pyramid);
	glBindVertexArray(vao_pyramid);
	
	//vbo for pyramid position
	glGenBuffers(1, &vbo_pyramid_position);															//here vbo returns with a memory mapped I/O address from GPU VRAM, i.e watching GPU memory(khidki) from CPU memory(khidki)
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pyramid_position);											//binding vbo to a target point of type of GL_ARRAY_BUFFER means, this vbo addr will hold array buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPosition), pyramidPosition, GL_STATIC_DRAW);		//putting pyramidPosition array in vbo in VRAM; GL_STATIC_DRAW means to fill buffer data now or on runtime, for runtime use GL_DYNAMIC_DRAW
	glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);					//this function tells the way & how to see the data stored in vbo
	glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);												//enabling the buffer array at position AMP_ATTRIBUTE_POSITION for further vertex processing
	glBindBuffer(GL_ARRAY_BUFFER, 0);																//unbinding vertex array buffer

	//vbo for pyramid color
	//here texture & color vbo is not needed we are drawing a plain simple geometry, 
	//we are sending white color to FragColor directly through fragment shader
	//but it is required for sphere with earth texture, etc

	//vbo for pyramid normal
	glGenBuffers(1, &vbo_pyramid_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pyramid_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidNormal), pyramidNormal, GL_STATIC_DRAW);
	glVertexAttribPointer(AMP_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(AMP_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);					//unbinding vertex array object vao for pyramid

	//clear the screen using black color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//light related changes
	//initializing ADSP values for 2 lights
	//light 0 - red light
	gsLights[0].lightAmbient = vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f);		//4th value 1.0f or 0.0f doesn't matter because here we don't consider blending
	gsLights[0].lightDiffuse = vec4(1.0f, 0.0f, 0.0f, 1.0f);			//red
	gsLights[0].lightSpecular = vec4(1.0f, 0.0f, 0.0f, 1.0f);			//red
	gsLights[0].lightPosition = vec4(-2.0f, 0.0f, 0.0f, 1.0f);			//4th value here tells type of light 1.0f for positional light & 0.0f for directional light

	//light 1 - blue light
	gsLights[1].lightAmbient = vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gsLights[1].lightDiffuse = vec4(0.0f, 0.0f, 1.0f, 1.0f);			//blue
	gsLights[1].lightSpecular = vec4(0.0f, 0.0f, 1.0f, 1.0f);			//blue
	gsLights[1].lightPosition = vec4(2.0f, 0.0f, 0.0f, 1.0f);

	//intializing perspective projection matrix
	perspectiveProjectionMatrix = mat4::identity();

	//warm up resize call
	resize(WIN_WIDTH - 16, WIN_HEIGHT - 39);

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
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	//use shadeProgramObject
	glUseProgram(shaderProgramObject);

	//PYRAMID
	//transformations related code
	//declaring TRS & MVP identity matrices
	mat4 translationMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();
	
	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	//initializing matrices with values or doing calculation
	translationMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	rotationMatrix = rotate(anglePyramid, 0.0f, 1.0f, 0.0f);
	
	modelMatrix = translationMatrix * rotationMatrix;		//here order of multiplication is very important & '*' is overloaded to multiply matrices in vmath.h

	//now passing/pushing above matrices with updated/calculated values to shader using uniform type variables
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

	for(int i = 0; i < 2; i++)
	{
		if(bLight == 1)
		{
			glUniform1i(lightingEnabledUniform, 1);

			//now passing/pushing arrays/vectors with updated/calculated values of LIGHT to shader using uniform type variables
			glUniform3fv(laUniform[i], 1, gsLights[i].lightAmbient);
			glUniform3fv(ldUniform[i], 1, gsLights[i].lightDiffuse);
			glUniform3fv(lsUniform[i], 1, gsLights[i].lightSpecular);
			glUniform1i(lightPositionUniform[i], gsLights[i].lightPosition);
		}
	}

	glBindVertexArray(vao_pyramid);
	glDrawArrays(GL_TRIANGLES, 0, 12); 			//1 triangle has 3 vertices, now pyramid has 4 sides each with 3 side, so 12
	glBindVertexArray(0);

	//unuse the shaderProgramObject
	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	//code - used in animation
	anglePyramid = anglePyramid + 1.0f;
	if (anglePyramid >= 360.f)
	{
		anglePyramid = anglePyramid - 360.0f;
	}
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
	if (vbo_pyramid_normal)
	{
		glDeleteBuffers(1, &vbo_pyramid_normal);
		vbo_pyramid_normal = 0;
	}

	if (vbo_pyramid_position)
	{
		glDeleteBuffers(1, &vbo_pyramid_position);
		vbo_pyramid_position = 0;
	}

	if (vao_pyramid)
	{
		glDeleteVertexArrays(1, &vao_pyramid);
		vao_pyramid = 0;
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
