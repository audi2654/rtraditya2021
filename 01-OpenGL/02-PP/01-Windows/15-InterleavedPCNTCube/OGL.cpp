//Date: 16/10/2022
//RTR2021 OGL PP 3D Marble Textured Colored Cube with Per Fragment Lighting
//Program for Interleaved Concept

//header files
#include <windows.h>
#include <stdio.h>			//for file I/O functions
#include <stdlib.h>			//for exit()
#include "OGL.h"			//for icon & texture

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
GLuint vao_cube;									//vertex array object for cube shape
GLuint vbo_cube;

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
GLuint materialShininessUniform;		//material shininess

//var for toggling between on/off of light
GLuint lightingEnabledUniform;			//used in Shader
BOOL bLight = FALSE; 					//used in WNDPROC to handle case for 'L'

//for texture variables
GLuint texture_marble;

//user defined uniform vars for texture
GLuint textureSamplerUniform;

//for animation
GLfloat angleCube = 0.0f;

//vars for values to use in light calculation (values taken from Gouraud Shading on Sphere FFP program)
//black & white
GLfloat gfLightAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat gfLightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};				//for u_ld (light color) in shader
GLfloat gfLightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gfLightPosition[] = {100.0f, 100.0f, 100.0f, 1.0f};			//change light position

