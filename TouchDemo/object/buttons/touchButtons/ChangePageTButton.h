#pragma once
#include "SimpleTButton.h"

class CChangePageTButton : public CSimpleTButton
{
public:
	CChangePageTButton(int x, int y, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*));
	~CChangePageTButton();
	void Draw(HDC& hdc);
};

