#include "stdafx.h"
#include "MenuTButton.h"
#include "SimpleTButton.h"
#include "util/Util.h"

std::vector<CMenuTButton*> CMenuTButton::allMenuTButtons;

CMenuTButton::CMenuTButton(int x, int y, int buttonPos, CAbstractKadr* parentKadr, void(CALLBACK* handler)(MOUSE_EVNT, CMenuTButton*)) : CAbstractButton(x, y, TBUTTON_SIDE_SIZE, TBUTTON_SIDE_SIZE, _T(""))
{
	_handler = handler;
	
	_parentKadr = parentKadr;
	allMenuTButtons.push_back(this);
	_enabled = false;

	for (int i = 0; i < MAX_MBUTTONS; i++)
		dropMenu[i] = nullptr;

	_buttonPos = buttonPos;
	buttonsNum = 0;
	curSelected = -1;
	lastTouch.x = -1;
	lastTouch.y = -1;
	CalculateConstants();

	blendFunc.SourceConstantAlpha	= 196;
	blendFunc.AlphaFormat			= 0;
	blendFunc.BlendFlags			= 0;
	blendFunc.BlendOp				= AC_SRC_OVER;

	HDC tmp = GetDC(NULL);
	tmpHDC		= CreateCompatibleDC(tmp);
	tmpBITMAP	= CreateCompatibleBitmap(tmp, _cx, _cy);
	DeleteDC(tmp);
}

CMenuTButton::~CMenuTButton()
{
	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
	for (int i = 0; i < MAX_MBUTTONS; i++)
		if (dropMenu[i] != nullptr)
			delete dropMenu[i];
	CMenuTButton::allMenuTButtons.erase(std::find(CMenuTButton::allMenuTButtons.begin(), CMenuTButton::allMenuTButtons.end(), this));
}

void CMenuTButton::Draw(HDC& hdc)
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

	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.WhitePen);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.WhiteBrush);
	int triangleSideSize = TO_PIXEL(10);
	if (_buttonPos > 0 && _buttonPos < MAX_LSIDE_TBUTTONS)
	{
		POINT pt [3] = {{_x + _cx - triangleSideSize, _y + _cy / 2},
						{_x + _cx - triangleSideSize * 2, _y + _cy / 2 - triangleSideSize},
						{_x + _cx - triangleSideSize * 2, _y + _cy / 2 + triangleSideSize}};
		Polygon(hdc, pt, 3);
	} else if (_buttonPos >= MAX_LSIDE_TBUTTONS && _buttonPos < MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS)
	{
		POINT pt [3] = {{_x + _cx / 2, _y + triangleSideSize},
						{_x + _cx / 2 - triangleSideSize, _y + triangleSideSize * 2},
						{_x + _cx / 2 + triangleSideSize, _y + triangleSideSize * 2}};
		Polygon(hdc, pt, 3);
	} else {
		POINT pt [3] = {{_x + triangleSideSize, _y + _cy / 2},
						{_x + triangleSideSize * 2, _y + _cy / 2 - triangleSideSize},
						{_x + triangleSideSize * 2, _y + _cy / 2 + triangleSideSize}};
		Polygon(hdc, pt, 3);
	}
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	
	SetBkMode(hdc, OPAQUE);
	SetTextAlign(hdc, oldTextAlign);
	SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
	
}

void CMenuTButton::LeftClickHandle()
{
	if (_hidden)
		return;
	if (_enabled)
		if (lastTouch.x != -1 && lastTouch.y != -1)
			for (int i = 0; i < buttonsNum; i++)
				if (dropMenu[i]->PointIsMine(lastTouch))
				{
					if (curSelected != i)
					{
						dropMenu[curSelected]->LeftClickHandle();
						dropMenu[i]->LeftClickHandle();
						_tcscpy_s(_caption, dropMenu[i]->GetCaption());
						curSelected = i;
					}
					lastTouch.x = -1;
					lastTouch.y = -1;
					break;
				}
	if (_handler)
	{
		_handler(M_EVNT_LB_DOWN, this);
	}
}

void CMenuTButton::DrawBackground()
{
	if (_hidden)
		return;
}

void CMenuTButton::Hide(bool hidden)
{
	_hidden = hidden;
	if (_hidden && _enabled)
	{
		_enabled = false;
		for (int i = 0; i < buttonsNum; i++)
			dropMenu[i]->Hide(true);
	}	
}

void CMenuTButton::AddButton(LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*))
{
	if (buttonsNum == maxButtonsForThisMenu)
		return;
	dropMenu[buttonsNum] = new CSimpleTButton(buttonPlaces[buttonsNum].x, buttonPlaces[buttonsNum].y, caption, handler);
	if (buttonsNum == 0)
	{
		_tcscpy_s(_caption, caption);
		curSelected = 0;
		dropMenu[curSelected]->LeftClickHandle();
	}
	dropMenu[buttonsNum]->Hide(true);
	buttonsNum++;
}

