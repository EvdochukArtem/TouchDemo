#pragma once
#include "../AbstractButton.h"

class CSimpleButton : public CAbstractButton
{
public:
	CSimpleButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleButton*));
	//Если потом понадобится задавать состояние кнопки:
	//CSimpleButton(int x, int y, int cx, int cy, LPCTSTR caption, bool enabled, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleButton*));
	~CSimpleButton() {};
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CSimpleButton*);

	friend class CSimpleButtonHandler;
};