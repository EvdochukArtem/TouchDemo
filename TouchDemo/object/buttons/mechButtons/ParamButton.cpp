#include "stdafx.h"
#include "ParamButton.h"
#include "ParamButtonHandler.h"
#include "util/Util.h"
#include "time.h"

std::vector<CParamButton*> CParamButton::allParamButtons;

CParamButton::CParamButton(int x, int y, int cx, int cy, LPCTSTR caption,
						   Value value, void(CALLBACK* rotaryHandler)(MOUSE_EVNT, CRotaryButton*))
						   : CAbstractButton(x, y, cx, cy, caption)
{
	_handler = CParamButtonHandler::OnParamButtonPress;
	enabled = false;
	activeValue = 0;
	values.push_back(value);
	this->rotaryHandler = rotaryHandler;
	lastActivityTime = 0;

	allParamButtons.push_back(this);
}

CParamButton::CParamButton(int x, int y, int cx, int cy, LPCTSTR caption,
						   std::vector <Value>& value, void(CALLBACK* rotaryHandler)(MOUSE_EVNT, CRotaryButton*))
						   : CAbstractButton(x, y, cx, cy, caption)
{
	_handler = CParamButtonHandler::OnParamButtonPress;
	enabled = false;
	activeValue = 0;
	values = value;
	this->rotaryHandler = rotaryHandler;
	lastActivityTime = 0;

	allParamButtons.push_back(this);
}

CParamButton::~CParamButton()
{
	values.clear();
	std::vector<CParamButton*>::iterator it = std::find(CParamButton::allParamButtons.begin(), CParamButton::allParamButtons.end(), this);
	CParamButton::allParamButtons.erase(it);
}

void CParamButton::Draw(HDC& hdc)
{
	if (_hidden)
		return;
	if (enabled && clock() - lastActivityTime > PARAM_BUTTON_ACTIVE_TIMER)
		LeftClickHandle();

	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial10b);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.WhitePen);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.BlackBrush);
	
	int indentX = TO_PIXEL(10);
	int indentY = TO_PIXEL(2);

	for (int i = 0; i < (int)values.size(); i++)
	{
		if (activeValue == i && enabled)
			SelectObject(hdc, DRAW_KIT.WhitePen2);
		else
			SelectObject(hdc, DRAW_KIT.WhitePen);
		Rectangle(hdc, _x + indentX, _y - indentY - _cy * (i + 1), _x + _cx - indentX, _y - _cy * i);
		TextOut(hdc, _x + _cx / 2, _y - indentY - _cy / 2 -_cy * i + TO_PIXEL(5), values.at(i).ToString(), (int)_tcslen(values.at(i).ToString()));
	}
	if (enabled)
	{
		SelectObject(hdc, DRAW_KIT.ActiveButtonPen);
		SelectObject(hdc, DRAW_KIT.ActiveButtonBrush);
		Rectangle(hdc, _x + indentX, _y, _x + _cx - indentX, _y + _cy - 4 * indentY);
	}

	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), _caption, (int)_tcslen(_caption));
		
	SetBkMode(hdc, OPAQUE);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
}

void CParamButton::DrawBackground()
{
	if (_hidden)
		return;
}

void CParamButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
		if (enabled)
			lastActivityTime = clock();
	}
}

void CParamButton::UpdateActivityTime()
{
	lastActivityTime = clock();
}

void CParamButton::ActivateNextValue()
{
	activeValue++;
	if (activeValue == (int)values.size())
		activeValue = 0;
}

CParamButton::Value::Value(void* value, PBTN_VALUE_TYPE type, int decimalPoint, double valueStep)
{
	this->value = value;
	this->vType = type;
	this->decimalPoint = decimalPoint;
	this->valueStep = valueStep;
}

LPCTSTR CParamButton::Value::ToString()
{
	double tmp;
	switch (vType)
	{
	case PBTN_VTYPE_INT:
		tmp = *((int*)value);
		break;
	case PBTN_VTYPE_LONG:
		tmp = *((long*)value);
		break;
	case PBTN_VTYPE_FLOAT:
		tmp = *((float*)value);
		break;
	case PBTN_VTYPE_DOUBLE:
		tmp = *((double*)value);
		break;
	default:
		break;
	}
	if (decimalPoint == 0)
		_stprintf_s(buf, _T("%.0f"), tmp);
	if (decimalPoint == 1)
		_stprintf_s(buf, _T("%.1f"), tmp);
	if (decimalPoint == 2)
		_stprintf_s(buf, _T("%.2f"), tmp);
	if (decimalPoint >= 3)
		_stprintf_s(buf, _T("%.3f"), tmp);

	return buf;
}

void CParamButton::Value::DecrimentValue()
{
	switch (vType)
	{
	case PBTN_VTYPE_INT:
		*((int*)value) -= (int)valueStep;
		break;
	case PBTN_VTYPE_LONG:
		*((long*)value) -= (long)valueStep;
		break;
	case PBTN_VTYPE_FLOAT:
		*((float*)value) -= (float)valueStep;
		break;
	case PBTN_VTYPE_DOUBLE:
		*((double*)value) -= valueStep;
		break;
	default:
		break;
	}
}

void CParamButton::Value::IncrimentValue()
{
	switch (vType)
	{
	case PBTN_VTYPE_INT:
		*((int*)value) += (int)valueStep;
		break;
	case PBTN_VTYPE_LONG:
		*((long*)value) += (long)valueStep;
		break;
	case PBTN_VTYPE_FLOAT:
		*((float*)value) += (float)valueStep;
		break;
	case PBTN_VTYPE_DOUBLE:
		*((double*)value) += valueStep;
		break;
	default:
		break;
	}
}