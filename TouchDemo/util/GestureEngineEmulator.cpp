#include "StdAfx.h"
#include "GestureEngineEmulator.h"
#include "util/Util.h"
#include "object/MechanicMenu.h"
#include "object/TouchSymbol.h"

#define _USE_MATH_DEFINES
#define DEAD_ZONE	TO_PIXEL(40)
#define SHIFT_X		TO_PIXEL(400)

CGestureEngineEmulator::CGestureEngineEmulator()
{
	_lButtonPressed = false;
	_lClickSteady = false;
#ifdef DEBUG
	pixelCheck = false;
#endif
}

LRESULT CGestureEngineEmulator::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_POINTERDOWN:
	case WM_LBUTTONDOWN:
		_ptFirst.x = LOWORD(lParam);
		_ptFirst.y = HIWORD(lParam);
		ScreenToClient(hWnd, &_ptFirst);
		_ptBegin = _ptFirst;
		_lButtonPressed = true;
		_lClickSteady = true;
		_lButtonTimer = GetTickCount();
		OnLMouseDown(_ptBegin);
		break;
		
	case WM_LBUTTONUP:
		{
			if (!_lButtonPressed)
				break;
			_lButtonTimer = GetTickCount() - _lButtonTimer;
			_lButtonPressed = false;
			_ptSecond.x = LOWORD(lParam);
			_ptSecond.y = HIWORD(lParam);
			ScreenToClient(hWnd, &_ptSecond);
			LONG diffX = _ptSecond.x - _ptBegin.x;
			LONG diffY = _ptSecond.y - _ptBegin.y;
			if (_lButtonTimer > CLICK_TIME && abs(diffX) < DEAD_ZONE && abs(diffY) < DEAD_ZONE)
			{
				OnLMouseUp(_ptFirst);
				SendMessage(hWnd, WM_UPDATE, 0, 0);
			}
			if (abs(diffX) > DEAD_ZONE || abs(diffY) > DEAD_ZONE)
			{
				if (EmulateTouchInKadrSpace(_ptSecond) == false)
					break;
				POINT Cords = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
				ProcessMove(_ptBegin, _ptFirst, Cords);
			}
		}
		break;

	case WM_RBUTTONUP:
		_ptSecond.x = LOWORD(lParam);
		_ptSecond.y = HIWORD(lParam);
		ScreenToClient(hWnd, &_ptSecond);
		GESTURE_EMULATOR.OnRMouseUp(_ptSecond);
		break;

	case WM_MBUTTONDOWN:
		_ptFirst.x = LOWORD(lParam);
		_ptFirst.y = HIWORD(lParam);
		ScreenToClient(hWnd, &_ptFirst);
		_ptBegin = _ptFirst;
		break;

	case WM_MBUTTONUP:
		break;

	case WM_POINTERUPDATE:
	{
		_ptSecond.x = LOWORD(lParam);
		_ptSecond.y = HIWORD(lParam);
		ScreenToClient(hWnd, &_ptSecond);
		if (abs(_ptSecond.x - _ptBegin.x) < DEAD_ZONE && abs(_ptSecond.y - _ptBegin.y) < DEAD_ZONE)
			break;
		else
		{
			_lClickSteady = false;
			_ptFirst = _ptSecond;
		}
	}
	break;

	
	case WM_POINTERUP:
	{
		if (!_lButtonPressed)
			break;
		_lButtonTimer = GetTickCount() - _lButtonTimer;
		_lButtonPressed = false;
		_ptSecond.x = LOWORD(lParam);
		_ptSecond.y = HIWORD(lParam);
		ScreenToClient(hWnd, &_ptSecond);
		LONG diffX = _ptSecond.x - _ptBegin.x;
		LONG diffY = _ptSecond.y - _ptBegin.y;
		if (_lButtonTimer > CLICK_TIME && abs(diffX) < DEAD_ZONE && abs(diffY) < DEAD_ZONE)
		{
			OnLMouseUp(_ptFirst);
			SendMessage(hWnd, WM_UPDATE, 0, 0);
		}
	}
	break;

	case WM_MOUSEMOVE:
		{
			switch(wParam)
			{
			case MK_LBUTTON:
				{
					_ptSecond.x = LOWORD(lParam);
					_ptSecond.y = HIWORD(lParam);
					ScreenToClient(hWnd, &_ptSecond);
					if (EmulateTouchInKadrSpace(_ptSecond) == false)
						break;
					POINT Coords = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
					if (abs(_ptSecond.x - _ptBegin.x) < DEAD_ZONE && abs(_ptSecond.y - _ptBegin.y) < DEAD_ZONE)
						break;
					else
					{
						_lClickSteady = false;
						ProcessMove(_ptBegin, _ptFirst, Coords);
						_ptFirst = _ptSecond;
					}
					
				}
				break;
			case MK_MBUTTON:
				{
					_ptSecond.x = LOWORD(lParam);
					_ptSecond.y = HIWORD(lParam);
					ScreenToClient(hWnd, &_ptSecond);
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
			ScreenToClient(hWnd, &_ptBegin);
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
	for (int j = 0; j < DISPLAY_COLS; j++)
		if (EKRAN_HANDLER.GetMechanicMenu(j) != nullptr && EKRAN_HANDLER.GetMechanicMenu(j)->PointIsMine(cursorPos))
		{
			EKRAN_HANDLER.GetMechanicMenu(j)->MouseWheelHandle(dZoomFactor, zoomCenter);
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
	for (int j = 0; j < DISPLAY_COLS; j++)
		if (EKRAN_HANDLER.GetMechanicMenu(j) != nullptr && EKRAN_HANDLER.GetMechanicMenu(j)->PointIsMine(cursorPos))
		{
			EKRAN_HANDLER.GetMechanicMenu(j)->MouseWheelHandle(dZoomFactor, zoomCenter);
			return;
		}
}

void CGestureEngineEmulator::ProcessMove(POINT beginCoord, POINT startCoord, POINT delta)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(beginCoord))
			{
                EKRAN_HANDLER.GetKadr(i, j)->Move(startCoord, delta);
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
		secondCursorPos.y = Y0_PX + KADR_BORDER_Y_HI + TO_PIXEL(20);
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
		secondCursorPos.y = Y0_PX + KADR_BORDER_Y_HI + KADR_WORK_AREA_HEIGHT - TO_PIXEL(20);
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
		EKRAN_HANDLER.ProcessKeyboard((UINT)key);
		break;
	}
}

void CGestureEngineEmulator::OnLMouseDown(POINT clickCoord)
{
	EKRAN_HANDLER.GetTouchSymbol()->LeftClickHandle(clickCoord);
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
	if (_lButtonPressed)
	{
		_lButtonPressed = false;
		_lClickSteady = false;
		return;
	}
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
				EKRAN_HANDLER.GetKadr(i, j)->DoRotate(dAngle, rotateCenter);
				return;
			}
}

bool CGestureEngineEmulator::EmulateTouchInKadrSpace(const POINT touchCoord)
{
	bool touchInKadrSpace = false;

    if (touchCoord.x > X0_PX + KADR_BORDER_X &&
        touchCoord.x < X0_PX + KADR_BORDER_X + KADR_WORK_AREA_WIDTH &&
        touchCoord.y > Y0_PX + KADR_BORDER_Y_HI &&
        touchCoord.y < Y0_PX + KADR_BORDER_Y_HI + KADR_WORK_AREA_HEIGHT)
        touchInKadrSpace = true;

    return touchInKadrSpace;
}
