#include "stdafx.h"
#include "SwitchButton.h"
#include "util/Util.h"


CSwitchButton::CSwitchButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSwitchButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	_handler = handler;
	enabled = false;
}

void CSwitchButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;
}

void CSwitchButton::DrawBackground()
{
	if (_hidden)
		return;
	oldTextAlign = SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.Arial10b);
	oldColor = SetTextColor(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GetWhiteColor());
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), TRANSPARENT);
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.ActiveButtonPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.ActiveButtonBrush);

	if (enabled)
	{
		int indentX = TO_PIXEL(10);
		int indentY = TO_PIXEL(2);
		Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x + indentX, _y, _x + _cx - indentX, _y + _cy - 2 * indentY);
	}

	TextOut(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), _caption, (int)_tcslen(_caption));
	
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), OPAQUE);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), oldTextAlign);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldFont);
	SetTextColor(DRAW_ENGINE.getBackgroundHDC(), oldColor);
}

void CSwitchButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}