#pragma once
#include "../AbstractButton.h"

class CSimpleTButton : public CAbstractButton
{
public:
	CSimpleTButton(int x, int y, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*));
	//Если потом понадобится задавать состояние кнопки:
	//CSimpleTButton(int x, int y, LPCTSTR caption, bool enabled, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*));
	~CSimpleTButton();
	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();

protected:
	void(CALLBACK* _handler)(MOUSE_EVNT, CSimpleTButton*);
	bool _enabled;

	BLENDFUNCTION	blendFunc;
	HDC				tmpHDC;
	HBITMAP			tmpBITMAP;

	friend class CSimpleTButtonHandler;
	friend class CMenuTButtonHandler;
};

