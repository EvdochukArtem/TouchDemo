#include "stdafx.h"
#include "SetTButton.h"
#include "util/Util.h"

CSetTButton::CSetTButton(int x, int y, void(CALLBACK* handler)(MOUSE_EVNT, CSetTButton*)) :  CAbstractButton(x, y, TBUTTON_SIDE_SIZE, TBUTTON_SIDE_SIZE, _T(""))
{
	_handler = handler;
	_enabled = false;

	blendFunc.SourceConstantAlpha	= 196;
	blendFunc.AlphaFormat			= 0;
	blendFunc.BlendFlags			= 0;
	blendFunc.BlendOp				= AC_SRC_OVER;

	HDC tmp = GetDC(NULL);
	tmpHDC		= CreateCompatibleDC(tmp);
	tmpBITMAP	= CreateCompatibleBitmap(tmp, _cx, _cy);
	DeleteDC(tmp);
}

CSetTButton::~CSetTButton()
{
	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
}

//TODO: Надо убрать цветную рамку когда шестеренка будет выглядеть нормально
void CSetTButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;

	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.OrangePen);
	oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.BlackBrush);

	Rectangle(tmpHDC, 0, 0, _cx, _cy);

	AlphaBlend(hdc, _x, _y, _cx, _cy, tmpHDC, 0, 0, _cx, _cy, blendFunc);

	SelectObject(tmpHDC, oldPen);
	SelectObject(tmpHDC, oldBrush);

	SelectObject(tmpHDC, hOld);
	DeleteObject(hOld);

	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.RedPen);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.GreyBrush);
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial13);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);
	
	if (_enabled)
		TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10), _T("ESC"), (int)_tcslen(_T("ESC")));
	
	SetBkMode(hdc, OPAQUE);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
	
	if (!_enabled)
		DrawGear(hdc);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

void CSetTButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}

void CSetTButton::DrawBackground()
{
	if (_hidden)
		return;
}

void CSetTButton::DrawGear(HDC& hdc)
{
	//TODO: Нарисуйте норм шетреренку
	Ellipse(hdc, _x + _cx / 4, _y + _cy / 4, _x + _cx * 3 / 4, _y + _cy * 3 / 4);
}