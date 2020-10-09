#include "StdAfx.h"
#include "GestureEngineEmulator.h"
#include "util/Util.h"

#define _USE_MATH_DEFINES
#define TOUCH_EKRAN_WIDTH	WIDTHPX
#define TOUCH_EKRAN_HEIGHT	HEIGHTPX - MECHANIC_MENU_HEIGHTPX
#define DEAD_ZONE			10
#define CLICK_TIME			200
#define SHIFT_X				300
#define SHIFT_Y				50

LRESULT CGestureEngineEmulator::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		_ptFirst.x = LOWORD(lParam);
		_ptFirst.y = HIWORD(lParam);
		//ScreenToClient(hWnd, &_ptFirst);
		_ptBegin = _ptFirst;
		_timer = GetTickCount();
		break;

	case WM_LBUTTONUP:
		{
			_timer = GetTickCount() - _timer;
			_ptSecond.x = LOWORD(lParam);
			_ptSecond.y = HIWORD(lParam);
			//ScreenToClient(hWnd, &_ptSecond);
			LONG diffX = _ptSecond.x - _ptBegin.x;
			LONG diffY = _ptSecond.y - _ptBegin.y;
			if (_timer < CLICK_TIME && diffX < DEAD_ZONE && diffY < DEAD_ZONE)
				OnLMouseUp(_ptSecond);
			else
			{
				if (EmulateTouchIsValid(_ptSecond) == false)
					break;
				POINT Cords = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
				ProcessMove(_ptFirst, Cords);
			}
		}
		break;

	case WM_RBUTTONUP:
		_ptSecond.x = LOWORD(lParam);
		_ptSecond.y = HIWORD(lParam);
		//ScreenToClient(hWnd, &_ptSecond);
		GESTURE_EMULATOR.OnRMouseUp(_ptSecond);
		break;

	case WM_MBUTTONDOWN:
		_ptFirst.x = LOWORD(lParam);
		_ptFirst.y = HIWORD(lParam);
		//ScreenToClient(hWnd, &_ptFirst);
		_ptBegin = _ptFirst;
		break;

	case WM_MBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		{
			switch(wParam)
			{
			case MK_LBUTTON:
				{
					_ptSecond.x = LOWORD(lParam);
					_ptSecond.y = HIWORD(lParam);
					//ScreenToClient(hWnd, &_ptSecond);
					if (EmulateTouchIsValid(_ptSecond) == false)
						break;
					POINT Coords = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
					ProcessMove(_ptFirst, Coords);
					_ptFirst = _ptSecond;
				}
				break;
			case MK_MBUTTON:
				{
					_ptSecond.x = LOWORD(lParam);
					_ptSecond.y = HIWORD(lParam);
					//ScreenToClient(hWnd, &_ptSecond);
					OnMouseRotate(_ptBegin, (_ptFirst.x - _ptSecond.x) * 0.01, _ptBegin);
					_ptFirst = _ptSecond;
				}
				break;
			}
		}
		break;

	case WM_MOUSEWHEEL:
		{
			_ptBegin.x = LOWORD(lParam);
			_ptBegin.y = HIWORD(lParam);
			//ScreenToClient(hWnd, &_ptBegin);
			if (0 < GET_WHEEL_DELTA_WPARAM(wParam))
				GESTURE_EMULATOR.OnMouseWheelUp(_ptBegin);
			else
				GESTURE_EMULATOR.OnMouseWheelDown(_ptBegin);
		}
		break;

	case WM_KEYDOWN:
	{
		GESTURE_EMULATOR.ProcessKeyboard(wParam);
		SendMessage(hWnd, WM_UPDATE, 0, 0);
	}
	break;

	default:
		break;
	}
	InvalidateRect(hWnd, NULL, FALSE);
	return TRUE;
}


void CGestureEngineEmulator::OnMouseWheelUp(POINT cursorPos)
{
	POINT zoomCenter;
	const double dZoomFactor = 1.1;
	zoomCenter.x = cursorPos.x;
	zoomCenter.y = cursorPos.y;
	
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(cursorPos))
				EKRAN_HANDLER.getDisplayCell(i, j)->Zoom(dZoomFactor, zoomCenter);
}

