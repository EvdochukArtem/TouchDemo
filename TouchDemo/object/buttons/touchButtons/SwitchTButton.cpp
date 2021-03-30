#include "stdafx.h"
#include "SwitchTButton.h"
#include "util/Util.h"

CSwitchTButton::CSwitchTButton(int x, int y, LPCTSTR caption, bool firstStatusActive, void(CALLBACK* handler)(MOUSE_EVNT, CSwitchTButton*)) :  CAbstractButton(x, y, TBUTTON_SIDE_SIZE, TBUTTON_SIDE_SIZE, caption)
{
	_handler = handler;
	this->firstStatusActive = firstStatusActive;

	_tcscpy_s(pos1, _caption);
	_tcscpy_s(pos2, _T(""));

	blendFunc.SourceConstantAlpha	= 196;
	blendFunc.AlphaFormat			= 0;
	blendFunc.BlendFlags			= 0;
	blendFunc.BlendOp				= AC_SRC_OVER;

	HDC tmp = GetDC(NULL);
	tmpHDC		= CreateCompatibleDC(tmp);
	tmpBITMAP	= CreateCompatibleBitmap(tmp, _cx, _cy);
	DeleteDC(tmp);
}

CSwitchTButton::CSwitchTButton(int x, int y, LPCTSTR firstStatus, LPCTSTR secondStatus, bool firstStatusActive, void(CALLBACK* handler)(MOUSE_EVNT, CSwitchTButton*)) :  CAbstractButton(x, y, TBUTTON_SIDE_SIZE, TBUTTON_SIDE_SIZE, _T(""))
{
	_handler = handler;
	this->firstStatusActive = firstStatusActive;

	_tcscpy_s(pos1, firstStatus);
	_tcscpy_s(pos2, secondStatus);

	blendFunc.SourceConstantAlpha	= 196;
	blendFunc.AlphaFormat			= 0;
	blendFunc.BlendFlags			= 0;
	blendFunc.BlendOp				= AC_SRC_OVER;

	tmpHDC		= CreateCompatibleDC(GetDC(NULL));
	tmpBITMAP	= CreateCompatibleBitmap(GetDC(NULL), _cx, _cy);
}

CSwitchTButton::~CSwitchTButton(void)
{
	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
}

void CSwitchTButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;

	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.OrangePen);
	oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.BlackBrush);

	RoundRect(tmpHDC, 0, 0, _cx, _cy, TO_PIXEL(40), TO_PIXEL(40));

	AlphaBlend(hdc, _x, _y, _cx, _cy, tmpHDC, 0, 0, _cx, _cy, blendFunc);

	SelectObject(tmpHDC, oldPen);
	SelectObject(tmpHDC, oldBrush);

	SelectObject(tmpHDC, hOld);
	DeleteObject(hOld);

	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial13);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);
	
	if (_tcscmp(pos2, _T("")) == 0)
	{
		TextOut(hdc, _x + _cx / 2, _y + _cy / 2, _caption, (int)_tcslen(_caption));
		SelectObject(hdc, DRAW_KIT.Arial12);
		if (!firstStatusActive)
		{
			SetTextColor(hdc, DRAW_KIT.GetGreyColor());
			TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(25), _T("¬€ À"), 4);
		} else {
			SetTextColor(hdc, DRAW_KIT.GetGreenColor());
			TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(25), _T("¬ À"), 3);
		}
	} else {
		if (firstStatusActive)
		{
			TextOut(hdc, _x + _cx / 2, _y + _cy / 2, pos1, (int)_tcslen(pos1));
			SetTextColor(hdc, DRAW_KIT.GetGreyColor());
			SelectObject(hdc, DRAW_KIT.Arial12);
			TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(25), pos2, (int)_tcslen(pos2));
		} else {
			SetTextColor(hdc, DRAW_KIT.GetGreyColor());
			SelectObject(hdc, DRAW_KIT.Arial12);
			TextOut(hdc, _x + _cx / 2, _y + _cy / 2, pos1, (int)_tcslen(pos1));
			SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
			SelectObject(hdc, DRAW_KIT.Arial13);
			TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(25), pos2, (int)_tcslen(pos2));
		}
	}
	
	SetBkMode(hdc, OPAQUE);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
	
}

void CSwitchTButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}

void CSwitchTButton::DrawBackground()
{
	if (_hidden)
		return;
}