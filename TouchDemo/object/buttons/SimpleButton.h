#pragma once
#include "AbstractButton.h"

class CSimpleButton : public CAbstractButton
{
public:
	CSimpleButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(BUTTON_EVENT, CSimpleButton*));
	~CSimpleButton() {};
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();
	virtual void RightClickHandle() {};
private:
	void(CALLBACK* _handler)(BUTTON_EVENT, CSimpleButton*);
};