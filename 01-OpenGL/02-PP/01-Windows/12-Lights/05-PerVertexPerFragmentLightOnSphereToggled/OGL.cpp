//Date: 31/07/2022
//RTR2021 OGL PP Per Vertex Per Fragment Lighting on Static Sphere Toggled
//using Phong ADS Lighting Model (ADS - Ambient Diffuse Specular)
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

//PP related global vars
GLuint shaderProgramObject_pv;					//shader object for per vertex lighting
GLuint shaderProgramObject_pf;					//shader object for per fragment lighting

enum
{
	AMP_ATTRIBUTE_POSITION = 0,
	AMP_ATTRIBUTE_NORMAL,
	AMP_ATTRIBUTE_TEXTURE0,
	AMP_ATTRIBUTE_ELEMENT
};

//sphere related variables
float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];
unsigned int gNumVertices;
unsigned int gNumElements = 0; 

//vao & vbo variables for attributes
GLuint vao_sphere;									//vertex array object for sphere
GLuint vbo_sphere_position;							//vertex buffer object for position
GLuint vbo_sphere_normal;							//vertex buffer object for normals
GLuint vbo_sphere_element;							//vertex buffer object for elements

//user defined uniform vars for MVP & different matrices in shaders
GLuint modelMatrixUniform;							//splitting single mvpMatrixUniform in 3 different uniforms 
GLuint viewMatrixUniform;
GLuint projectionMatrixUniform;

//user defined uniform vars to do light calculations in shaders
GLuint laUniform;						//light ambient
GLuint ldUniform;						//light diffuse
GLuint lsUniform;						//light specular
GLuint lightPositionUniform;			//light position

GLuint kaUniform;						//material ambient
GLuint kdUniform;						//material diffuse
GLuint ksUniform;						//material specular
GLuint materialShininessUniform;		//material shinines

//var for toggling between on/off of light
GLuint lightingEnabledUniform;			//used in Shader
BOOL bLight = FALSE; 					//used in WNDPROC to handle case for 'L'
char chosenShader = 'v';

//vars for values to use in light calculation (values taken from Gouraud Shading on Sphere FFP program)
//black & white
// GLfloat gfLightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
// GLfloat gfLightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
// GLfloat gfLightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
// GLfloat gfLightPosition[] = {100.0f, 100.0f, 100.0f, 1.0f};

// GLfloat gfMaterialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
// GLfloat gfMaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
// GLfloat gfMaterialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
// GLfloat gfMaterialShininess = 50.0f;

//albedo
GLfloat gfLightAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat gfLightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfLightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfLightPosition[] = {100.0f, 100.0f, 100.0f, 1.0f};			//change light position

