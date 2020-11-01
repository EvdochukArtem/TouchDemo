#include "stdafx.h"
#include "MenuButton.h"
#include "util/Util.h"

CMenuButton::CMenuButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(BUTTON_EVENT, CMenuButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	isActive = false;
	isSOI = false;
	_handler = handler;
}

void CMenuButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10), _caption, (int)_tcslen(_caption));
	SetTextAlign(hdc, oldTextAlign);
	
	/*oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreenPen);
	DrawBorders(hdc);
	MoveToEx(hdc, _x,_cy, NULL);
	LineTo(hdc, _x, HEIGHTPX);
	MoveToEx(hdc, _x + _cx, _cy, NULL);
	LineTo(hdc, _x + _cx, HEIGHTPX);
	SelectObject(hdc, oldPen);*/
	
}

void CMenuButton::DrawBackground()
{
	if (_hidden)
		return;
	if (!isActive)
		return;
}

void CMenuButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (!isActive)
	{
		if (_handler)
			_handler(LM_DOWN, this);//Activate();
	}	
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

CMenuButton* CMenuButton::ChangePos(int x, int y)
{
	_x = x;
	_y = y;
	return this;
}