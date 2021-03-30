#include "stdafx.h"
#include "TabButton.h"
#include "util/Util.h"

CTabButton::CTabButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CTabButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	isActive = false;
	isSOI = false;
	_handler = handler;
}

void CTabButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;

	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial10b);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetBlackColor());

	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10), _caption, (int)_tcslen(_caption));
	SetTextAlign(hdc, oldTextAlign);
	
	SelectObject(hdc, oldFont);
	SetTextAlign(hdc, oldTextAlign);
	SetTextColor(hdc, oldColor);
	/*oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreenPen);
	DrawBorders(hdc);
	MoveToEx(hdc, _x, Y0_PX + _cy, NULL);
	LineTo(hdc, _x, Y0_PX + HEIGHTPX);
	MoveToEx(hdc, _x + _cx, Y0_PX + _cy, NULL);
	LineTo(hdc, _x + _cx, Y0_PX + HEIGHTPX);
	SelectObject(hdc, oldPen);*/
	
}

void CTabButton::DrawBackground()
{
	if (_hidden)
		return;
	if (!isActive)
		return;
}

void CTabButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (!isActive)
	{
		if (_handler)
			_handler(M_EVNT_LB_DOWN, this);
	}	
	else
	{
		POINT pt = {_x + _cx / 2,_y + _cy / 2};
		EKRAN_HANDLER.SetSOI(pt);
	}
	//MessageBox(NULL, _caption, L"", MB_OK);
}

void CTabButton::Activate()
{
	_prior = PRIOR_ACTIVE;
	DRAW_ENGINE.ResetDrawingObject(this);
	isActive = true;
}

void CTabButton::Disactivate()
{
	_prior = PRIOR_MAX;
	DRAW_ENGINE.ResetDrawingObject(this);
	isActive = false;
	SwitchSOI(false);
}

void CTabButton::SwitchSOI(bool soi)
{
	if (soi)
	{
		_prior = PRIOR_SOI;
		DRAW_ENGINE.ResetDrawingObject(this);
		isActive = true;
		isSOI = true;
	}
	else 
	{
		_prior = PRIOR_ACTIVE;
		DRAW_ENGINE.ResetDrawingObject(this);
		isSOI = false;
	}
}