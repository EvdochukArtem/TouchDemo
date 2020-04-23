#include "windows.h"
#include "GestureEngine.h"
#include "KadrHandler.h"

HINSTANCE hInst;
HWND hMainWnd;
TCHAR szClassName[] = L"TouchDemo Class";
TCHAR szTitle[] = L"Touch App Demo";
CGestureEngine gestureEngine;
CKadrHandler kadrHandler;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE /* hPrevInstance */,
	LPWSTR    /* lpCmdLine */,
	int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX mainClassEx;

	mainClassEx.cbSize = sizeof(WNDCLASSEX);

	mainClassEx.style = CS_HREDRAW | CS_VREDRAW;
	mainClassEx.lpfnWndProc = WndProc;
	mainClassEx.cbClsExtra = 0;
	mainClassEx.cbWndExtra = 0;
	mainClassEx.hInstance = hInstance;
	mainClassEx.hIcon = 0;
	mainClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	mainClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	mainClassEx.lpszMenuName = NULL;
	mainClassEx.lpszClassName = szClassName;
	mainClassEx.hIconSm = 0;

	return RegisterClassEx(&mainClassEx);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	hMainWnd = CreateWindow(szClassName, szTitle, WS_SYSMENU,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);

	if (!hMainWnd)
	{
		return FALSE;
	}

	ShowWindow(hMainWnd, SW_MAXIMIZE);
	UpdateWindow(hMainWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		/*if (hWnd == hMainWnd)
		{
			MessageBox(NULL, L"Child click", L"Left mouse button", MB_OK);
		}
		else
		{
			MessageBox(NULL, L"Parent click", L"Left mouse button", MB_OK);
		}*/
		break;

	case WM_GESTURENOTIFY:
	{
		// This is the right place to define the list of gestures that this
		// application will support. By populating GESTURECONFIG structure 
		// and calling SetGestureConfig function. We can choose gestures 
		// that we want to handle in our application. In this app we
		// decide to handle all gestures.

		DWORD dwPanWant = GC_PAN | GC_PAN_WITH_SINGLE_FINGER_VERTICALLY | GC_PAN_WITH_SINGLE_FINGER_HORIZONTALLY;
		DWORD dwPanBlock = GC_PAN_WITH_GUTTER | GC_PAN_WITH_INERTIA;

		GESTURECONFIG gc[] = { {GID_PAN, dwPanWant, dwPanBlock},
					  { GID_ZOOM, GC_ZOOM, 0 },
					  { GID_ROTATE, GC_ROTATE, 0},
					  { GID_TWOFINGERTAP, GC_TWOFINGERTAP , 0},
					  { GID_PRESSANDTAP, GC_PRESSANDTAP , 0}
		};

		BOOL bResult = SetGestureConfig(
			hWnd,                 // window for which configuration is specified  
			0,                    // reserved, must be 0
			5,                    // count of GESTURECONFIG structures
			gc,                  // array of GESTURECONFIG structures, dwIDs will be processed in the
								  // order specified and repeated occurances will overwrite previous ones
			sizeof(GESTURECONFIG) // sizeof(GESTURECONFIG)
		);

		if (!bResult)
		{
			//assert(L"Error in execution of SetGestureConfig" && 0);
			MessageBox(NULL, L"Error in execution of SetGestureConfig", L"Error", MB_OK | MB_ICONERROR);
		}
	}
	break;

	case WM_GESTURE:
		return gestureEngine.WndProc(hWnd, wParam, lParam);
		break;

	case WM_HSCROLL:
		return gestureEngine.WndProc(hWnd, wParam, lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < DISPLAY_ROWS; i++)
			for (int j = 0; j < DISPLAY_COLS; j++)
				if (kadrHandler.getDisplayCell(i, j) != NULL)
					kadrHandler.getDisplayCell(i, j)->Paint(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:

		PostQuitMessage(0);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}