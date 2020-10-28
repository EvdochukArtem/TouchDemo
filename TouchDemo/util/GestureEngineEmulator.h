/*
*	����� �������� � ������������ ��������� � ������� � ����� � ���������� ��� ���� �� �������� ����� ���������.
*/
#pragma once

class CGestureEngineEmulator
{
public:
	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnMouseWheelUp(POINT pt);													//���+
	void OnMouseWheelDown(POINT pt);												//���-
	void ProcessMove(POINT beginCoord, POINT firstCoord, POINT finishCoord);	
	void ProcessKeyboard(WPARAM key);												//����� (����������� � ������������ �������)
	void OnLMouseUp(POINT clickCoord);
	void OnRMouseUp(POINT clickCoord);												//�����
	void OnMouseRotate(POINT firstTouchCoord, double dAngle, POINT rotateCenter);	//�������
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
