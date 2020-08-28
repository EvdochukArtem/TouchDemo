#include "TouchDemo.h"

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE /* hPrevInstance */,
	LPWSTR    /* lpCmdLine */,
	int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

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

	mainClassEx.style = 0;//CS_HREDRAW | CS_VREDRAW;
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
		return FALSE;

	if (!gestureEngine.Create(hMainWnd))
		return FALSE;

	if (!drawEngine.Create())
		return FALSE;

	if (!kadrHandler.Create())
		return FALSE;

	drawKit.Init();

	SendMessage(hMainWnd, WM_UPDATE, 0, 0);

	ShowWindow(hMainWnd, SW_MAXIMIZE);
	UpdateWindow(hMainWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GESTURENOTIFY:
	{
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

	case WM_UPDATE:
	{
		drawEngine.UpdateBackground();
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		drawEngine.Draw(hdc);
		/*kadrHandler.DrawBackground(hdc);

		hdcMem = CreateCompatibleDC(hdc);
		hbmMem = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		hOld = SelectObject(hdcMem, hbmMem);

		kadrHandler.Draw(hdc);
		
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HGDIOBJ hPenOld = SelectObject(hdc, hPen);
		Rectangle(hdc, 0, 0, 100, 25);
		Rectangle(hdc, 0, HEIGHTPX, 100, HEIGHTPX - 25);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);

		BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);*/

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