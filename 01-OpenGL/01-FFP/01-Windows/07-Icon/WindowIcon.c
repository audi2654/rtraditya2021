// Date: 06/02/2022
// RTR2021 Custom Icon (File Icon in Explorer, Taskbar & System Icon)

// cl.exe /c /EHsc WindowIcon.c
// rc.exe WindowIcon.rc (creates .res file)
// link.exe WindowIcon.obj WindowIcon.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

// header files
#include <Windows.h>
#include "WindowIcon.h"     //also include this line in .rc file for System Icon on Caption Bar
//rc.exe gives some random ID by itself to your resource
//but by including .h file in .c & .rc files name or ID matches 
//in both files .c & .res by cl.exe & rc.exe respectively while compiling
//linker embeds your .res file in between Primary Header & Data Region of your .exe file & hence its size of .exe is increased
//only in Windows OS resources get embedded in the .exe file, not in any other OS

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
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));

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
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            break;
    }

    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
