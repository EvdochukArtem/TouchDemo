#pragma once
#include "../AbstractButton.h"

class CSetTButton : public CAbstractButton
{
public:
	CSetTButton(int x, int y, void(CALLBACK* handler)(MOUSE_EVNT, CSetTButton*));
	~CSetTButton();

	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CSetTButton*);
	bool _enabled;

	void DrawGear(HDC& hdc);

	BLENDFUNCTION	blendFunc;
	HDC				tmpHDC;
	HBITMAP			tmpBITMAP;

	friend class CSetTButtonHandler;
};

