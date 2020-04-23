#pragma once

#include <windows.h>

class CGestureEngine
{
public:
	CGestureEngine();
	~CGestureEngine() {};

	LRESULT WndProc(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void ProcessPressAndTap(const POINT firstTouchCoord);
    void ProcessTwoFingerTap(const POINT firstTouchCoord);
    void ProcessZoom(const POINT firstTouchCoord, const double dZoomFactor, const LONG lZx, const LONG lZy);
    void ProcessMove(const POINT firstTouchCoord, const LONG ldx, const LONG ldy);
    void ProcessSwipe(const POINT firstTouchCoord, const POINT secondTouchCoord);
    void ProcessRotate(const POINT firstTouchCoord, const double dAngle, const LONG lOx, const LONG lOy);

private:
    POINT _ptFirst;        // first significant point of the gesture
    POINT _ptSecond;       // second significant point of the gesture
    DWORD _dwArguments;    // 4 bytes long argument
    bool TouchIsValid(const POINT touchCoord);
};