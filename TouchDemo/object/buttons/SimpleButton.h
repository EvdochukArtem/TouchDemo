#pragma once
#include "AbstractButton.h"

class CSimpleButton : public CAbstractButton
{
public:
	CSimpleButton(UINT x, UINT y, UINT cx, UINT cy, LPCTSTR caption, void(CALLBACK* handler)(BUTTON_EVENT, CSimpleButton*));
	~CSimpleButton() {};
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();
	CSimpleButton* ChangePos(UINT x, UINT y);
private:
	void(CALLBACK* _handler)(BUTTON_EVENT, CSimpleButton*);
};