GLfloat gfMaterialAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gfMaterialDiffuse[] = {0.5f, 0.2f, 0.7f, 1.0f};				//for u_kd (light brightness) in shader
GLfloat gfMaterialSpecular[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat gfMaterialShininess = 128.0f;								//change shininess for object

//var for matrix of perspective projection matrix
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
		TEXT("AMP RTR PP Window - Interleaved PCNT Cube with Per Fragment Light & Marble Texture"),
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
		fprintf(gpFile, "LoadGlTexture for Marble FAILED\n");
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
	BOOL LoadGlTexture(GLuint*, TCHAR[]);
	
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
		"in vec4 a_color;" \
		"in vec3 a_normal;" \
		"in vec2 a_texcoord;" \
		"uniform mat4 u_modelMatrix;" \
		"uniform mat4 u_viewMatrix;" \
		"uniform mat4 u_projectionMatrix;" \
		"uniform vec4 u_lightPosition;" \
		"uniform int u_lightingEnabled;" \
		"out vec3 transformedNormal;" \
		"out vec3 lightDirection;" \
		"out vec3 viewerVector;" \
		"out vec4 a_color_out;" \
		"out vec2 a_texcoord_out;" \
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
			"a_color_out = a_color;" \
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
		"in vec3 transformedNormal;" \
		"in vec3 lightDirection;" \
		"in vec3 viewerVector;" \
		"in vec4 a_color_out;" \
		"in vec2 a_texcoord_out;" \
		"uniform vec3 u_la;" \
		"uniform vec3 u_ld;" \
		"uniform vec3 u_ls;" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_materialShininess;" \
		"uniform int u_lightingEnabled;" \
		"uniform sampler2D u_textureSampler;" \
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
			"vec3 tex = vec3(texture(u_textureSampler, a_texcoord_out));" \
			"FragColor = vec4(tex * phong_ads_light * vec3(a_color_out), 1.0);" \
		"}";

	//FragColor = vec4(tex * phong_ads_light, 1.0) * a_color_out * texture(u_textureSampler, a_texcoord_out) also works

	//texture return type is vec4
	//GLSL function texture() basically samples the colors from texture (textures & lights are nothing but a different kind of colors) 
	//which you gave by u_textureSampler textureSamplerUniform at location glGetUniformLocation on line 514 
	//& maps them on coordicates given by a_texcoord_out variable

	//for different geometries by using below 3 lines before drawing it in display(), you bind & give the desired texture
	//& push it to textureSamplerUniform location into shader to use selected texture while drawing geometries
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, texture_marble);
		// glUniform1i(textureSamplerUniform, 0); 		//0 here is for active texture GL_TEXTURE0
	
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
	glBindAttribLocation(shaderProgramObject, AMP_ATTRIBUTE_NORMAL, "a_normal");
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

	//post linking retrieving uniformed locations of user defined uniform type variables from shaderProgramObject
		modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_modelMatrix");				//viable place for andhar			
		viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_viewMatrix");
		projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "u_projectionMatrix");
		textureSamplerUniform = glGetUniformLocation(shaderProgramObject, "u_textureSampler");

		//retrieving uniformed locations of light ADS uniform vars
		laUniform = glGetUniformLocation(shaderProgramObject, "u_la");						//light ambient
		ldUniform = glGetUniformLocation(shaderProgramObject, "u_ld");						//light diffuse
		lsUniform = glGetUniformLocation(shaderProgramObject, "u_ls");						//light specular
		lightPositionUniform = glGetUniformLocation(shaderProgramObject, "u_lightPosition");

		//retrieving uniformed locations of material ADS uniform vars
		kaUniform = glGetUniformLocation(shaderProgramObject, "u_ka");						//material ambient
		kdUniform = glGetUniformLocation(shaderProgramObject, "u_kd");						//material diffuse
		ksUniform = glGetUniformLocation(shaderProgramObject, "u_ks");						//material specular
		materialShininessUniform = glGetUniformLocation(shaderProgramObject, "u_materialShininess");

		//retrieving uniformed locations of var for toggling between on/off of light
		lightingEnabledUniform = glGetUniformLocation(shaderProgramObject, "u_lightingEnabled");

	//here starts OpenGL code
	//declaration of vertex data arrays
	//ORDER of PCNT position, color, texcoord & normals for faces of shapes is important
	//i.e if in 1st array first 3 values are for front face then all 3 arrays should have first 3 values for front face

	const GLfloat cube_pcnt[] =
	{
		// positions                 //colors               //normals                   //texture

		// Top face               // Top face                 // Top face              // Top face
		1.0f, 1.0f, -1.0f,       0.0f,0.0f,1.0f,          0.0f, 1.0f, 0.0f,            1.0f,1.0f,
		-1.0f, 1.0f, -1.0f,      0.0f,0.0f,1.0f,          0.0f, 1.0f, 0.0f,            0.0f,1.0f,
		-1.0f, 1.0f, 1.0f,       0.0f,0.0f,1.0f,          0.0f, 1.0f, 0.0f,            0.0f,0.0f,
		1.0f, 1.0f, 1.0f,        0.0f,0.0f,1.0f,          0.0f, 1.0f, 0.0f,            1.0f,0.0f,

		// Bottom face            // Bottom face             // Bottom face            // Bottom face
		1.0f, -1.0f, -1.0f,      0.0f,1.0f,0.0f,         0.0f, -1.0f, 0.0f,            1.0f,1.0f,
		-1.0f, -1.0f, -1.0f,     0.0f,1.0f,0.0f,         0.0f, -1.0f, 0.0f,            0.0f,1.0f,
		-1.0f, -1.0f, 1.0f,      0.0f,1.0f,0.0f,         0.0f, -1.0f, 0.0f,            0.0f,0.0f,
		1.0f, -1.0f, 1.0f,       0.0f,1.0f,0.0f,         0.0f, -1.0f, 0.0f,            1.0f,0.0f,

		// Front face             // Front face              // Front face             // Front face
		1.0f, 1.0f, 1.0f,        1.0f,0.0f,0.0f,         0.0f, 0.0f, 1.0f,             1.0f,1.0f,
		-1.0f, 1.0f, 1.0f,       1.0f,0.0f,0.0f,         0.0f, 0.0f, 1.0f,             0.0f,1.0f,
		-1.0f, -1.0f, 1.0f,      1.0f,0.0f,0.0f,         0.0f, 0.0f, 1.0f,             0.0f,0.0f,
		1.0f, -1.0f, 1.0f,       1.0f,0.0f,0.0f,         0.0f, 0.0f, 1.0f,             1.0f,0.0f,

		// Back face              // Back face              // Back face              // Back face
		1.0f, 1.0f, -1.0f,       0.0f,1.0f,1.0f,         0.0f, 0.0f, -1.0f,             1.0f,1.0f,
		-1.0f, 1.0f, -1.0f,      0.0f,1.0f,1.0f,         0.0f, 0.0f, -1.0f,             0.0f,1.0f,
		-1.0f, -1.0f, -1.0f,     0.0f,1.0f,1.0f,         0.0f, 0.0f, -1.0f,             0.0f,0.0f,
		1.0f, -1.0f, -1.0f,      0.0f,1.0f,1.0f,         0.0f, 0.0f, -1.0f,             1.0f,0.0f,

		// Right face              // Right face          	// Right face              // Right face
		1.0f, 1.0f, -1.0f,      1.0f,0.0f,1.0f,         1.0f, 0.0f, 0.0f,               1.0f,1.0f,
		1.0f, 1.0f, 1.0f,       1.0f,0.0f,1.0f,         1.0f, 0.0f, 0.0f,               0.0f,1.0f,
		1.0f, -1.0f, 1.0f,      1.0f,0.0f,1.0f,         1.0f, 0.0f, 0.0f,               0.0f,0.0f,
		1.0f, -1.0f, -1.0f,     1.0f,0.0f,1.0f,         1.0f, 0.0f, 0.0f,               1.0f,0.0f,

		// Left face                // Left face           // Left face                // Left face
		-1.0f, 1.0f, 1.0f,      1.0f,1.0f,0.0f,         -1.0f, 0.0f, 0.0f,              1.0f,1.0f,
		-1.0f, 1.0f, -1.0f,     1.0f,1.0f,0.0f,         -1.0f, 0.0f, 0.0f,              0.0f,1.0f,
		-1.0f, -1.0f, -1.0f,    1.0f,1.0f,0.0f,         -1.0f, 0.0f, 0.0f,              0.0f,0.0f,
		-1.0f, -1.0f, 1.0f,     1.0f,1.0f,0.0f,         -1.0f, 0.0f, 0.0f,              1.0f,0.0f,
	};

	//vao for cube
	glGenVertexArrays(1, &vao_cube);
	glBindVertexArray(vao_cube);

	//single vbo for PCNT of cube
	glGenBuffers(1, &vbo_cube);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pcnt), cube_pcnt, GL_STATIC_DRAW);			//sizeof(vbo_cube) is nothing but 11 * 24 * sizeof(GLfloat)
	
	//position
	glVertexAttribPointer(AMP_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(0));
	glEnableVertexAttribArray(AMP_ATTRIBUTE_POSITION);

	//color
	glVertexAttribPointer(AMP_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(AMP_ATTRIBUTE_COLOR);

	//normal
	glVertexAttribPointer(AMP_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(AMP_ATTRIBUTE_NORMAL);

	//texture
	glVertexAttribPointer(AMP_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));
	glEnableVertexAttribArray(AMP_ATTRIBUTE_TEXTURE0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);					//unbinding vertex array object vao for cube

	//clear the screen using black color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//RGBA here we only tell which color to use when clearing screen, actual clearing happens in display()

	//depth 3D related changes
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//texture related code
	if(LoadGlTexture(&texture_marble, MAKEINTRESOURCE(IDBITMAP_MARBLE)) == FALSE)
	{
		return -6;
	}

	//enabling the texture
	glEnable(GL_TEXTURE_2D);

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

	//CUBE
	//transformations related code
	//declaring TRS & MVP identity matrices as per requirement
	mat4 translationMatrix = mat4::identity();
	mat4 scaleMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();
	mat4 rotationMatrix_x = mat4::identity();
	mat4 rotationMatrix_y = mat4::identity();
	mat4 rotationMatrix_z = mat4::identity();

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();

	//initializing matrices with values or doing calculation
	translationMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	scaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);
	rotationMatrix_x = vmath::rotate(angleCube, 1.0f, 0.0f, 0.0f);
	rotationMatrix_y = vmath::rotate(angleCube, 0.0f, 1.0f, 0.0f);
	rotationMatrix_z = vmath::rotate(angleCube, 0.0f, 0.0f, 1.0f);
	rotationMatrix = rotationMatrix_x * rotationMatrix_y * rotationMatrix_z;
	
	modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;		//here order of multiplication is very important -> Translation, Rotation, Scale (TRS) & '*' is overloaded to multiply matrices in vmath.h

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

	//for texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_marble);
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

	glBindTexture(GL_TEXTURE_2D, 0);			//unbinding texture_marble - optional

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

