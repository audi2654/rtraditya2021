// Date: 24/01/2022
// RTR2021 Window Painting - Calling GetClientRect() in WM_CREATE

// cl.exe /c /EHsc Window.c
// link.exe Window.obj user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

// header files
#include <Windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   // Window Procedure (can be renamed but WndProc is coding convention)

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
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // registering above initialized WNDCLASSEX struct
    RegisterClassEx(&wndclass);

    // create the window
    hwnd = CreateWindow(szAppName,
                        TEXT("Aditya RTR Window Painting"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

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
    // local variable declaration
    HDC hdc;
    PAINTSTRUCT ps;
    static RECT rc;       //rc static here so as to retain its value across msgs & not reinitialized while in msg loop
    TCHAR str[] = TEXT("Hello World!!!");

    // code
    switch(iMsg)
    {
    case WM_CREATE:
        GetClientRect(hwnd, &rc);   //this will cause Hello World to not recenter when we resize window because 
        //GetClientRect() gets called only once here throughout end of program since WM_CREATE is only called once
        //in WndProc i.e as soon as CreateWindow() gets called so new resized values are not updated in rc
        break;

    case WM_PAINT:
        //GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(0, 255, 0));
        DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
