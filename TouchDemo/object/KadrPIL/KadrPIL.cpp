#include "stdafx.h"
#include "KadrPIL.h"
#include "util/Util.h"

CKadrPIL::CKadrPIL(UINT id, KADR_SIZE kadrSize) : CKadr(id, kadrSize)
{
	_kadrType = PLD;
}

void CKadrPIL::Draw(HDC& hdc)
{
	if (_blocked)
		return;
	::TextOut(hdc, _x+_cx/2, _y+_cy/2, L"PIL KADR", 9);
}

void CKadrPIL::DrawBackground()
{
	if (_blocked)
		return;
	//���
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