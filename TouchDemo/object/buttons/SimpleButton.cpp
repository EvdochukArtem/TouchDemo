#include "stdafx.h"
#include "SimpleButton.h"
#include "util/Util.h"

CSimpleButton::CSimpleButton(UINT x, UINT y, UINT cx, UINT cy, LPCTSTR caption, void(CALLBACK* handler)(BUTTON_EVENT, CSimpleButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	_handler = handler;
}

void CSimpleButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2, _caption, (int)_tcslen(_caption));
	SetTextAlign(hdc, oldTextAlign);
	/*oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.PurplePen);
	DrawBorders(hdc);
	SelectObject(hdc, oldPen);*/
}

CSimpleButton* CSimpleButton::ChangePos(UINT x, UINT y)
{
	_x = x;
	_y = y;
	return this;
}

void CSimpleButton::DrawBackground()
{
	if (_hidden)
		return;
}

void CSimpleButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
		_handler(LM_DOWN, this);
}