#include "stdafx.h"
#include "SimpleButton.h"
#include "util/Util.h"

CSimpleButton::CSimpleButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	_handler = handler;
}

/*CSimpleButton::CSimpleButton(int x, int y, int cx, int cy, LPCTSTR caption, bool enabled, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	_handler = handler;
	this->enabled = enabled;
}*/

void CSimpleButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;
}

void CSimpleButton::DrawBackground()
{
	if (_hidden)
		return;
	oldTextAlign = SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.Arial10b);
	oldColor = SetTextColor(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GetWhiteColor());
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), TRANSPARENT);
	
	TextOut(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), _caption, (int)_tcslen(_caption));

	SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), oldTextAlign);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldFont);
	SetTextColor(DRAW_ENGINE.getBackgroundHDC(), oldColor);
}

void CSimpleButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}