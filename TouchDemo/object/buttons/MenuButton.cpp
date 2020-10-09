#include "stdafx.h"
#include "MenuButton.h"
#include "util/Util.h"

CMenuButton::CMenuButton(UINT x, UINT y, UINT cx, UINT cy, LPCWSTR caption) : CAbstractButton(x, y, cx, cy, caption)
{
	isActive = false;
	isSOI = false;
}

void CMenuButton::Draw(HDC hdc)
{
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10), _caption, (int)_tcslen(_caption));
	SetTextAlign(hdc, oldTextAlign);
	/*
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreenPen2);
	DrawBorders(hdc);
	SelectObject(hdc, oldPen);
	*/
}

void CMenuButton::DrawBackground()
{
	if (!isActive)
		return;
	if (isSOI)
		oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.YellowPen3);
	else
		oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
	DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CMenuButton::LeftClickHandle()
{
	if (!isActive)
		Activate();
	else
	{
		POINT pt = {_x + _cx / 2,_y + _cy / 2};
		EKRAN_HANDLER.SetSOI(pt);
	}
	//MessageBox(NULL, _caption, L"", MB_OK);
}

void CMenuButton::Activate()
{
	_prior = ACTIVE;
	DRAW_ENGINE.ResetDrawingObject(this);
	isActive = true;
}

void CMenuButton::Disactivate()
{
	_prior = MAX;
	DRAW_ENGINE.ResetDrawingObject(this);
	isActive = false;
	SwitchSOI(false);
}

void CMenuButton::SwitchSOI(bool soi)
{
	if (soi)
	{
		_prior = SOI;
		DRAW_ENGINE.ResetDrawingObject(this);
		isActive = true;
		isSOI = true;
	}
	else 
	{
		_prior = ACTIVE;
		DRAW_ENGINE.ResetDrawingObject(this);
		isSOI = false;
	}
}

CMenuButton* CMenuButton::ChangePos(UINT x, UINT y)
{
	_x = x;
	_y = y;
	return this;
}