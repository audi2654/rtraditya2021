// RTR2021 Window Centered using SystemParametersInfo

// cl.exe /c /EHsc WindowC.c
// link.exe WindowC.obj /SUBSYSTEM:WINDOWS

// header files
#include <Windows.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   // Window Procedure (can be renamed but WndProc is coding convention)

// global var decl.
int xWindowPosition = 0;
int yWindowPosition = 0;

// entry point functions
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // variable declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("AMPWindow");
    
    int cxScreenWidth, cyScreenHeight;

    RECT rect;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    
    //cxScreenWidth = GetSystemMetrics(SM_CXSCREEN);  //1366
    //cyScreenHeight = GetSystemMetrics(SM_CYSCREEN);     //768

    cxScreenWidth = rect.right;  //1366
    cyScreenHeight = rect.bottom;     //768

    int cxWindowWidth = 600;
    int cyWindowHeight = 600;
    
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
    xWindowPosition = (cxScreenWidth / 2) - (cxWindowWidth / 2);
    yWindowPosition = (cyScreenHeight / 2) - (cyWindowHeight / 2);

    hwnd = CreateWindow(szAppName,
                        TEXT("Aditya RTR Centered Window using SystemParametersInfo"),
                        WS_OVERLAPPEDWINDOW,
                        xWindowPosition,
                        yWindowPosition,
                        cxWindowWidth,
                        cyWindowHeight,
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
    RECT rc;
    TCHAR str[] = TEXT("Aditya's Centered Window using SystemParametersInfo");
    TCHAR str2[255];

    // code
    switch(iMsg)
    {
    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(0, 255, 0));
        DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        //wsprintf(str2, TEXT("X & Y positions are : %d, %i"), xWindowPosition, yWindowPosition);
        //TextOut(hdc, 5, 5, str2, (int)_tcslen(str2));

        EndPaint(hwnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);

        wsprintf(str2, TEXT("X & Y positions are : %d, %i"), xWindowPosition, yWindowPosition);
        
        //TextOut(hdc, 5, 5, str2, (int)_tcslen(str2));
        MessageBox(hwnd, str2, TEXT("Centered Window Position"), MB_OK);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