void CGestureEngineEmulator::OnMouseWheelDown(POINT cursorPos)
{
	POINT zoomCenter;
	const double dZoomFactor = 0.9;
	zoomCenter.x = cursorPos.x;
	zoomCenter.y = cursorPos.y;
	
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(cursorPos))
				EKRAN_HANDLER.getDisplayCell(i, j)->Zoom(dZoomFactor, zoomCenter);
}

void CGestureEngineEmulator::ProcessMove(POINT firstCoord, POINT finishCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstCoord))
                EKRAN_HANDLER.getDisplayCell(i, j)->Move(firstCoord, finishCoord);
}

void CGestureEngineEmulator::ProcessKeyboard(WPARAM key)
{
	POINT firstCursorPos;
	POINT secondCursorPos;
	switch(key)
	{
	case VK_LEFT:
		GetCursorPos(&firstCursorPos);
		secondCursorPos.x = firstCursorPos.x - SHIFT_X;
		secondCursorPos.y = firstCursorPos.y;
		for (int i = 0; i < DISPLAY_ROWS; i++)
		{
			for (int j = 0; j < DISPLAY_COLS; j++)
			{
				if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.getDisplayCell(i, j)->Swipe(firstCursorPos, secondCursorPos);
					return;
				}
			}
		}
		break;
	case VK_RIGHT:
		GetCursorPos(&firstCursorPos);
		secondCursorPos.x = firstCursorPos.x + SHIFT_X;
		secondCursorPos.y = firstCursorPos.y;
		for (int i = 0; i < DISPLAY_ROWS; i++)
		{
			for (int j = 0; j < DISPLAY_COLS; j++)
			{
				if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.getDisplayCell(i, j)->Swipe(firstCursorPos, secondCursorPos);
					return;
				}
			}
		}
		break;
	case VK_UP:
		GetCursorPos(&firstCursorPos);
		secondCursorPos.x = firstCursorPos.x;
		secondCursorPos.y = SHIFT_Y;
		for (int i = 0; i < DISPLAY_ROWS; i++)
		{
			for (int j = 0; j < DISPLAY_COLS; j++)
			{
				if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.getDisplayCell(i, j)->Swipe(firstCursorPos, secondCursorPos);
					return;
				}
			}
		}
		break;
	case VK_DOWN:
		GetCursorPos(&firstCursorPos);
		secondCursorPos.x = firstCursorPos.x;
		secondCursorPos.y = HEIGHTPX - SHIFT_Y;
		for (int i = 0; i < DISPLAY_ROWS; i++)
		{
			for (int j = 0; j < DISPLAY_COLS; j++)
				if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.getDisplayCell(i, j)->Swipe(firstCursorPos, secondCursorPos);
					return;
				}
		}
		break;
#ifdef DEBUG
	case VK_F5:
		pixelCheck = !pixelCheck;
		break;
#endif
	default:
		break;
	}
}

void CGestureEngineEmulator::OnLMouseUp(POINT clickCoord)
{
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		if (EKRAN_HANDLER.getMechanicMenu(i)->PointIsMine(clickCoord))
		{
			EKRAN_HANDLER.getMechanicMenu(i)->LeftClickHandle(clickCoord);
			return;
		}
		for (int j = 0; j < DISPLAY_ROWS; j++)
			if (EKRAN_HANDLER.getDisplayCell(j, i) != nullptr && EKRAN_HANDLER.getDisplayCell(j, i)->PointIsMine(clickCoord))
				{
					MessageBox(NULL, L"ClickHandle", L"", MB_OK);
					//EKRAN_HANDLER.getDisplayCell(i, j)->LeftClickHandle();
					return;
				}
	}
}

void CGestureEngineEmulator::OnRMouseUp(POINT clickCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(clickCoord))
				EKRAN_HANDLER.getDisplayCell(i, j)->Reset();
}

void CGestureEngineEmulator::OnMouseRotate(const POINT firstTouchCoord, const double dAngle, const POINT rotateCenter)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
				EKRAN_HANDLER.getDisplayCell(i, j)->Rotate(dAngle, rotateCenter);
}

bool CGestureEngineEmulator::EmulateTouchIsValid(const POINT touchCoord)
{
	bool touchIsValid = false;

    if (touchCoord.x > 0 &&
        touchCoord.x < TOUCH_EKRAN_WIDTH &&
        touchCoord.y > MECHANIC_MENU_HEIGHTPX &&
        touchCoord.y < TOUCH_EKRAN_HEIGHT)
        touchIsValid = true;

    return touchIsValid;
}