GLfloat gfMaterialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gfMaterialDiffuse[] = {0.5f, 0.2f, 0.7f, 1.0f};
GLfloat gfMaterialSpecular[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat gfMaterialShininess = 128.0f;

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
		TEXT("AMP OGL PP - Per Vertex Per Fragment Phong Lighting Toggled - Use L,F,V keypress"),
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
			{
				chosenShader = 'f';
			}
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

		case 'V':
		case 'v':
			{
				chosenShader = 'v';
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

	//vertex shader code for PER VERTEX Lighting
	const GLchar* vertexShaderSourceCode_pv =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec3 a_normal;" \
		"uniform mat4 u_modelMatrix;" \
		"uniform mat4 u_viewMatrix;" \
		"uniform mat4 u_projectionMatrix;" \
		"uniform vec3 u_la;" \
		"uniform vec3 u_ld;" \
		"uniform vec3 u_ls;" \
		"uniform vec4 u_lightPosition;" \
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
				"vec3 ambient = u_la * u_ka;" \
				"vec4 eyeCoordinates = u_viewMatrix * u_modelMatrix * a_position;" \
				"mat3 normalMatrix = mat3(u_viewMatrix * u_modelMatrix);" \
				"vec3 transformedNormals = normalize(normalMatrix * a_normal);" \
				"vec3 lightDirection = normalize(vec3(u_lightPosition) - eyeCoordinates.xyz);" \
				"vec3 diffuse = u_ld * u_kd * max(dot(lightDirection, transformedNormals), 0.0);" \
				"vec3 reflectionVector = reflect(-lightDirection, transformedNormals);" \
				"vec3 viewerVector = normalize(-eyeCoordinates.xyz);" \
				"vec3 specular = u_ls * u_ks * pow(max(dot(reflectionVector, viewerVector), 0.0), u_materialShininess);" \
				"phong_ads_light = ambient + diffuse + specular;" \
			"}" \
			"else" \
			"{" \
				"phong_ads_light = vec3(1.0f, 1.0, 1.0);" \
			"}" \
			"gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;" \
		"}";

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

	GLuint vertexShaderObject_pv = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderObject_pv, 1, (const GLchar**)&vertexShaderSourceCode_pv, NULL);

	glCompileShader(vertexShaderObject_pv);	//inline shader compiler

	//error checking for vertex shader
	GLint status = 0;
	GLint infoLogLength = 0;
	char* log = NULL;

	glGetShaderiv(vertexShaderObject_pv, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject_pv, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(vertexShaderObject_pv, infoLogLength, &written, log);
				fprintf(gpFile, "\nVertex Shader for PV Light Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//fragment shader code for PER VERTEX Lighting
	const GLchar* fragmentShaderSourceCode_pv =
		"#version 460 core" \
		"\n" \
		"in vec3 phong_ads_light;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
			"FragColor = vec4(phong_ads_light, 1.0);" \
		"}";
	
	GLuint fragmentShaderObject_pv = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderObject_pv, 1, (const GLchar**)&fragmentShaderSourceCode_pv, NULL);

	glCompileShader(fragmentShaderObject_pv);	//inline shader compiler

	//error checking for fragment shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(fragmentShaderObject_pv, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject_pv, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(fragmentShaderObject_pv, infoLogLength, &written, log);
				fprintf(gpFile, "\nFragment Shader for PV Light Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//vertex shader code for PER FRAGMENT Lighting
	const GLchar* vertexShaderSourceCode_pf =
		"#version 460 core" \
		"\n" \
		"in vec4 a_position;" \
		"in vec3 a_normal;" \
		"uniform mat4 u_modelMatrix;" \
		"uniform mat4 u_viewMatrix;" \
		"uniform mat4 u_projectionMatrix;" \
		"uniform vec4 u_lightPosition;" \
		"uniform int u_lightingEnabled;" \
		"out vec3 transformedNormal;" \
		"out vec3 lightDirection;" \
		"out vec3 viewerVector;" \
		"void main(void)" \
		"{" \
			"if(u_lightingEnabled == 1)" \
			"{" \
				"vec4 eyeCoordinates = u_viewMatrix * u_modelMatrix * a_position;" \
				"mat3 normalMatrix = mat3(u_viewMatrix * u_modelMatrix);" \
				"transformedNormal = normalMatrix * a_normal;" \
				"lightDirection = vec3(u_lightPosition) - eyeCoordinates.xyz;" \
				"viewerVector = (-eyeCoordinates.xyz);" \
			"}" \
			"gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;" \
		"}";

	GLuint vertexShaderObject_pf = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderObject_pf, 1, (const GLchar**)&vertexShaderSourceCode_pf, NULL);

	glCompileShader(vertexShaderObject_pf);	//inline shader compiler

	//error checking for vertex shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(vertexShaderObject_pf, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(vertexShaderObject_pf, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(vertexShaderObject_pf, infoLogLength, &written, log);
				fprintf(gpFile, "\nVertex Shader for PF Light Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//fragment shader code for PER FRAGMENT Lighting
	const GLchar* fragmentShaderSourceCode_pf =
		"#version 460 core" \
		"\n" \
		"in vec3 transformedNormal;" \
		"in vec3 lightDirection;" \
		"in vec3 viewerVector;" \
		"uniform vec3 u_la;" \
		"uniform vec3 u_ld;" \
		"uniform vec3 u_ls;" \
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
				"vec3 ambient = u_la * u_ka;" \
				"vec3 normalized_transformed_normal = normalize(transformedNormal);" \
				"vec3 normalized_light_direction = normalize(lightDirection);" \
				"vec3 diffuse = u_ld * u_kd * max(dot(normalized_light_direction, normalized_transformed_normal), 0.0);" \
				"vec3 reflectionVector = reflect(-normalized_light_direction, normalized_transformed_normal);" \
				"vec3 normalized_viewer_vector = normalize(viewerVector);" \
				"vec3 specular = u_ls * u_ks * pow(max(dot(reflectionVector, normalized_viewer_vector), 0.0), u_materialShininess);" \
				"phong_ads_light = ambient + diffuse + specular;" \
			"}" \
			"else" \
			"{" \
				"phong_ads_light = vec3(0.5f, 1.0, 1.0);" \
			"}" \
			"FragColor = vec4(phong_ads_light, 1.0);" \
		"}";
	
	GLuint fragmentShaderObject_pf = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderObject_pf, 1, (const GLchar**)&fragmentShaderSourceCode_pf, NULL);

	glCompileShader(fragmentShaderObject_pf);	//inline shader compiler

	//error checking for fragment shader
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetShaderiv(fragmentShaderObject_pf, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(fragmentShaderObject_pf, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(fragmentShaderObject_pf, infoLogLength, &written, log);
				fprintf(gpFile, "\nFragment Shader for PF Light Compilation Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//attaching shaderObject with shaders of PER VERTEX Lighting
	shaderProgramObject_pv = glCreateProgram();
	glAttachShader(shaderProgramObject_pv, vertexShaderObject_pv);
	glAttachShader(shaderProgramObject_pv, fragmentShaderObject_pv);

	//attaching shaderObject with shaders of PER FRAGMENT Lighting
	shaderProgramObject_pf = glCreateProgram();
	glAttachShader(shaderProgramObject_pf, vertexShaderObject_pf);
	glAttachShader(shaderProgramObject_pf, fragmentShaderObject_pf);

	//prelinking & binding of shader program object with vertex attributes for PER VERTEX Lighting
	glBindAttribLocation(shaderProgramObject_pv, AMP_ATTRIBUTE_POSITION, "a_position");			//viable place for andhar
	glBindAttribLocation(shaderProgramObject_pv, AMP_ATTRIBUTE_NORMAL, "a_normal");

	//prelinking & binding of shader program object with vertex attributes for PER FRAGMENT Lighting
	glBindAttribLocation(shaderProgramObject_pf, AMP_ATTRIBUTE_POSITION, "a_position");			//viable place for andhar
	glBindAttribLocation(shaderProgramObject_pf, AMP_ATTRIBUTE_NORMAL, "a_normal");

	glLinkProgram(shaderProgramObject_pv);			//inline shader linker
	glLinkProgram(shaderProgramObject_pf);			//inline shader linker

	//error checking for shader program for PER VERTEX Lighting
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetProgramiv(shaderProgramObject_pv, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject_pv, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(shaderProgramObject_pv, infoLogLength, &written, log);
				fprintf(gpFile, "\nShader Program Compilation for PER VERTEX Light Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//error checking for shader program for PER FRAGMENT Lighting
	status = 0;
	infoLogLength = 0;
	log = NULL;

	glGetProgramiv(shaderProgramObject_pf, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetProgramiv(shaderProgramObject_pf, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			log = (char*)malloc(infoLogLength);
			if (log != NULL)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(shaderProgramObject_pf, infoLogLength, &written, log);
				fprintf(gpFile, "\nShader Program Compilation for PER FRAGMENT Light Log: %s\n", log);
				free(log);
				uninitialize();
			}
		}
	}

	//For PER VERTEX Lighting
	//post linking retrieving uniformed locations of user defined uniform type variables from shaderProgramObject
		modelMatrixUniform = glGetUniformLocation(shaderProgramObject_pv, "u_modelMatrix");				//viable place for andhar			
		viewMatrixUniform = glGetUniformLocation(shaderProgramObject_pv, "u_viewMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgramObject_pv, "u_projectionMatrix");

		//retrieving uniformed locations of light ADS uniform vars
		laUniform = glGetUniformLocation(shaderProgramObject_pv, "u_la");						//light ambient
		ldUniform = glGetUniformLocation(shaderProgramObject_pv, "u_ld");						//light diffuse
		lsUniform = glGetUniformLocation(shaderProgramObject_pv, "u_ls");						//light specular
		lightPositionUniform = glGetUniformLocation(shaderProgramObject_pv, "u_lightPosition");

		//retrieving uniformed locations of material ADS uniform vars
		kaUniform = glGetUniformLocation(shaderProgramObject_pv, "u_ka");						//material ambient
		kdUniform = glGetUniformLocation(shaderProgramObject_pv, "u_kd");						//material diffuse
		ksUniform = glGetUniformLocation(shaderProgramObject_pv, "u_ks");						//material specular
		materialShininessUniform = glGetUniformLocation(shaderProgramObject_pv, "u_materialShininess");

		//retrieving uniformed locations of var for toggling between on/off of light
		lightingEnabledUniform = glGetUniformLocation(shaderProgramObject_pv, "u_lightingEnabled");

	//For PER FRAGMENT Lighting
	//post linking retrieving uniformed locations of user defined uniform type variables from shaderProgramObject
		modelMatrixUniform = glGetUniformLocation(shaderProgramObject_pf, "u_modelMatrix");				//viable place for andhar			
		viewMatrixUniform = glGetUniformLocation(shaderProgramObject_pf, "u_viewMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgramObject_pf, "u_projectionMatrix");

		//retrieving uniformed locations of light ADS uniform vars
		laUniform = glGetUniformLocation(shaderProgramObject_pf, "u_la");						//light ambient
		ldUniform = glGetUniformLocation(shaderProgramObject_pf, "u_ld");						//light diffuse
		lsUniform = glGetUniformLocation(shaderProgramObject_pf, "u_ls");						//light specular
		lightPositionUniform = glGetUniformLocation(shaderProgramObject_pf, "u_lightPosition");

		//retrieving uniformed locations of material ADS uniform vars
		kaUniform = glGetUniformLocation(shaderProgramObject_pf, "u_ka");						//material ambient
		kdUniform = glGetUniformLocation(shaderProgramObject_pf, "u_kd");						//material diffuse
		ksUniform = glGetUniformLocation(shaderProgramObject_pf, "u_ks");						//material specular
		materialShininessUniform = glGetUniformLocation(shaderProgramObject_pf, "u_materialShininess");

		//retrieving uniformed locations of var for toggling between on/off of light
		lightingEnabledUniform = glGetUniformLocation(shaderProgramObject_pf, "u_lightingEnabled");

	//here starts OpenGL code
	//declaration of vertex data arrays
	//ORDER of position, texcoord & normals for faces of shapes is important
	//i.e if in 1st array first 3 values are for front face then all 3 arrays should have first 3 values for front face

	getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
	gNumVertices = getNumberOfSphereVertices();
	gNumElements = getNumberOfSphereElements();

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

	//vbo for sphere texture & color
	//here texture & color vbo is not needed we are drawing a plain simple sphere, 
	//but it is required for sphere with earth texture, etc

	glBindVertexArray(0);					//unbinding sphere vao

	//clear the screen using black color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//here actual clearing happens with color which was set in initialize(), framebuffer/colorbuffer in VRAM

	//use shadeProgramObject
	if(chosenShader == 'v')
	{
		glUseProgram(shaderProgramObject_pv);
	}

	if(chosenShader == 'f')
	{
		glUseProgram(shaderProgramObject_pf);
	}

	//SPHERE
	//transformations related code
	//declaring TRS & MVP identity matrices as per requirement
	mat4 translationMatrix = mat4::identity();

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();

	//initializing matrices with values or doing calculation
	translationMatrix = vmath::translate(0.0f, 0.0f, -2.0f);	//glTranslatef() is replaced by this line
	
	modelMatrix = translationMatrix;							//here order of multiplication is very important -> Translation, Rotation, Scale (TRS) & '*' is overloaded to multiply matrices in vmath.h

	//now passing/pushing above matrices with updated/calculated values to shader using uniform type variables
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, perspectiveProjectionMatrix);

	if(bLight == TRUE)
	{
		glUniform1i(lightingEnabledUniform, 1);

		//now passing/pushing arrays/vectors with updated/calculated values of LIGHT to shader using uniform type variables
		glUniform3fv(laUniform, 1, gfLightAmbient);		//can also be written as glUniform3f(laUniform, 0.0f, 0.3f, 0.6f);
		glUniform3fv(ldUniform, 1, gfLightDiffuse);
		glUniform3fv(lsUniform, 1, gfLightSpecular);
		glUniform4fv(lightPositionUniform, 1, gfLightPosition);

		//now passing/pushing arrays/vectors with updated/calculated values of MATERIAL to shader using uniform type variables
		glUniform3fv(kaUniform, 1, gfMaterialAmbient);
		glUniform3fv(kdUniform, 1, gfMaterialDiffuse);
		glUniform3fv(ksUniform, 1, gfMaterialSpecular);
		glUniform1f(materialShininessUniform, gfMaterialShininess);
	}
	else
	{
		glUniform1i(lightingEnabledUniform, 0);
	}

	glBindVertexArray(vao_sphere);		//binding here vao means running cassette & running all lines of vbo written in initialize() between bind & unbind of vao

	//here there should be drawing code
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_sphere_element);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	//unbinding vbo of sphere

	glBindVertexArray(0);				//unbinding vao of sphere

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
	if (vbo_sphere_position)
	{
		glDeleteBuffers(1, &vbo_sphere_position);
		vbo_sphere_position = 0;
	}

	if (vbo_sphere_normal)
	{
		glDeleteBuffers(1, &vbo_sphere_normal);
		vbo_sphere_normal = 0;
	}

	if (vbo_sphere_element)
	{
		glDeleteBuffers(1, &vbo_sphere_element);
		vbo_sphere_element = 0;
	}

	//deletion/uninitialization of vao
	if (vao_sphere)
	{
		glDeleteVertexArrays(1, &vao_sphere);
		vao_sphere = 0;
	}

	//shader uninitialization
	if (shaderProgramObject_pv)
	{
		glUseProgram(shaderProgramObject_pv);
		
		GLsizei numAttachedShaders = 0;
		glGetProgramiv(shaderProgramObject_pv, GL_ATTACHED_SHADERS, &numAttachedShaders);

		GLuint* shaderObjects = NULL;
		shaderObjects = (GLuint*)malloc(numAttachedShaders * sizeof(GLuint));

		glGetAttachedShaders(shaderProgramObject_pv, numAttachedShaders, &numAttachedShaders, shaderObjects);

		for (GLsizei i = 0; i < numAttachedShaders; i++)
		{
			glDetachShader(shaderProgramObject_pv, shaderObjects[i]);
			glDeleteShader(shaderObjects[i]);	//deleting shader obj from OGL memory
			shaderObjects[i] = 0;
		}

		free(shaderObjects);	//freeing malloc() memory
		shaderObjects = NULL;

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject_pv);
		shaderProgramObject_pv = 0;
	}

	if (shaderProgramObject_pf)
	{
		glUseProgram(shaderProgramObject_pf);
		
		GLsizei numAttachedShaders = 0;
		glGetProgramiv(shaderProgramObject_pf, GL_ATTACHED_SHADERS, &numAttachedShaders);

		GLuint* shaderObjects = NULL;
		shaderObjects = (GLuint*)malloc(numAttachedShaders * sizeof(GLuint));

		glGetAttachedShaders(shaderProgramObject_pf, numAttachedShaders, &numAttachedShaders, shaderObjects);

		for (GLsizei i = 0; i < numAttachedShaders; i++)
		{
			glDetachShader(shaderProgramObject_pf, shaderObjects[i]);
			glDeleteShader(shaderObjects[i]);	//deleting shader obj from OGL memory
			shaderObjects[i] = 0;
		}

		free(shaderObjects);	//freeing malloc() memory
		shaderObjects = NULL;

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject_pf);
		shaderProgramObject_pf = 0;
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
