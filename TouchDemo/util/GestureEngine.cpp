#include "StdAfx.h"
#include "GestureEngine.h"
#include "util/Util.h"

#define PAN_TIMER_ID (001)

// One of the fields in GESTUREINFO structure is type of ULONGLONG (8 bytes).
// The relevant gesture information is stored in lower 4 bytes. This
// macro is used to read gesture information from this field.
#define LODWORD(ull) ((DWORD)((ULONGLONG)(ull) & 0x00000000ffffffff))

CGestureEngine *CGestureEngine::pGestureEngine = nullptr;

CGestureEngine::CGestureEngine()
{
	CGestureEngine::pGestureEngine = this;
	_dwArguments = 0;
	panIsComplete = false;
}

BOOL CGestureEngine::Create()
{
	return TRUE;
}

BOOL CGestureEngine::CleanUp()
{
	return TRUE;
}

LRESULT CGestureEngine::WndProc(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    GESTUREINFO gi;
    gi.cbSize = sizeof(gi);
    BOOL bResult = GetGestureInfo((HGESTUREINFO)lParam, &gi);

    if (!bResult)
    {
        MessageBox(NULL, L"Error in execution of GetGestureInfo", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    switch (gi.dwID)
    {
    case GID_ZOOM:
		HandleZoom(hWnd, gi);
        break;

    case GID_PAN:
		HandlePan(hWnd, gi);
        break;

    case GID_ROTATE:
		HandleRotate(hWnd, gi);
        break;

    case GID_TWOFINGERTAP:
		HandleTwoFingerTap(hWnd, gi);
        break;

    case GID_PRESSANDTAP:
		HandlePressAndTap(hWnd, gi);
        break;
    }
    CloseGestureInfoHandle((HGESTUREINFO)lParam);
    return TRUE;
}

void CGestureEngine::ProcessMove(const POINT beginCoord, const POINT startCoord, const POINT delta)
{
    for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(beginCoord))
			{
                EKRAN_HANDLER.GetKadr(i, j)->Move(startCoord, delta);
				return;
			}
}

void CGestureEngine::ProcessPressAndTap(const POINT firstTouchCoord)
{
    //MessageBox(NULL, L"Press and Tap Gesture", L"Gesture Captured", MB_OK | MB_ICONINFORMATION);
}

void CGestureEngine::ProcessRotate(const POINT firstTouchCoord, const double dAngle, const POINT rotateCenter)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.GetKadr(i, j)->DoRotate(dAngle, rotateCenter);
				return;
			}
}

void CGestureEngine::ProcessTwoFingerTap(const POINT firstTouchCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.GetKadr(i, j)->Reset();
				return;
			}
}

void CGestureEngine::ProcessZoom(const POINT firstTouchCoord, const double dZoomFactor, const POINT zoomCenter)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.GetKadr(i, j)->Zoom(dZoomFactor, zoomCenter);
				return;
			}
}

void CGestureEngine::ProcessSwipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
{
    for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.GetKadr(i, j) != nullptr && !EKRAN_HANDLER.GetKadr(i, j)->GetBlockStatus() && EKRAN_HANDLER.GetKadr(i, j)->PointIsMine(firstTouchCoord))
            {
				EKRAN_HANDLER.GetKadr(i, j)->Swipe(firstTouchCoord, secondTouchCoord);
				return;
			}
}

bool CGestureEngine::TouchInKadrSpace(const POINT touchCoord)
{
    bool touchInKadrSpace = false;

    if (touchCoord.x > X0_PX + KADR_BORDER_X &&
        touchCoord.x < X0_PX + KADR_BORDER_X + KADR_WORK_AREA_WIDTH &&
        touchCoord.y > Y0_PX + KADR_BORDER_Y_HI &&
        touchCoord.y < Y0_PX + KADR_BORDER_Y_HI + KADR_WORK_AREA_HEIGHT)
        touchInKadrSpace = true;

    return touchInKadrSpace;
}

void CGestureEngine::PanTimerProc(HWND hWnd, UINT message, UINT idTimer, DWORD dwTime)
{
	if (pGestureEngine->panIsComplete)
		return;
	pGestureEngine->ProcessSwipe(pGestureEngine->_ptFirst, pGestureEngine->_ptSecond);
	pGestureEngine->panIsComplete = true;
	SendMessage(hWnd, WM_UPDATE, 0, 0);
	KillTimer(hWnd, PAN_TIMER_ID);
}