void uninitialize(void)
{
	//function declarations
	void ToggleFullScreen(void);

	//code
	if (gbFullScreen)
	{
		ToggleFullScreen();		//window should not die in Fullscreen mode
	}

	//for texture variables
	if(texture_marble)
	{
		glDeleteTextures(1, &texture_marble);
		texture_marble = 0;
	}

	//deletion/uninitialization of vbo
	if (vbo_cube)
	{
		glDeleteBuffers(1, &vbo_cube);
		vbo_cube = 0;
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

//user defined func definition
BOOL LoadGlTexture(GLuint* texture, TCHAR ImageResourceID[])
{
	//local var decl.
	HBITMAP hbitmap = NULL;
	BITMAP bmp;
	BOOL bResult = FALSE;

	//code
	hbitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), ImageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	//LR_CREATEDIBSECTION == returns a device independent bitmap section

	if(hbitmap)
	{
		bResult = TRUE;

		GetObject(hbitmap, sizeof(BITMAP), &bmp);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//here we tell to unpack the pixels & arrange them in aligned manner of rows of 4 bits
		//4 types that is RGBA, in PP on shader level jump of 1 performs better/faster

		glGenTextures(1, texture);		//5th step

		glBindTexture(GL_TEXTURE_2D, *texture);		//6th step

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //7th step
		//when texture is near to viewer we tell OGL to draw it with magnified/maximum details

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //7th step
		//when texture is far from viewer we tell OGL to draw it with minimum details
		//for less load on OGL machine & increase performance

		//creating the actual texture
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		//not avaiable in OGL PP, it is wrapper function for glTexImage2D() & glGenerateMipmap()
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.bmWidth, bmp.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp.bmBits);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);	//8th step

		DeleteObject(hbitmap);		//9th step
	}

	return(bResult);
}
