/*
*	Класс получает и обрабатывает сообщения с данными о вводе с клавиатуры или мыши из главного файла программы.
*/
#pragma once
#ifdef DEBUG
const double CLICK_TIME = 100.0;
#else
const double CLICK_TIME = 250.0;
#endif


class CGestureEngineEmulator
{
public:
	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnMouseWheelUp(POINT pt);													//зум+
	void OnMouseWheelDown(POINT pt);												//зум-
	void ProcessMove(POINT beginCoord, POINT startCoord, POINT delta);	
	void ProcessKeyboard(WPARAM key);												//сдвиг (сопоставить с координатами курсора)
	void OnLMouseDown(POINT clickCoord);
	void OnLMouseUp(POINT clickCoord);
	void OnRMouseUp(POINT clickCoord);												//сброс
	void OnMouseRotate(POINT firstTouchCoord, double dAngle, POINT rotateCenter);	//поворот
#ifdef DEBUG
	bool pixelCheck;
#endif
	bool GetLButtonStatus() { return _lButtonPressed; };
	bool GetLClickSteady() { return _lClickSteady; };
	int  GetLButtonTimer() { return GetTickCount() - _lButtonTimer; };

private:
	CGestureEngineEmulator();
	~CGestureEngineEmulator() {};
	BOOL Create() { return TRUE; };
	BOOL CleanUp() { return TRUE; };

	friend class CUtil;

	POINT	_ptBegin;
    POINT	_ptFirst;    
    POINT	_ptSecond;
	int		_lButtonTimer;
	bool	_lButtonPressed;
	bool	_lClickSteady;

    bool EmulateTouchInKadrSpace(const POINT touchCoordEmulate);
};
