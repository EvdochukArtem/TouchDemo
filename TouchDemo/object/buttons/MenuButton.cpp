#include "stdafx.h"
#include "MenuButton.h"
#include "util/Util.h"

CMenuButton::CMenuButton(UINT x, UINT y, UINT cx, UINT cy, LPCWSTR caption) : CAbstractButton(x, y, cx, cy, caption)
{
	isSOI = false;
}

void CMenuButton::Draw(HDC hdc)
{
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2, _caption, _tcslen(_caption));
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreenPen2);
	DrawBorders(hdc);
	SelectObject(hdc, oldPen);
	SetTextAlign(hdc, oldTextAlign);
}

void CMenuButton::DrawBackground()
{}

void CMenuButton::LeftClickHandle()
{
	if (!isSOI)
		SwitchSOI();
	//MessageBox(NULL, _caption, L"", MB_OK);
}

void CMenuButton::SwitchSOI()
{
	isSOI = !isSOI;
}

void CMenuButton::RightClickHandle() {}