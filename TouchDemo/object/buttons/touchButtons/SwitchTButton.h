#pragma once
#include "../AbstractButton.h"

//TODO: ��������! ����� ����� ��������� ����������� �� 2: ������� ���/���� � ������� ���1/���2
class CSwitchTButton : public CAbstractButton
{
public:
	CSwitchTButton(int x, int y, LPCTSTR caption, bool firstStatusActive, void(CALLBACK* handler)(MOUSE_EVNT, CSwitchTButton*));
	CSwitchTButton(int x, int y, LPCTSTR firstStatus, LPCTSTR secondStatus, bool firstStatusActive, void(CALLBACK* handler)(MOUSE_EVNT, CSwitchTButton*));
	~CSwitchTButton();

	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();

	void SetFirstStatus()	{ firstStatusActive = true; };
	void SetSecondStatus()	{ firstStatusActive = false; };

	/*int		GetStatus() { return (firstStatusActive) ? 1 : 0; }; //1 ���� ������ �������� ��� ��������� � ������ ���������, 0 ���� ��������� ��� �� ������ �������
	void	SwitchStatus() { firstStatusActive = !firstStatusActive; };*/

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CSwitchTButton*);

	bool firstStatusActive;
	TCHAR pos1 [128];
	TCHAR pos2 [128];

	BLENDFUNCTION	blendFunc;
	HDC				tmpHDC;
	HBITMAP			tmpBITMAP;

	friend class CSwitchTButtonHandler;
};