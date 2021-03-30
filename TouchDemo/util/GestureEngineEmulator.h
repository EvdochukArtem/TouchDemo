/*
*	����� �������� � ������������ ��������� � ������� � ����� � ���������� ��� ���� �� �������� ����� ���������.
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
	void OnMouseWheelUp(POINT pt);													//���+
	void OnMouseWheelDown(POINT pt);												//���-
	void ProcessMove(POINT beginCoord, POINT startCoord, POINT delta);	
	void ProcessKeyboard(WPARAM key);												//����� (����������� � ������������ �������)
	void OnLMouseDown(POINT clickCoord);
	void OnLMouseUp(POINT clickCoord);
	void OnRMouseUp(POINT clickCoord);												//�����
	void OnMouseRotate(POINT firstTouchCoord, double dAngle, POINT rotateCenter);	//�������
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
