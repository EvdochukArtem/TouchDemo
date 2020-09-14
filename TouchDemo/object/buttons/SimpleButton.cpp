#include "stdafx.h"
#include "SimpleButton.h"
#include "util/Util.h"

CSimpleButton::CSimpleButton(UINT x, UINT y, UINT cx, UINT cy, LPCWSTR caption) : CAbstractButton(x, y, cx, cy, caption)
{}

void CSimpleButton::Draw(HDC hdc)
{
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2, _caption, _tcslen(_caption));
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.RedPen2);
	DrawBorders(hdc);
	SelectObject(hdc, oldPen);
	SetTextAlign(hdc, oldTextAlign);
}

void CSimpleButton::DrawBackground()
{}

void CSimpleButton::LeftClickHandle()
{
	MessageBox(NULL, _caption, L"", MB_OK);
}

void CSimpleButton::RightClickHandle() {}