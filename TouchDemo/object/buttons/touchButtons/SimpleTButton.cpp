#include "stdafx.h"
#include "SimpleTButton.h"
#include "util/Util.h"

CSimpleTButton::CSimpleTButton(int x, int y, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*)) :  CAbstractButton(x, y, TBUTTON_SIDE_SIZE, TBUTTON_SIDE_SIZE, caption)
{
	_handler = handler;
	_enabled = false;

	blendFunc.SourceConstantAlpha	= 196;
	blendFunc.AlphaFormat			= 0;
	blendFunc.BlendFlags			= 0;
	blendFunc.BlendOp				= AC_SRC_OVER;
	HDC tmp = GetDC(NULL);
	tmpHDC		= CreateCompatibleDC(tmp);
	tmpBITMAP	= CreateCompatibleBitmap(tmp, _cx, _cy);
	DeleteDC(tmp);
}

CSimpleTButton::~CSimpleTButton()
{
	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
}

void CSimpleTButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;

	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.OrangePen);
	if (_enabled)
		oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.ActiveButtonBrush);
	else
		oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.BlackBrush);

	RoundRect(tmpHDC, 0, 0, _cx, _cy, TO_PIXEL(40), TO_PIXEL(40));

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

void CSimpleTButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}

void CSimpleTButton::DrawBackground()
{
	if (_hidden)
		return;
}