CAbstractButton* CMenuTButton::ChangePos(int x, int y)
{
	_x = x;
	_y = y;
	CalculateConstants();
	for (int i = 0; i < buttonsNum; i++)
			dropMenu[i]->ChangePos(buttonPlaces[i].x, buttonPlaces[i].y);
	return this;
}

void CMenuTButton::CalculateConstants()
{
	if (_buttonPos >= MAX_LSIDE_TBUTTONS && _buttonPos < MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS)
		CalculateBottomSidePositions();
	else
	{
		if (_buttonPos < MAX_LSIDE_TBUTTONS)
			CalculateLeftSidePositions();
		if (_buttonPos >= MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS)
			CalculateRightSidePositions();
	}
}

void CMenuTButton::CalculateLeftSidePositions()
{
	if (_buttonPos < 5)
	{
		maxButtonsForThisMenu = (MAX_LSIDE_TBUTTONS - _buttonPos - 1) * MAX_BSIDE_TBUTTONS;
		for (int col = 0; col < MAX_BSIDE_TBUTTONS; col++)
			for (int row = 0; row <= maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS; row++)
			{
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].x = _x + _cx + (col + 1) * TBUTTON_HOR_INDENT + col * TBUTTON_SIDE_SIZE;
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].y = _y + row * (TBUTTON_VERT_INDENT + TBUTTON_SIDE_SIZE);
			}
	} else {
		maxButtonsForThisMenu = (_buttonPos + 1) * MAX_BSIDE_TBUTTONS;
		for (int col = 0; col < MAX_BSIDE_TBUTTONS; col++)
			for (int row = 0; row <= maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS; row++)
			{
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].x = _x + _cx + (col + 1) * TBUTTON_HOR_INDENT + col * TBUTTON_SIDE_SIZE;
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].y =  _y - row * (TBUTTON_VERT_INDENT + TBUTTON_SIDE_SIZE);
			}
	}
}

void CMenuTButton::CalculateBottomSidePositions()
{
	if (MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS - _buttonPos > 2)
	{
		maxButtonsForThisMenu = MAX_LSIDE_TBUTTONS - 1;
		for (int row = 0; row < MAX_LSIDE_TBUTTONS; row++)
		{
			buttonPlaces[row].x = _x;
			buttonPlaces[row].y = _y - (row + 1) * (TBUTTON_VERT_INDENT + TBUTTON_SIDE_SIZE);
		}
	}
	else
	{
		maxButtonsForThisMenu = MAX_LSIDE_TBUTTONS - 1;
		for (int row = 0; row < MAX_LSIDE_TBUTTONS - 1; row++)
		{
			buttonPlaces[row].x = _x;
			buttonPlaces[row].y = _y - (row + 1) * (TBUTTON_VERT_INDENT + TBUTTON_SIDE_SIZE);
		}
	}
}

void CMenuTButton::CalculateRightSidePositions()
{
	if (MAX_TBUTTONS - _buttonPos <= 5)
	{
		maxButtonsForThisMenu = (_buttonPos - MAX_LSIDE_TBUTTONS - MAX_BSIDE_TBUTTONS) * MAX_BSIDE_TBUTTONS;
		for (int col = 0; col < MAX_BSIDE_TBUTTONS; col++)
			for (int row = 0; row <= maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS; row++)
			{
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].x = _x - ((col + 1) * TBUTTON_HOR_INDENT + (col + 1) * TBUTTON_SIDE_SIZE);
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].y = _y + row * (TBUTTON_VERT_INDENT + TBUTTON_SIDE_SIZE);
			}
	} else {
		maxButtonsForThisMenu = (MAX_TBUTTONS - _buttonPos) * MAX_BSIDE_TBUTTONS;
		for (int col = 0; col < MAX_BSIDE_TBUTTONS; col++)
			for (int row = 0; row <= maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS; row++)
			{
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].x = _x - ((col + 1) * TBUTTON_HOR_INDENT + (col + 1) * TBUTTON_SIDE_SIZE);
				buttonPlaces[col * (maxButtonsForThisMenu / MAX_BSIDE_TBUTTONS) + row].y =  _y - row * (TBUTTON_VERT_INDENT + TBUTTON_SIDE_SIZE);
			}
	}
}

bool CMenuTButton::PointIsMine(const POINT& touchCoord)
{
	if (_enabled)
		for (int i = 0; i < buttonsNum; i++)
			if (dropMenu[i]->PointIsMine(touchCoord))
			{
				lastTouch = touchCoord;
				return true;
			}

	if (touchCoord.x >= (LONG)_x &&
		touchCoord.x <= ((LONG)_x + (LONG)_cx) &&
		touchCoord.y >= (LONG)_y &&
		touchCoord.y <= ((LONG)_y + (LONG)_cy))
		return true;

	return false;
}