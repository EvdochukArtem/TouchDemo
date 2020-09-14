#pragma once

class CGestureEngineEmulator
{
public:
	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnMouseWheelUp(POINT pt);			//зум+
	void OnMouseWheelDown(POINT pt);		//зум-
	void ProcessMove(const POINT firstCoord, const POINT finishCoord);
	void ProcessKeyboard(UINT key);			//сдвиг (сопоставить с координатами курсора)
	void OnLMouseUp(POINT clickCoord);
	void OnRMouseUp(POINT clickCoord);	//сброс
	void OnMouseRotate(const POINT firstTouchCoord, const double dAngle, const POINT rotateCenter);	//поворот

private:
	CGestureEngineEmulator() {};
	~CGestureEngineEmulator() {};
	BOOL Create() { return TRUE; };

	friend class CUtil;

	POINT _ptBegin;
	POINT _ptFirst;
	POINT _ptSecond;
	DWORD _timer;
	bool EmulateTouchIsValid(const POINT touchCoordEmulate);
};