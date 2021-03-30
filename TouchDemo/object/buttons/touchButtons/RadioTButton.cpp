#include "stdafx.h"
#include "RadioTButton.h"
#include "util/Util.h"

std::vector<CRadioTButton*> CRadioTButton::allRadioTButtons;

//Вообще конечно по-хорошему надо кнопку создавать не в конструткоре а в методе Create на случай если кнопка с таким именем в этой группе уже есть.
CRadioTButton::CRadioTButton(int x, int y, LPCTSTR caption, LPCTSTR groupName, CAbstractKadr* parentKadr, void(CALLBACK* handler)(MOUSE_EVNT, CRadioTButton*)) :  CAbstractButton(x, y, TBUTTON_SIDE_SIZE, TBUTTON_SIDE_SIZE, caption)
{
	_tcscpy_s(_groupName, groupName);
	_parentKadr = parentKadr;
	_handler = handler;
	std::vector<CRadioTButton*> rButtonsGroup;
	for (CRadioTButton* button : CRadioTButton::allRadioTButtons)
		if (_tcscmp(button->_groupName, _groupName) == 0 && _parentKadr == button->_parentKadr)
			rButtonsGroup.push_back(button);
	if (rButtonsGroup.size() == 0)
		_enabled = true;
	else
		_enabled = false;

	allRadioTButtons.push_back(this);

	blendFunc.SourceConstantAlpha	= 196;
	blendFunc.AlphaFormat			= 0;
	blendFunc.BlendFlags			= 0;
	blendFunc.BlendOp				= AC_SRC_OVER;

	HDC tmp = GetDC(NULL);
	tmpHDC		= CreateCompatibleDC(tmp);
	tmpBITMAP	= CreateCompatibleBitmap(tmp, _cx, _cy);
	DeleteDC(tmp);
}

CRadioTButton::~CRadioTButton()
{
	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
	std::vector<CRadioTButton*>::iterator it = std::find(CRadioTButton::allRadioTButtons.begin(), CRadioTButton::allRadioTButtons.end(), this);
	if (_enabled)
	{
		_enabled = false;
		std::vector<CRadioTButton*> rButtonsGroup;
		for (CRadioTButton* button : CRadioTButton::allRadioTButtons)
			if (_tcscmp(button->_groupName, _groupName) == 0 && _parentKadr == button->_parentKadr)
				rButtonsGroup.push_back(button);
		rButtonsGroup.at(0)->_enabled = true;
	}
	CRadioTButton::allRadioTButtons.erase(it);
}

void CRadioTButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;

	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.OrangePen);
	if (_enabled)
		oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.ActiveButtonBrush);
	else
		oldBrush = (HBRUSH)SelectObject(tmpHDC, DRAW_KIT.BlackBrush);

	RoundRect(tmpHDC, 0, 0, _cx, _cy, TO_PIXEL(40), TO_PIXEL(40));

	AlphaBlend(hdc, _x, _y, _cx, _cy, tmpHDC, 0, 0, _cx, _cy, blendFunc);

	SelectObject(tmpHDC, oldPen);
	SelectObject(tmpHDC, oldBrush);

	SelectObject(tmpHDC, hOld);
	DeleteObject(hOld);

	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial12);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10), _caption, (int)_tcslen(_caption));
	
	SetBkMode(hdc, OPAQUE);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
}

void CRadioTButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}

void CRadioTButton::DrawBackground()
{
	if (_hidden)
		return;
}