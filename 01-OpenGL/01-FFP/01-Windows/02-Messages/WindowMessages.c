// Date: 23/01/2022
// RTR2021 Handling Messages in WndProc 

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
                        TEXT("Aditya Window Messages"),
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
    // code
    switch(iMsg)
    {
    case WM_CREATE:
        MessageBox(hwnd, TEXT("This is WM_CREATE message"), TEXT("Message from WndProc Switch Block"), MB_OK);
        break;

    case WM_KEYDOWN:
        MessageBox(hwnd, TEXT("This is WM_KEYDOWN message"), TEXT("Message from Switch Block"), MB_OK);
        break;

    case WM_LBUTTONDOWN:
        MessageBox(hwnd, TEXT("This is WM_LBUTTONDOWN message"), TEXT("Message from Switch Block"), MB_OK);
        break;

    case WM_RBUTTONDOWN:
        MessageBox(hwnd, TEXT("This is WM_RBUTTONDOWN message"), TEXT("Message from Switch Block"), MB_OK);
        break;

    case WM_DESTROY:
        MessageBox(hwnd, TEXT("This is WM_DESTROY message"), TEXT("Message from Switch Block"), MB_OK);
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
