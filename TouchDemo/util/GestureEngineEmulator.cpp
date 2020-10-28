#include "StdAfx.h"
#include "GestureEngineEmulator.h"
#include "util/Util.h"

#define _USE_MATH_DEFINES
const int TOUCH_EKRAN_WIDTH		= WIDTHPX;
const int TOUCH_EKRAN_HEIGHT	= HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
const int DEAD_ZONE				= TO_PIXEL(10);
const int CLICK_TIME			= TO_PIXEL(200);
const int SHIFT_X				= TO_PIXEL(300);
const int SHIFT_Y				= TO_PIXEL(50);

CGestureEngineEmulator::CGestureEngineEmulator()
{
	_lButtonPressed = false;
#ifdef DEBUG
	pixelCheck = false;
#endif
}

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
		_lButtonPressed = true;
		break;

	case WM_LBUTTONUP:
		{
			_lButtonPressed = false;
			_timer = GetTickCount() - _timer;
			_ptSecond.x = LOWORD(lParam);
			_ptSecond.y = HIWORD(lParam);
			//ScreenToClient(hWnd, &_ptSecond);
			LONG diffX = _ptSecond.x - _ptBegin.x;
			LONG diffY = _ptSecond.y - _ptBegin.y;
			if (_timer < CLICK_TIME && diffX < DEAD_ZONE && diffX > -DEAD_ZONE && diffY < DEAD_ZONE && diffY > -DEAD_ZONE)
				OnLMouseUp(_ptFirst);
			else
			{
				if (EmulateTouchIsValid(_ptSecond) == false)
					break;
				POINT Cords = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
				ProcessMove(_ptBegin, _ptFirst, Cords);
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
					ProcessMove(_ptBegin, _ptFirst, Coords);
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
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(cursorPos))
			{
				EKRAN_HANDLER.GetKadr(i, j)->Zoom(dZoomFactor, zoomCenter);
				return;
			}
}

void CGestureEngineEmulator::OnMouseWheelDown(POINT cursorPos)
{
	POINT zoomCenter;
	const double dZoomFactor = 0.9;
	zoomCenter.x = cursorPos.x;
	zoomCenter.y = cursorPos.y;
	
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(cursorPos))
			{
				EKRAN_HANDLER.GetKadr(i, j)->Zoom(dZoomFactor, zoomCenter);
				return;
			}
}

void CGestureEngineEmulator::ProcessMove(POINT beginCoord, POINT firstCoord, POINT finishCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(beginCoord))
			{
                EKRAN_HANDLER.GetKadr(i, j)->Move(firstCoord, finishCoord);
				return;
			}
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
				if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.GetKadr(i, j)->Swipe(firstCursorPos, secondCursorPos);
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
				if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.GetKadr(i, j)->Swipe(firstCursorPos, secondCursorPos);
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
				if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.GetKadr(i, j)->Swipe(firstCursorPos, secondCursorPos);
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
				if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstCursorPos))
				{
					EKRAN_HANDLER.GetKadr(i, j)->Swipe(firstCursorPos, secondCursorPos);
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
	for (int j = 0; j < DISPLAY_COLS; j++)
	{
		if (EKRAN_HANDLER.GetMechanicMenu(j)->PointIsMine(clickCoord))
		{
			EKRAN_HANDLER.GetMechanicMenu(j)->LeftClickHandle(clickCoord);
			return;
		}
		for (int i = 0; i < DISPLAY_ROWS; i++)
		{
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(clickCoord))
			{
				EKRAN_HANDLER.GetKadr(i, j)->LeftClickHandle(clickCoord);
				return;
			}
		}
	}
}

void CGestureEngineEmulator::OnRMouseUp(POINT clickCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(clickCoord))
			{
				EKRAN_HANDLER.GetKadr(i, j)->Reset();
				return;
			}
}

void CGestureEngineEmulator::OnMouseRotate(const POINT firstTouchCoord, const double dAngle, const POINT rotateCenter)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.GetKadr(i, j)->Rotate(dAngle, rotateCenter);
				return;
			}
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
