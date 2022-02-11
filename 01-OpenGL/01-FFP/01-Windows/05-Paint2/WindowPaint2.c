// Date: 05/02/2022
// RTR2021 Window Painting 2

// cl.exe /c /EHsc WindowPaint2.c
// link.exe WindowPaint2.obj user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

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
    RECT rc;
    TCHAR str[] = TEXT("Hello World!!!");
    static int iColorFlag = 0;

    // code
    switch(iMsg)
    {
    case WM_KEYDOWN:
        switch(wParam)
        {
        case 27:
            DestroyWindow(hwnd);
            break;

        default:
            break;
        }

        break;
    
    case WM_CHAR:
        switch(wParam)
        {
        //key press kelyavr swatahhun OS WM_PAINT nahi pathvat cause by default 8 WM_PAINT walya cases madhe key press nai yet
        case 'R':
        case 'r':
            iColorFlag = 1;
            InvalidateRect(hwnd, NULL, TRUE);   //internally this sends WM_PAINT msg
            break;

        case 'G':
        case 'g':
            iColorFlag = 2;
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case 'B':
        case 'b':
            iColorFlag = 3;
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        default:
            iColorFlag = 0;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }

        break;

    case WM_PAINT:
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));

        if(iColorFlag == 1)
            SetTextColor(hdc, RGB(255, 0, 0));
        else if(iColorFlag == 2)
            SetTextColor(hdc, RGB(0, 255, 0));
        else if(iColorFlag == 3)
            SetTextColor(hdc, RGB(0, 0, 255));
        else    
            SetTextColor(hdc, RGB(255, 255, 255));
        
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
