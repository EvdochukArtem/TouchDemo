#include "StdAfx.h"
#include "GestureEngine.h"
#include "util/Util.h"

#define _USE_MATH_DEFINES
#define TOUCH_EKRAN_WIDTH WIDTHPX
#define TOUCH_EKRAN_HEIGHT HEIGHTPX - MECHANIC_MENU_HEIGHTPX
#define PAN_TIMER_ID       (001)

// One of the fields in GESTUREINFO structure is type of ULONGLONG (8 bytes).
// The relevant gesture information is stored in lower 4 bytes. This
// macro is used to read gesture information from this field.
#define LODWORD(ull) ((DWORD)((ULONGLONG)(ull) & 0x00000000ffffffff))

CGestureEngine *CGestureEngine::pGestureEngine = nullptr;

CGestureEngine::CGestureEngine()
{
	CGestureEngine::pGestureEngine = this;
}

BOOL CGestureEngine::Create()
{
	_dwArguments = 0;
	panIsComplete = false;
	return TRUE;
}

LRESULT CGestureEngine::WndProc(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    POINT ptZoomCenter;
    double k;

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
            if (TouchIsValid(_ptSecond) == false)
                break;

            // We have to calculate zoom center point 
            ptZoomCenter.x = (_ptFirst.x + _ptSecond.x) / 2;
            ptZoomCenter.y = (_ptFirst.y + _ptSecond.y) / 2;

            // The zoom factor is the ratio between the new and the old distance. 
            // The new distance between two fingers is stored in gi.ullArguments 
            // (lower DWORD) and the old distance is stored in _dwArguments.
            k = (double)(LODWORD(gi.ullArguments)) / (double)(_dwArguments);

            // Now we process zooming in/out of the object
            ProcessZoom(_ptFirst, k, ptZoomCenter);

            // Now we have to store new information as a starting information 
            // for the next step in this gesture.
            _ptFirst = _ptSecond;
            _dwArguments = LODWORD(gi.ullArguments);
        }
        break;

    case GID_PAN:
        switch (gi.dwFlags)
        {
        case GF_BEGIN:
			_ptFirst.x = gi.ptsLocation.x;
			_ptFirst.y = gi.ptsLocation.y;
			ScreenToClient(hWnd, &_ptFirst);
			if (TouchIsValid(_ptFirst) == false)
				break;
			if (LODWORD(gi.ullArguments) != 0)
				panIsComplete = false;
            break;
		case GF_END:
			_dwArguments = LODWORD(gi.ullArguments);
			_ptSecond.x = gi.ptsLocation.x;
			_ptSecond.y = gi.ptsLocation.y;
			ScreenToClient(hWnd, &_ptSecond);
			if (TouchIsValid(_ptSecond) == false)
				break;
            if (_dwArguments != 0)
            {
                ProcessSwipe(_ptFirst, _ptSecond);
				panIsComplete = true;
				SendMessage(hWnd, WM_UPDATE, 0, 0);
            }
			else {
				POINT pt = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
				ProcessMove(_ptFirst, pt);
				_ptFirst = _ptSecond;
			}
            break;
		default:
            _ptSecond.x = gi.ptsLocation.x;
			_ptSecond.y = gi.ptsLocation.y;
			ScreenToClient(hWnd, &_ptSecond);
			if (TouchIsValid(_ptSecond) == false)
				break;
            if (gi.ullArguments != 0)
            {
				SetTimer(hWnd, PAN_TIMER_ID, 200, (TIMERPROC) PanTimerProc);
			}
			else 
			{
				POINT pt = {_ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y};
				ProcessMove(_ptFirst, pt);
                _ptFirst = _ptSecond;
			}
            break;
        }
        break;

    case GID_ROTATE:
        switch (gi.dwFlags)
        {
        case GF_BEGIN:
            _dwArguments = 0;
            break;

        default:
            _ptFirst.x = gi.ptsLocation.x;
            _ptFirst.y = gi.ptsLocation.y;
            ScreenToClient(hWnd, &_ptFirst);
            if (TouchIsValid(_ptFirst) == false)
                break;
            ProcessRotate(_ptFirst,
                GID_ROTATE_ANGLE_FROM_ARGUMENT(LODWORD(gi.ullArguments))
                - GID_ROTATE_ANGLE_FROM_ARGUMENT(_dwArguments),
                _ptFirst
				);
            _dwArguments = LODWORD(gi.ullArguments);
            break;
        }
        break;

    case GID_TWOFINGERTAP:
		_ptFirst.x = gi.ptsLocation.x;
		_ptFirst.y = gi.ptsLocation.y;
		ScreenToClient(hWnd, &_ptFirst);
        if (TouchIsValid(_ptFirst) == false)
            break;
        ProcessTwoFingerTap(_ptFirst);
        break;

    case GID_PRESSANDTAP:
        switch (gi.dwFlags)
        {
        case GF_BEGIN:
			_ptFirst.x = gi.ptsLocation.x;
			_ptFirst.y = gi.ptsLocation.y;
			ScreenToClient(hWnd, &_ptFirst);
            if (TouchIsValid(_ptFirst) == false)
                break;
            ProcessPressAndTap(_ptFirst);
            break;
        }
        break;
    }

	InvalidateRect(hWnd, NULL, FALSE);
    CloseGestureInfoHandle((HGESTUREINFO)lParam);
    return TRUE;
}

void CGestureEngine::ProcessMove(const POINT firstTouchCoord, const POINT finishCoord)
{
    for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
			{
                EKRAN_HANDLER.getDisplayCell(i, j)->Move(firstTouchCoord, finishCoord);
				return;
			}
}

void CGestureEngine::ProcessPressAndTap(const POINT firstTouchCoord)
{
    MessageBox(NULL, L"Press and Tap Gesture", L"Gesture Captured", MB_OK | MB_ICONINFORMATION);
}

void CGestureEngine::ProcessRotate(const POINT firstTouchCoord, const double dAngle, const POINT rotateCenter)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.getDisplayCell(i, j)->Rotate(dAngle, rotateCenter);
				return;
			}
}

void CGestureEngine::ProcessTwoFingerTap(const POINT firstTouchCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.getDisplayCell(i, j)->Reset();
				return;
			}
}

void CGestureEngine::ProcessZoom(const POINT firstTouchCoord, const double dZoomFactor, const POINT zoomCenter)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
			{
				EKRAN_HANDLER.getDisplayCell(i, j)->Zoom(dZoomFactor, zoomCenter);
				return;
			}
}

void CGestureEngine::ProcessSwipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
{
    for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (EKRAN_HANDLER.getDisplayCell(i, j) != nullptr && EKRAN_HANDLER.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
            {
				EKRAN_HANDLER.getDisplayCell(i, j)->Swipe(firstTouchCoord, secondTouchCoord);
				return;
			}
}

bool CGestureEngine::TouchIsValid(const POINT touchCoord)
{
    bool touchIsValid = false;

    if (touchCoord.x > 0 &&
        touchCoord.x < TOUCH_EKRAN_WIDTH &&
        touchCoord.y > MECHANIC_MENU_HEIGHTPX &&
        touchCoord.y < TOUCH_EKRAN_HEIGHT)
        touchIsValid = true;

    return touchIsValid;
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