// Date: 06/02/2022
// RTR2021 Toggle Fullscreen Window

// cl.exe /c /EHsc WindowFullScreen.c
// link.exe WindowFullScreen.obj user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS

// header files
#include <Windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   // Window Procedure (can be renamed but WndProc is coding convention)

// global variable declarations
HWND ghwnd = NULL;
BOOL gbFullScreen = FALSE;       //in GLUT similar is done globally

// entry point functions
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // variable declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyWindow");

    // code

    // initialization of WNDCLASSEX struct
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // registering above initialized WNDCLASSEX struct
    RegisterClassEx(&wndclass);

    // create the window
    hwnd = CreateWindow(szAppName,
                        TEXT("Aditya RTR Window"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    ghwnd = hwnd;

    // showing the window
    ShowWindow(hwnd, iCmdShow);

    // updating the window
    UpdateWindow(hwnd);

    // message loop
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int)msg.wParam);
}

// callback function definition
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    //local func decl.
    void ToggleFullScreen(void);
    
    // code
    switch(iMsg)
    {
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
    //static BOOL bFullScreen = FALSE; OR = gbFullScreen; also works

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
