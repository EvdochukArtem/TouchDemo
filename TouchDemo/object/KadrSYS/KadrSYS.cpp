#include "stdafx.h"
#include "KadrSYS.h"
#include "util/Util.h"

CKadrSYS::CKadrSYS(UINT id, KADR_SIZE kadrSize) : CKadr(id, kadrSize)
{
	_kadrType = SYST;
}

void CKadrSYS::Draw(HDC& hdc)
{
	if (_blocked)
		return;
	::TextOut(hdc, _x+_cx/2, _y+_cy/2, L"SYSTEM KADR", 12);
}

void CKadrSYS::DrawBackground()
{
	if (_blocked)
		return;
	//‘ÓÌ
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	if (_id / 4 == 1 && _kadrSize == EIGHTH)
	{
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
		DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	}
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}