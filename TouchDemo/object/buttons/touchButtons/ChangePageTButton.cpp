#include "stdafx.h"
#include "ChangePageTButton.h"
#include "util/Util.h"

CChangePageTButton::CChangePageTButton(int x, int y, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*)) : CSimpleTButton(x, y, caption, handler)
{
}

CChangePageTButton::~CChangePageTButton(void)
{
}

void CChangePageTButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;

	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.OrangePen);
	oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.BlackBrush);

	Rectangle(tmpHDC, 0, 0, _cx, _cy);

	AlphaBlend(hdc, _x, _y, _cx, _cy, tmpHDC, 0, 0, _cx, _cy, blendFunc);

	SelectObject(tmpHDC, oldPen);
	SelectObject(tmpHDC, oldBrush);

	SelectObject(tmpHDC, hOld);
	DeleteObject(hOld);

	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial12);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10), _caption, (int)_tcslen(_caption));
	
	SetBkMode(hdc, OPAQUE);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
}
