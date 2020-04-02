#include "windows.h"
#include "Kadr.h"

//#define DISPLAY_ROWS 2;
//#define DISPLAY_COLS 4;

HINSTANCE hInst;
HWND hMainWnd;
TCHAR szClassName[] = L"TouchDemo Class";
TCHAR szTitle[] = L"Touch App Demo";
CKadr firstKadr = CKadr(FULL_SC);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
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
		if (hWnd == hMainWnd)
		{
			MessageBox(NULL, L"Child click", L"Left mouse button", MB_OK);
		}
		else
		{
			MessageBox(NULL, L"Parent click", L"Left mouse button", MB_OK);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Full redraw: background + rectangle
		firstKadr.Paint(hdc);

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