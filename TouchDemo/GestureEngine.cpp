#include "GestureEngine.h"
#include <math.h>
#include "KadrHandler.h"

#define _USE_MATH_DEFINES
#define KADR_BORDER 20
#define EKRAN_WIDTH GetSystemMetrics(SM_CXSCREEN) - KADR_BORDER
#define EKRAN_HEIGHT GetSystemMetrics(SM_CYSCREEN) - KADR_BORDER

// One of the fields in GESTUREINFO structure is type of ULONGLONG (8 bytes).
// The relevant gesture information is stored in lower 4 bytes. This
// macro is used to read gesture information from this field.
#define LODWORD(ull) ((DWORD)((ULONGLONG)(ull) & 0x00000000ffffffff))

extern CKadrHandler kadrHandler;

CGestureEngine::CGestureEngine() : _dwArguments(0) {}

LRESULT CGestureEngine::WndProc(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // helper variables
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
            ProcessZoom(_ptFirst, k, ptZoomCenter.x, ptZoomCenter.y);

            InvalidateRect(hWnd, NULL, TRUE);

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
            break;
		case GF_END:
			_dwArguments = LODWORD(gi.ullArguments);
            if (_dwArguments != 0)
            {
                _ptSecond.x = gi.ptsLocation.x;
                _ptSecond.y = gi.ptsLocation.y;
				ScreenToClient(hWnd, &_ptSecond);
                if (TouchIsValid(_ptSecond) == false)
                    break;
                ProcessSwipe(_ptFirst, _ptSecond);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        default:
            if (gi.ullArguments == 0)
            {
                _ptSecond.x = gi.ptsLocation.x;
                _ptSecond.y = gi.ptsLocation.y;
                    ScreenToClient(hWnd, &_ptSecond);
                if (TouchIsValid(_ptSecond) == false)
                    break;
				ProcessMove(_ptFirst, _ptSecond.x - _ptFirst.x, _ptSecond.y - _ptFirst.y);
                InvalidateRect(hWnd, NULL, TRUE);
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
                _ptFirst.x, _ptFirst.y
            );
            InvalidateRect(hWnd, NULL, TRUE);
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
        InvalidateRect(hWnd, NULL, TRUE);
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
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    }

    CloseGestureInfoHandle((HGESTUREINFO)lParam);

    return TRUE;
}

void CGestureEngine::ProcessMove(const POINT firstTouchCoord, const LONG ldx, const LONG ldy)
{
    for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (kadrHandler.getDisplayCell(i, j) != NULL && kadrHandler.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
                kadrHandler.getDisplayCell(i, j)->Move(firstTouchCoord, ldx, ldy);
}

void CGestureEngine::ProcessPressAndTap(const POINT firstTouchCoord)
{
    MessageBox(NULL, L"Press and Tap Gesture", L"Gesture Captured", MB_OK | MB_ICONINFORMATION);
}

void CGestureEngine::ProcessRotate(const POINT firstTouchCoord, const double dAngle, const LONG lOx, const LONG lOy)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (kadrHandler.getDisplayCell(i, j) != NULL && kadrHandler.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
				kadrHandler.getDisplayCell(i, j)->Rotate(dAngle, lOx, lOy);
}

void CGestureEngine::ProcessTwoFingerTap(const POINT firstTouchCoord)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (kadrHandler.getDisplayCell(i, j) != NULL && kadrHandler.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
				kadrHandler.getDisplayCell(i, j)->ResetInteractiveObject();
}

void CGestureEngine::ProcessZoom(const POINT firstTouchCoord, const double dZoomFactor, const LONG lZx, const LONG lZy)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (kadrHandler.getDisplayCell(i, j) != NULL && kadrHandler.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
				kadrHandler.getDisplayCell(i, j)->Zoom(dZoomFactor, lZx, lZy);    
}

void CGestureEngine::ProcessSwipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
{
    for (int i = 0; i < DISPLAY_ROWS; i++)
        for (int j = 0; j < DISPLAY_COLS; j++)
            if (kadrHandler.getDisplayCell(i, j) != NULL && kadrHandler.getDisplayCell(i, j)->PointIsMine(firstTouchCoord))
                kadrHandler.getDisplayCell(i, j)->Swipe(firstTouchCoord, secondTouchCoord);
}

bool CGestureEngine::TouchIsValid(const POINT touchCoord)
{
    bool touchIsValid = false;

    if (touchCoord.x > KADR_BORDER &&
        touchCoord.x < EKRAN_WIDTH &&
        touchCoord.y > KADR_BORDER &&
        touchCoord.y < EKRAN_HEIGHT)
        touchIsValid = true;

    return touchIsValid;
}