void CGestureEngine::HandleZoom(HWND hWnd, GESTUREINFO gi)
{
	POINT ptZoomCenter;
    double k;
	switch (gi.dwFlags)
	{
	case GF_BEGIN:
		_dwArguments = LODWORD(gi.ullArguments);
		_ptFirst.x = gi.ptsLocation.x;
		_ptFirst.y = gi.ptsLocation.y;
		ScreenToClient(hWnd, &_ptFirst);
		break;

	default:
		// We read here the second point of the gesture. This is middle point between 
		// fingers in this new position.
		_ptSecond.x = gi.ptsLocation.x;
		_ptSecond.y = gi.ptsLocation.y;
		ScreenToClient(hWnd, &_ptSecond);
		if (TouchInKadrSpace(_ptSecond) == false)
			break;

		// We have to calculate zoom center point 
		ptZoomCenter.x = (_ptFirst.x + _ptSecond.x) / 2;
		ptZoomCenter.y = (_ptFirst.y + _ptSecond.y) / 2;

		// The zoom factor is the ratio between the new and the old distance. 
		// The new distance between two fingers is stored in gi.ullArguments 
		// (lower DWORD) and the old distance is stored in _dwArguments.
		k = (double)(_dwArguments) / (double)(LODWORD(gi.ullArguments));
		// Now we process zooming in/out of the object
		if (k > 0.5 && k < 1.5)
			ProcessZoom(_ptFirst, k, ptZoomCenter);

		// Now we have to store new information as a starting information 
		// for the next step in this gesture.
		_ptFirst = _ptSecond;
		_dwArguments = LODWORD(gi.ullArguments);
	}
}

void CGestureEngine::HandlePan(HWND hWnd, GESTUREINFO gi)
{
	switch (gi.dwFlags)
    {
    case GF_BEGIN:
		_ptFirst.x = gi.ptsLocation.x;
		_ptFirst.y = gi.ptsLocation.y;
		_ptBegin = _ptFirst;
		ScreenToClient(hWnd, &_ptFirst);
		if (TouchInKadrSpace(_ptFirst) == false)
			break;
		if (LODWORD(gi.ullArguments) != 0)
			panIsComplete = false;
        break;
	case GF_END:
		_dwArguments = LODWORD(gi.ullArguments);
		_ptSecond.x = gi.ptsLocation.x;
		_ptSecond.y = gi.ptsLocation.y;
		ScreenToClient(hWnd, &_ptSecond);
		if (TouchInKadrSpace(_ptSecond) == false)
			break;
        if (_dwArguments != 0)
        {
            ProcessSwipe(_ptFirst, _ptSecond);
			panIsComplete = true;
			SendMessage(hWnd, WM_UPDATE, 0, 0);
        }
		else {
			POINT pt = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
			ProcessMove(_ptBegin, _ptFirst, pt);
			_ptFirst = _ptSecond;
		}
        break;
	default:
        _ptSecond.x = gi.ptsLocation.x;
		_ptSecond.y = gi.ptsLocation.y;
		ScreenToClient(hWnd, &_ptSecond);
		if (TouchInKadrSpace(_ptSecond) == false)
			break;
        if (gi.ullArguments != 0)
        {
			SetTimer(hWnd, PAN_TIMER_ID, 200, (TIMERPROC) PanTimerProc);
		}
		else 
		{
			POINT pt = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
			ProcessMove(_ptBegin, _ptFirst, pt);
            _ptFirst = _ptSecond;
		}
        break;
    }
}

void CGestureEngine::HandleRotate(HWND hWnd, GESTUREINFO gi)
{
	switch (gi.dwFlags)
    {
    case GF_BEGIN:
        _dwArguments = 0;
        break;

    default:
        _ptFirst.x = gi.ptsLocation.x;
        _ptFirst.y = gi.ptsLocation.y;
        ScreenToClient(hWnd, &_ptFirst);
        if (TouchInKadrSpace(_ptFirst) == false)
            break;
        ProcessRotate(_ptFirst,
            GID_ROTATE_ANGLE_FROM_ARGUMENT(LODWORD(gi.ullArguments))
            - GID_ROTATE_ANGLE_FROM_ARGUMENT(_dwArguments),
            _ptFirst
			);
        _dwArguments = LODWORD(gi.ullArguments);
        break;
    }
}

void CGestureEngine::HandleTwoFingerTap(HWND hWnd, GESTUREINFO gi)
{
	_ptFirst.x = gi.ptsLocation.x;
	_ptFirst.y = gi.ptsLocation.y;
	ScreenToClient(hWnd, &_ptFirst);
    if (TouchInKadrSpace(_ptFirst) == false)
        return;
    ProcessTwoFingerTap(_ptFirst);
}

void CGestureEngine::HandlePressAndTap(HWND hWnd, GESTUREINFO gi)
{
	switch (gi.dwFlags)
    {
    case GF_BEGIN:
		_ptFirst.x = gi.ptsLocation.x;
		_ptFirst.y = gi.ptsLocation.y;
		ScreenToClient(hWnd, &_ptFirst);
        if (TouchInKadrSpace(_ptFirst) == false)
            break;
        ProcessPressAndTap(_ptFirst);
        break;
    }
}
