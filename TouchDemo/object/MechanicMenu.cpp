#include "StdAfx.h"
#include "object/MechanicMenu.h"
#include "util/Util.h"

#define EKRAN_WIDTH (int)(WIDTHPX)
#define EKRAN_HEIGHT (int)(HEIGHTPX)
#define BUTTON_INDENT TO_PIXEL(2)
#define SCALE_FACTOR 0.98

CSimpleButton* CMechanicMenu::hiButton[2] = {new CSimpleButton(BUTTON_INDENT, BUTTON_INDENT, WIDTHPX / 28 * SCALE_FACTOR, MECHANIC_MENU_HEIGHTPX - BUTTON_INDENT, L"ÏÇÊ1"),
											new CSimpleButton(WIDTHPX - WIDTHPX / 28 * SCALE_FACTOR - 2 * BUTTON_INDENT, 0, WIDTHPX / 28, MECHANIC_MENU_HEIGHTPX, L"ÏÇÊ2")};
CSimpleButton* CMechanicMenu::loRotary[2] = {new CSimpleButton(BUTTON_INDENT, HEIGHTPX - MECHANIC_MENU_HEIGHTPX, WIDTHPX / 28 * SCALE_FACTOR + BUTTON_INDENT, MECHANIC_MENU_HEIGHTPX - BUTTON_INDENT, L"ÌÔÌ1"),
											new CSimpleButton(WIDTHPX - WIDTHPX / 28 * SCALE_FACTOR - 2 * BUTTON_INDENT, HEIGHTPX - MECHANIC_MENU_HEIGHTPX + BUTTON_INDENT, WIDTHPX / 28, MECHANIC_MENU_HEIGHTPX - BUTTON_INDENT, L"ÌÔÌ2")};

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

void CMechanicMenu::ChangeSOIStatus()
{
	hiMenu->isSOI = !hiMenu->isSOI;
	hiMenu->buttons[hiMenu->curActive]->SwitchSOI(hiMenu->isSOI);
}

bool CMechanicMenu::PointIsMine(const POINT pt)
{
	return hiMenu->PointIsMine(pt) || loMenu->PointIsMine(pt);
}

void CMechanicMenu::LeftClickHandle(POINT clickCoord)
{
	if (hiMenu->PointIsMine(clickCoord))
		hiMenu->LeftClickHandle(clickCoord);
	else if (loMenu->PointIsMine(clickCoord))
		loMenu->LeftClickHandle(clickCoord);
	if (_id == 0)
		if (hiButton[0]->PointIsMine(clickCoord))
			hiButton[0]->LeftClickHandle();
		else if (loRotary[0]->PointIsMine(clickCoord))
			loRotary[0]->LeftClickHandle();
	if (_id == DISPLAY_COLS - 1)
		if (hiButton[1]->PointIsMine(clickCoord))
			hiButton[1]->LeftClickHandle();
		else if (loRotary[1]->PointIsMine(clickCoord))
			loRotary[1]->LeftClickHandle();

	extern HWND MFIWindow;
	SendMessage(MFIWindow, WM_UPDATE, 0, 0);
}

void CMechanicMenu::SetBlock(bool blockStatus)
{
	if (blockStatus)
		hiMenu->buttons[hiMenu->curActive]->Disactivate();
	hiMenu->blocked = blockStatus;
	if (!blockStatus)
		hiMenu->buttons[hiMenu->curActive]->Activate();
}

bool CMechanicMenu::GetBlockStatus()
{
	return hiMenu->blocked;
}

UINT CMechanicMenu::GetActiveButtonPosition()
{
	return hiMenu->curActive;
}

CMechanicMenu* CMechanicMenu::ChangePos(UINT newPos)
{
	_id = newPos;
	hiMenu->_id = newPos;
	loMenu->_id = newPos;
	hiMenu->PosMenu();
	loMenu->PosMenu();
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (_id % 2 == 0)
		{
			hiMenu->buttons[i]->ChangePos(hiMenu->_x + BUTTON_INDENT + (i + 1) * (hiMenu->_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), hiMenu->_y + BUTTON_INDENT);
			loMenu->buttons[i]->ChangePos(loMenu->_x + BUTTON_INDENT + (i + 1) * (loMenu->_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), loMenu->_y + BUTTON_INDENT);
		} else {
			hiMenu->buttons[i]->ChangePos(hiMenu->_x + BUTTON_INDENT + i * (hiMenu->_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), hiMenu->_y + BUTTON_INDENT);
			loMenu->buttons[i]->ChangePos(loMenu->_x + BUTTON_INDENT + i * (loMenu->_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), loMenu->_y + BUTTON_INDENT);
		}
	return this;
}

CMechanicMenu::CHiMenu::CHiMenu(UINT id) : CDrawingObject(MAX)
{
	_id = id;
	blocked = false;
	PosMenu();
	CreateButtons();
	curActive = 1;
	isSOI = false;
	buttons[curActive]->Activate();
}

void CMechanicMenu::CHiMenu::PosMenu()
{
	_cy = MECHANIC_MENU_HEIGHTPX;
	_x = _id * EKRAN_WIDTH / 4;
	_y = 0;
	_cx = EKRAN_WIDTH / 4;
}

