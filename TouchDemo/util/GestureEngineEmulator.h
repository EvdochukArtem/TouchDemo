/*
*	Класс получает и обрабатывает сообщения с данными о вводе с клавиатуры или мыши из главного файла программы.
*/
#pragma once

class CGestureEngineEmulator
{
public:
	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnMouseWheelUp(POINT pt);													//зум+
	void OnMouseWheelDown(POINT pt);												//зум-
	void ProcessMove(POINT beginCoord, POINT firstCoord, POINT finishCoord);	
	void ProcessKeyboard(WPARAM key);												//сдвиг (сопоставить с координатами курсора)
	void OnLMouseUp(POINT clickCoord);
	void OnRMouseUp(POINT clickCoord);												//сброс
	void OnMouseRotate(POINT firstTouchCoord, double dAngle, POINT rotateCenter);	//поворот
#ifdef DEBUG
	bool pixelCheck;
#endif
	bool GetLButtonStatus() { return _lButtonPressed; };
private:
	CGestureEngineEmulator();
	~CGestureEngineEmulator() {};
	BOOL Create() { return TRUE; };

	friend class CUtil;

	POINT _ptBegin;
    POINT _ptFirst;    
    POINT _ptSecond;
	int _timer;
    bool EmulateTouchIsValid(const POINT touchCoordEmulate);
	bool  _lButtonPressed;
};
