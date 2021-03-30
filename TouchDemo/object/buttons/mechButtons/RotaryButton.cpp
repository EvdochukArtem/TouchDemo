#include "stdafx.h"
#include "RotaryButton.h"
#include "RotaryButtonHandler.h"
#include "ParamButton.h"
#include "util/Util.h"

CRotaryButton::CRotaryButton(int x, int y, int cx, int cy) : CAbstractButton(x, y, cx, cy, _T(""))
{
	enabled = false;
	_handler = nullptr;
}

//TODO: Добавить ползунок регулировки как альтернатива прокрутки колесиком мышки
void CRotaryButton::Draw(HDC& hdc)
{
	if (_hidden || !enabled)
		return;

	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial10b);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.ActiveButtonPen);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.ActiveButtonBrush);

	int indentX = TO_PIXEL(10);
	int indentY = TO_PIXEL(2);
	Rectangle(hdc, _x + indentX, _y, _x + _cx - indentX, _y + _cy - 2 * indentY);
	LPCTSTR tmp = paramBtn->GetActiveValue().ToString();
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), tmp, (int)_tcslen(tmp));
	
	SetBkMode(hdc, OPAQUE);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
}

void CRotaryButton::DrawBackground()
{
	if (_hidden)
		return;
}

void CRotaryButton::LeftClickHandle()
{
	if (_hidden || _handler == nullptr)
		return;
	if (paramBtn == nullptr)
		return;
	_handler(M_EVNT_LB_DOWN, this);
}

void CRotaryButton::MouseWheelHandle(double scrollFactor)
{
	if (_hidden || _handler == nullptr)
		return;
	if (paramBtn == nullptr)
		return;
	if (1 > scrollFactor)
	{
		_handler(M_EVNT_WHEEL_DOWN, this);
	}
	else
	{
		_handler(M_EVNT_WHEEL_UP, this);
	}
}

void CRotaryButton::AttachParamButton(CParamButton* btn)
{
	enabled = true;
	paramBtn = btn;
	_handler = btn->rotaryHandler;
}

void CRotaryButton::DeAttachParamButton()
{
	enabled = false;
	paramBtn = nullptr;
	_handler = nullptr;
}