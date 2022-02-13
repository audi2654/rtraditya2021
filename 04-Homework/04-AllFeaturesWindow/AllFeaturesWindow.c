//All Features Window
//Window with:
//	-Icon
//	-Fullscreen
//	-Centered Window
//	-File I/O
//	-Escape key exit
//	-Active Window
//	-Special / game loop

//header files
#include <windows.h>
#include <stdio.h>			//for file IO functions
#include <stdlib.h>			//for exit()
#include "WindowIcon.h"		//for icon

#define ID_TIMER1 600

//global func decl.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global var decl.
//for fullscreen
HWND ghwnd = NULL;
BOOL gbFullScreen = FALSE;

//for centered window
int xWindowPosition = 0;
int yWindowPosition = 0;

int cxWindowWidth = 600;
int cyWindowHeight = 600;

//for active window
BOOL gbActiveWindow = FALSE;

//for file I/O
FILE* gpFile = NULL;

//entry point func
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local var decl.
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Window Assignment");
	BOOL bDone = FALSE;		//for special loop

	int cxScreenWidth, cyScreenHeight;
	cxScreenWidth = GetSystemMetrics(SM_CXSCREEN);  //1366
	cyScreenHeight = GetSystemMetrics(SM_CYSCREEN);     //768

	//code
	
	// file IO
	if (fopen_s(&gpFile, "FeaturedWindowLog.txt", "w") != 0)      //fopen_s safe/secured
	   //fopen_s(out parameter ptr for the file opened or created, "name of file to open or create / path of file to read/write", reason to open file "r", "w", "a", "r+", etc)
	{
		MessageBox(HWND_DESKTOP, "Creation of Log file failed. Exitting!", "File I/O Error", MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Featured Window Log file CREATED successfully!\n");
	}

	//initialize wndclass struct
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_PIN);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(AMP_MYICON));

	//register wndclass struct in memory
	RegisterClassEx(&wndclass);

	//create window
	xWindowPosition = (cxScreenWidth / 2) - (cxWindowWidth / 2);
	yWindowPosition = (cyScreenHeight / 2) - (cyWindowHeight / 2);

	hwnd = CreateWindow(szAppName,
		TEXT("AMP Features Window Assignment"),
		WS_OVERLAPPEDWINDOW,
		xWindowPosition,
		yWindowPosition,
		cxWindowWidth,
		cyWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	//show window
	ShowWindow(hwnd, iCmdShow);

	//update window
	UpdateWindow(hwnd);

	//msg loop
	/*while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

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
				// here game runs (Game Mode)
				// because OpenGL & DirectX works only when Window msgs are not received or processed

			}
		}
	}

	/*if (gpFile)
	{
		fprintf(gpFile, "Log file CLOSED successfully!\n");
		fclose(gpFile);
		gpFile = NULL;
	}*/

	return((int)msg.wParam);
}

//callback func definition
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local func decl.
	void ToggleFullScreen(void);

	//local var decl.
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[] = TEXT("AMP Featured Window");
	TCHAR str2[255];
	static int iPaintFlag = 0;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER1, 100, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, ID_TIMER1);
		iPaintFlag++;
		if (iPaintFlag >= 8)
		{
			iPaintFlag = 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, ID_TIMER1, 500, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		//DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2), str, (int)_tcslen(str));

		wsprintf(str2, TEXT("Features are : "));
		TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 30, str2, (int)_tcslen(str2));

		if (iPaintFlag == 1)
		{
			SetTextColor(hdc, RGB(255, 0, 0));
			wsprintf(str2, TEXT("1. Icon"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 45, str2, (int)_tcslen(str2));
		} 
		else if (iPaintFlag == 2)
		{
			SetTextColor(hdc, RGB(0, 255, 0));
			wsprintf(str2, TEXT("2. Fullscreen (Press Escape to try)"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 60, str2, (int)_tcslen(str2));
		}
		else if (iPaintFlag == 3)
		{
			SetTextColor(hdc, RGB(0, 0, 255));
			wsprintf(str2, TEXT("3. Centered Window"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 75, str2, (int)_tcslen(str2));
		}
		else if (iPaintFlag == 4)
		{
			SetTextColor(hdc, RGB(0, 255, 255));
			wsprintf(str2, TEXT("4. File I/O"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 90, str2, (int)_tcslen(str2));
		}
		else if (iPaintFlag == 5)
		{
			SetTextColor(hdc, RGB(255, 0, 255));
			wsprintf(str2, TEXT("5. Escape Key Exit (Press Escape to try)"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 105, str2, (int)_tcslen(str2));
		}
		else if (iPaintFlag == 6)
		{
			SetTextColor(hdc, RGB(255, 255, 0));
			wsprintf(str2, TEXT("6. Active Window"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 120, str2, (int)_tcslen(str2));
		}
		else if (iPaintFlag == 7)
		{
			SetTextColor(hdc, RGB(180, 255, 42));
			wsprintf(str2, TEXT("7. Special Loop"));
			TextOut(hdc, (xWindowPosition / 2), (yWindowPosition / 2) + 135, str2, (int)_tcslen(str2));
		}
		else
		{
			SetTextColor(hdc, RGB(0, 255, 0));
		}

		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);

		wsprintf(str2, TEXT("X & Y positions are : %d, %i"), xWindowPosition, yWindowPosition);

		//TextOut(hdc, 5, 5, str2, (int)_tcslen(str2));
		MessageBox(hwnd, str2, TEXT("Centered Window Position"), MB_OK);
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

	case WM_SETFOCUS:
		gbActiveWindow = TRUE;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = FALSE;
		break;

	case WM_DESTROY:
		if (gpFile)
		{
			fprintf(gpFile, "Featured Window Log file CLOSED successfully!\n");
			fclose(gpFile);
			gpFile = NULL;
		}

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