void CMechanicMenu::CHiMenu::CreateButtons()
{
	buttons[0] = nullptr;
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
	{
		_stprintf_s(buf, _T("Â%d"), (_id + 1) * 10 + i);
		if (_id % 2 == 0)
			buttons[i] = new CMenuButton(_x + BUTTON_INDENT + (i + 1) * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT, _cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT, buf);
		else
			buttons[i] = new CMenuButton(_x + BUTTON_INDENT + i * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT, _cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT, buf);
	}
}

void CMechanicMenu::CHiMenu::DrawBackground()
{
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	//SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
	//DrawBorders(DRAW_ENGINE.getBackgroundHDC());

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
}

/*void CMechanicMenu::CHiMenu::DrawBorders(HDC hdc)
{
	int shift = (_id % 2 == 0) ? 0 : - 1;
	UINT neatIndent = TO_PIXEL(10);
	if (curActive != BUTTONS_MAX_NUM)
	{
		POINT pts[6];
		pts[0].x = _x;
		pts[0].y = _cy;
		pts[1].x = _x + (curActive + shift) * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)) - neatIndent;
		pts[1].y = _cy;
		pts[2].x = _x + (curActive + shift) * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)) + neatIndent;
		pts[2].y = _y + neatIndent;
		pts[3].x = _x + (curActive + shift + 1) * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)) - neatIndent;
		pts[3].y = _y + neatIndent;
		pts[4].x = _x + (curActive + shift + 1) * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)) + neatIndent;
		pts[4].y = _cy;
		pts[5].x = _x + _cx;
		pts[5].y = _cy;
		Polyline(hdc, pts, 6);
		
		pts[0].x = _x + _cx;
		pts[0].y = HEIGHTPX - _cy;

		if (_id % 2 == 0)	pts[1].x = _x + _cx;
		else				pts[1].x = _x + _cx - _cx / (BUTTONS_MAX_NUM + 1);
		pts[1].y = HEIGHTPX - _cy;

		if (_id % 2 == 0)	pts[2].x = _x + _cx - 2 * neatIndent;
		else				pts[2].x = _x + _cx - _cx / (BUTTONS_MAX_NUM + 1) - 2 * neatIndent;
		pts[2].y = HEIGHTPX - neatIndent;

		if (_id % 2 == 0)	pts[3].x = _x + _cx / (BUTTONS_MAX_NUM + 1) + 2*neatIndent;
		else				pts[3].x = _x + 2 * neatIndent;
		pts[3].y = HEIGHTPX - neatIndent;

		if (_id % 2 == 0)	pts[4].x = _x + _cx / (BUTTONS_MAX_NUM + 1);
		else				pts[4].x = _x;
		pts[4].y = HEIGHTPX - _cy;

		pts[5].x = _x;
		pts[5].y = HEIGHTPX - _cy;
		Polyline(hdc, pts, 6);
	}
	else 
	{
		POINT pts[2];
		pts[0].x = _x;
		pts[0].y = _cy;
		pts[1].x = _x + _cx;
		pts[1].y = _cy;
		Polyline(hdc, pts, 2);

		pts[0].x = _x;
		pts[0].y = HEIGHTPX - _cy;
		pts[1].x = _x + _cx;
		pts[1].y = HEIGHTPX - _cy;
		Polyline(hdc, pts, 2);
	}
}*/

void CMechanicMenu::CHiMenu::Draw(HDC hdc)
{} 

void CMechanicMenu::CHiMenu::LeftClickHandle(POINT clickCoord)
{
	if (blocked)
		return;
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (buttons[i] != nullptr && buttons[i]->PointIsMine(clickCoord))
		{
			if (i == 0)
				return;
			if (curActive != i)
				buttons[curActive]->Disactivate();
			curActive = i;
			buttons[curActive]->LeftClickHandle();
			if (isSOI)
				buttons[curActive]->SwitchSOI(true);
		}
}

CMechanicMenu::CLoMenu::CLoMenu(UINT id) : CDrawingObject(MID)
{
	_id = id;
	PosMenu();
	CreateButtons();
}

void CMechanicMenu::CLoMenu::PosMenu()
{
	_cy = MECHANIC_MENU_HEIGHTPX;
	_x = _id * EKRAN_WIDTH / 4;
	_y = HEIGHTPX - _cy;
	_cx = EKRAN_WIDTH / 4;
}

void CMechanicMenu::CLoMenu::LeftClickHandle(POINT clickCoord)
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (buttons[i] != nullptr && buttons[i]->PointIsMine(clickCoord))
		{
			buttons[i]->LeftClickHandle();
			return;
		}
}

void CMechanicMenu::CLoMenu::CreateButtons()
{
	buttons[0] = nullptr;
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
	{
		_stprintf_s(buf, _T("Í%d"), i);
		if (_id % 2 == 0)
			buttons[i] = new CSimpleButton(_x + BUTTON_INDENT + (i + 1) * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT, _cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT, buf);
		else
			buttons[i] = new CSimpleButton(_x + BUTTON_INDENT + i * (_cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT, _cx * SCALE_FACTOR / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT, buf);
		
	}
}

void CMechanicMenu::CLoMenu::DrawBackground()
{
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
}

void CMechanicMenu::CLoMenu::Draw(HDC hdc)
{}