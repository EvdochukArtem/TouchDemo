#include "stdafx.h"
#include "RadioButton.h"
#include "util/Util.h"

std::vector<CRadioButton*> CRadioButton::allRadioButtons;

//Вообще конечно по-хорошему надо кнопку создавать не в конструткоре а в методе Create на случай если кнопка с таким именем в этой группе уже есть.
CRadioButton::CRadioButton(int x, int y, int cx, int cy, LPCTSTR caption, LPCTSTR groupName, CMechanicMenu::CLoMenu* parentMenu, void(CALLBACK* handler)(MOUSE_EVNT, CRadioButton*)) : CAbstractButton(x, y, cx, cy, caption)
{
	_tcscpy_s(_groupName, groupName);
	_parentMenu = parentMenu;
	_handler = handler;
	std::vector<CRadioButton*> rButtonsGroup;
	for (CRadioButton* button : CRadioButton::allRadioButtons)
		if (_tcscmp(button->_groupName, _groupName) == 0 && _parentMenu == button->_parentMenu)
			rButtonsGroup.push_back(button);
	if (rButtonsGroup.size() == 0)
		_enabled = true;
	else
		_enabled = false;

	allRadioButtons.push_back(this);
}

CRadioButton::~CRadioButton()
{
	std::vector<CRadioButton*>::iterator it = std::find(CRadioButton::allRadioButtons.begin(), CRadioButton::allRadioButtons.end(), this);
	if (_enabled)
	{
		_enabled = false;
		std::vector<CRadioButton*> rButtonsGroup;
		for (CRadioButton* button : CRadioButton::allRadioButtons)
			if (_tcscmp(button->_groupName, _groupName) == 0 && _parentMenu == button->_parentMenu)
				rButtonsGroup.push_back(button);
		rButtonsGroup.at(0)->_enabled = true;
	}
	CRadioButton::allRadioButtons.erase(it);
}

void CRadioButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;
}

void CRadioButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}

void CRadioButton::DrawBackground()
{
	if (_hidden)
		return;
	oldTextAlign = SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.Arial10b);
	oldColor = SetTextColor(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GetWhiteColor());
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), TRANSPARENT);
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.ActiveButtonPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.ActiveButtonBrush);

	if (_enabled)
	{
		int indentX = TO_PIXEL(10);
		int indentY = TO_PIXEL(2);
		Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x + indentX, _y, _x + _cx - indentX, _y + _cy - 2 * indentY);
	}

	TextOut(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), _caption, (int)_tcslen(_caption));
	
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), OPAQUE);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), oldTextAlign);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldFont);
	SetTextColor(DRAW_ENGINE.getBackgroundHDC(), oldColor);
}