#pragma once
#include "../AbstractButton.h"

//TODO: Подумать! Может стоит разделить радиокнопку на 2: тумблер вкл/выкл и тумблер поз1/поз2
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

	/*int		GetStatus() { return (firstStatusActive) ? 1 : 0; }; //1 если кнопка включена или находится в первом положении, 0 если выключена или во второй позиции
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