#include "StdAfx.h"
#include "object/MechanicMenu.h"
#include "util/Util.h"

#define EKRAN_WIDTH (int)(WIDTHPX)
#define EKRAN_HEIGHT (int)(HEIGHTPX)
#define BUTTON_INDENT 2

CMechanicMenu::CMechanicMenu(UINT id)
{
	_id = id;
	hiMenu = new CHiMenu(id);
	loMenu = new CLoMenu(id);
}

CMechanicMenu::~CMechanicMenu()
{
	delete hiMenu;
	delete loMenu;
}

void CMechanicMenu::DrawBackground()
{
	hiMenu->DrawBackground();
	loMenu->DrawBackground();
}

void CMechanicMenu::Draw(HDC hdc)
{
	hiMenu->Draw(hdc);
	loMenu->Draw(hdc);
}

bool CMechanicMenu::PointIsMine(const POINT pt)
{
	return hiMenu->PointIsMine(pt) || loMenu->PointIsMine(pt);
}

void CMechanicMenu::LeftClickHandle(POINT clickCoord)
{
	if (hiMenu->PointIsMine(clickCoord))
	{
		hiMenu->LeftClickHandle(clickCoord);
		return;
	}
	if (loMenu->PointIsMine(clickCoord))
	{
		loMenu->LeftClickHandle(clickCoord);
		return;
	}
}

CMechanicMenu::CHiMenu::CHiMenu(UINT id)
{
	_cy = MECHANIC_MENU_HEIGHTPX;
	_x = id * EKRAN_WIDTH / 4;
	_y = 0;
	_cx = EKRAN_WIDTH / 4;
	_id = id;
	CreateButtons();
	curSOI = BUTTONS_MAX_NUM;
}

void CMechanicMenu::CHiMenu::CreateButtons()
{
	buttons[0] = NULL;
	for (int i = 1; i < BUTTONS_MAX_NUM; i++)
	{
		_stprintf_s(buf, _T("Â%d"), i);
		if (_id % 2 == 0)
			buttons[i] = new CMenuButton(_x + BUTTON_INDENT + i * (_cx / BUTTONS_MAX_NUM), _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM, _cy - BUTTON_INDENT, buf);
		else
			buttons[i] = new CMenuButton(_x + BUTTON_INDENT + (i - 1) * (_cx / BUTTONS_MAX_NUM), _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM, _cy - BUTTON_INDENT, buf);
	}
	if (_id == 0)
		buttons[0] = new CMenuButton(_x + BUTTON_INDENT, _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM - BUTTON_INDENT, _cy - BUTTON_INDENT, L"ÏÇÊ");
	if (_id == 3)
		buttons[0] = new CMenuButton(_x - BUTTON_INDENT + (BUTTONS_MAX_NUM - 1) * _cx / BUTTONS_MAX_NUM, _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM - BUTTON_INDENT, _cy - BUTTON_INDENT, L"ÏÇÊ");
}

void CMechanicMenu::CHiMenu::DrawBackground()
{
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BluePen2);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.LightGreyBrush);

	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
}

void CMechanicMenu::CHiMenu::Draw(HDC hdc)
{
	if (curSOI < BUTTONS_MAX_NUM)
	{
		oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.YellowBrush);
		UINT x;
		UINT cx;
		if (_id % 2 == 0)
			x = _x + BUTTON_INDENT + curSOI * (_cx / BUTTONS_MAX_NUM);
		else
			x = _x + BUTTON_INDENT + (curSOI - 1) * (_cx / BUTTONS_MAX_NUM);
		cx = _cx / BUTTONS_MAX_NUM;
		Rectangle(hdc, x, _y + BUTTON_INDENT, x + cx, _cy - BUTTON_INDENT);
		SelectObject(hdc, oldBrush);
	}
}

CMechanicMenu::CLoMenu::CLoMenu(UINT id)
{
	_cy = MECHANIC_MENU_HEIGHTPX;
	_x = id * EKRAN_WIDTH / 4;
	_y = EKRAN_HEIGHT - _cy;
	_cx = EKRAN_WIDTH / 4;
	_id = id;
	CreateButtons();
}

void  CMechanicMenu::CHiMenu::LeftClickHandle(POINT clickCoord)
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (buttons[i] != NULL && buttons[i]->PointIsMine(clickCoord))
		{
			if (i == 0)
				return;
			if (curSOI < BUTTONS_MAX_NUM && curSOI != i)
				buttons[curSOI]->SwitchSOI();
			buttons[i]->LeftClickHandle();
			curSOI = i;
		}
}

void CMechanicMenu::CLoMenu::LeftClickHandle(POINT clickCoord)
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (buttons[i] != NULL && buttons[i]->PointIsMine(clickCoord))
			buttons[i]->LeftClickHandle();

}

void CMechanicMenu::CLoMenu::CreateButtons()
{
	buttons[0] = NULL;
	for (int i = 1; i < BUTTONS_MAX_NUM; i++)
	{
		_stprintf_s(buf, _T("Í%d"), i);
		if (_id % 2 == 0)
			buttons[i] = new CSimpleButton(_x + BUTTON_INDENT + i * (_cx / BUTTONS_MAX_NUM), _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM, _cy - BUTTON_INDENT, buf);
		else
			buttons[i] = new CSimpleButton(_x + BUTTON_INDENT + (i - 1) * (_cx / BUTTONS_MAX_NUM), _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM, _cy - BUTTON_INDENT, buf);

	}
	if (_id == 0)
		buttons[0] = new CSimpleButton(_x + BUTTON_INDENT, _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM, _cy - BUTTON_INDENT, L"ÌÔÌ");
	if (_id == 3)
		buttons[0] = new CSimpleButton(_x - BUTTON_INDENT + (BUTTONS_MAX_NUM - 1) * _cx / BUTTONS_MAX_NUM, _y + BUTTON_INDENT, _cx / BUTTONS_MAX_NUM, _cy - BUTTON_INDENT, L"ÌÔÌ");
}

void CMechanicMenu::CLoMenu::DrawBackground()
{
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BluePen2);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.LightGreyBrush);

	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
}

void CMechanicMenu::CLoMenu::Draw(HDC hdc)
{}