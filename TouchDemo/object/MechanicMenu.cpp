#include "StdAfx.h"
#include "MechanicMenu.h"
#include "util/Util.h"

#define EKRAN_WIDTH (int)(WIDTHPX)
#define EKRAN_HEIGHT (int)(HEIGHTPX)
#define BUTTON_INDENT TO_PIXEL(2)
#define SCALE_FACTOR 0.98

CSimpleButton* CMechanicMenu::hiButton[2] = {new CSimpleButton(BUTTON_INDENT,
															   BUTTON_INDENT,
															   WIDTHPX / 28 * SCALE_FACTOR,
															   MECHANIC_MENU_HEIGHTPX - BUTTON_INDENT,
															   L"ÏÇÊ1",
															   CSimpleButtonHandler::OnPZKPress),
											new CSimpleButton(WIDTHPX - WIDTHPX / 28 * SCALE_FACTOR - 2 * BUTTON_INDENT,
															  0,
															  WIDTHPX / 28,
															  MECHANIC_MENU_HEIGHTPX,
															  L"ÏÇÊ2",
															  CSimpleButtonHandler::OnPZKPress)};
CSimpleButton* CMechanicMenu::loRotary[2] = {new CSimpleButton(BUTTON_INDENT,
															   HEIGHTPX - MECHANIC_MENU_HEIGHTPX + BUTTON_INDENT,
															   WIDTHPX / 28 * SCALE_FACTOR + BUTTON_INDENT,
															   MECHANIC_MENU_HEIGHTPX - BUTTON_INDENT,
															   L"ÌÔÌ1",
															   CSimpleButtonHandler::OnMFMPress),
											new CSimpleButton(WIDTHPX - WIDTHPX / 28 * SCALE_FACTOR - 2 * BUTTON_INDENT,
															  HEIGHTPX - MECHANIC_MENU_HEIGHTPX + BUTTON_INDENT,
															  WIDTHPX / 28,
															  MECHANIC_MENU_HEIGHTPX - BUTTON_INDENT,
															  L"ÌÔÌ2",
															  CSimpleButtonHandler::OnMFMPress)};

CMechanicMenu::CMechanicMenu(UINT id, KADR_TYPE type)
{
	_id = id;
	hiMenu = new CHiMenu(id, type);
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

void CMechanicMenu::Draw(HDC& hdc)
{
	hiMenu->Draw(hdc);
	loMenu->Draw(hdc);
}

void CMechanicMenu::SetSOIStatus(bool soiStatus)
{
	hiMenu->_isSOI = soiStatus;
	hiMenu->buttons[hiMenu->_curActive]->SwitchSOI(hiMenu->_isSOI);
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
}

void CMechanicMenu::SetBlock(bool blockStatus, SWIPE_DIRECTION swipeDir)
{
	if (blockStatus)
	{
		hiMenu->buttons[hiMenu->_curActive]->Disactivate();
		hiMenu->_blockerSide = (swipeDir == LEFT) ? RIGHT : LEFT;
	}
	hiMenu->_blocked = blockStatus;
	if (!blockStatus)
		hiMenu->buttons[hiMenu->_curActive]->Activate();
}

bool CMechanicMenu::GetBlockStatus()
{
	return hiMenu->_blocked;
}

UINT CMechanicMenu::GetActiveButtonPosition()
{
	return hiMenu->_curActive;
}

CMechanicMenu* CMechanicMenu::ChangePos(UINT newPos)
{
	_id = newPos;
	hiMenu->_id = newPos;
	loMenu->_id = newPos;
	hiMenu->PlaceMenu();
	loMenu->PlaceMenu();
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (_id % 2 == 0)
		{
			hiMenu->buttons[i]->ChangePos(hiMenu->_x + BUTTON_INDENT + (i + 1) * (hiMenu->_cx / (BUTTONS_MAX_NUM + 1)), hiMenu->_y + BUTTON_INDENT);
			loMenu->buttons[i]->ChangePos(loMenu->_x + BUTTON_INDENT + (i + 1) * (loMenu->_cx / (BUTTONS_MAX_NUM + 1)), loMenu->_y + BUTTON_INDENT);
		} else {
			hiMenu->buttons[i]->ChangePos(hiMenu->_x + BUTTON_INDENT + i * (hiMenu->_cx / (BUTTONS_MAX_NUM + 1)), hiMenu->_y + BUTTON_INDENT);
			loMenu->buttons[i]->ChangePos(loMenu->_x + BUTTON_INDENT + i * (loMenu->_cx / (BUTTONS_MAX_NUM + 1)), loMenu->_y + BUTTON_INDENT);
		}
	return this;
}

void CMechanicMenu::EnableKadrTypeSelection()
{
	hiMenu->EnableKadrTypeSelection();
}

void CMechanicMenu::DisableKadrTypeSelection()
{
	hiMenu->DisableKadrTypeSelection();
}

void CMechanicMenu::CHiMenu::EnableKadrTypeSelection()
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
	{
		buttons[i]->Hide(true);
		tmp[i] = buttons[i];
		buttons[i] = nullptr;
	}
	CreateButtons(EMPTY);
	kadrSelection = true;
}

void CMechanicMenu::CHiMenu::DisableKadrTypeSelection()
{
	if (!kadrSelection)
		return;
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
	{
		delete buttons[i];
		buttons[i] = tmp[i];
		tmp[i] = nullptr;
		buttons[i]->Hide(false);
	}
	kadrSelection = false;
}

CMechanicMenu::CHiMenu::CHiMenu(UINT id, KADR_TYPE type) : CDrawingObject(MAX)
{
	_id = id;
	_blocked = false;
	_blockerSide = LEFT;
	PlaceMenu();
	_curActive = 1;
	CreateButtons(type);
	_isSOI = false;
	kadrSelection = false;
	buttons[_curActive]->Activate();
}

CMechanicMenu::CHiMenu::~CHiMenu()
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		delete buttons[i];
}

void CMechanicMenu::CHiMenu::PlaceMenu()
{
	_cy = MECHANIC_MENU_HEIGHTPX;
	_x = _id * EKRAN_WIDTH / 4;
	_y = 0;
	_cx = EKRAN_WIDTH / 4;
}

void CMechanicMenu::CHiMenu::CreateButtons(KADR_TYPE type)
{
	switch (type)
	{
	case EMPTY:
	{
		_stprintf_s(buf, _T("ESC"));
		buttons[0] = new CMenuButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
										_cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
										buf, CMenuButtonHandler::OnEscButtonPress);
		buttons[1] = new CMenuButton(_x + BUTTON_INDENT + (2 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("PLD"), CMenuButtonHandler::OnPLDButtonPress);
		buttons[2] = new CMenuButton(_x + BUTTON_INDENT + (3 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYST"), CMenuButtonHandler::OnSYSTButtonPress);
		buttons[3] = new CMenuButton(_x + BUTTON_INDENT + (4 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM"), CMenuButtonHandler::OnCAMButtonPress);
		buttons[4] = new CMenuButton(_x + BUTTON_INDENT + (5 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("MAP"), CMenuButtonHandler::OnMAPButtonPress);
		buttons[5] = new CMenuButton(_x + BUTTON_INDENT + (6 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("RDR"), CMenuButtonHandler::OnRDRButtonPress);
	}
		break;
	case PLD:
		_stprintf_s(buf, _T("PLD"));
		break;
	case SYST:
		_stprintf_s(buf, _T("SYST"));
		break;
	case CAM:
		_stprintf_s(buf, _T("CAM"));
		break;
	case MAP:
		_stprintf_s(buf, _T("MAP"));
		break;
	case RDR:
		_stprintf_s(buf, _T("RDR"));
		break;
	case MAX_KADR_TYPE:
		_stprintf_s(buf, _T("XXX"));
		break;
	default:
		break;
	}
	if (type != EMPTY)
	{
		buttons[0] = new CMenuButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
										_cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
										buf, CMenuButtonHandler::OnSetButtonPress);
		for (int i = 1; i < BUTTONS_MAX_NUM; i++)
		{
			_stprintf_s(buf, _T("Â%d"), (_id + 1) * 10 + i);
			buttons[i] = new CMenuButton(_x + BUTTON_INDENT + (i + 1 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)),
											_y + BUTTON_INDENT,
											_cx / (BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
											buf, CMenuButtonHandler::OnMenuButtonPress);
		}
	}
}

void CMechanicMenu::CHiMenu::DrawBackground()
{
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
}

void CMechanicMenu::CHiMenu::Draw(HDC& hdc)
{} 

void CMechanicMenu::CHiMenu::LeftClickHandle(POINT clickCoord)
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		if (buttons[i] != nullptr && buttons[i]->PointIsMine(clickCoord))
		{
			if (i != 0 && !kadrSelection)
			{
				if (_curActive != i)
					buttons[_curActive]->Disactivate();
				_curActive = i;
			}

			if (_blocked)
			{
				UINT kadrID = (_blockerSide == LEFT) ? _id - 1 : _id;
				EKRAN_HANDLER.DivideKadr(kadrID, HALF, _blockerSide);
				if (i == 0)
					buttons[i]->LeftClickHandle();
			} else {
				buttons[i]->LeftClickHandle();
				if (!kadrSelection && _isSOI)
					buttons[_curActive]->SwitchSOI(true);
			}
			return;
		}
}

CMechanicMenu::CLoMenu::CLoMenu(UINT id) : CDrawingObject(MID)
{
	_id = id;
	PlaceMenu();
	CreateButtons();
}

CMechanicMenu::CLoMenu::~CLoMenu()
{
	for (int i = 0; i < BUTTONS_MAX_NUM; i++)
		delete buttons[i];
}

void CMechanicMenu::CLoMenu::PlaceMenu()
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
		buttons[i] = new CSimpleButton(_x + BUTTON_INDENT + (i + 1 - _id % 2) * (_cx / (BUTTONS_MAX_NUM + 1)),
									   _y + BUTTON_INDENT,
									   _cx / (BUTTONS_MAX_NUM + 1),
									   _cy - BUTTON_INDENT,
									   buf,
									   CSimpleButtonHandler::OnSimpleButtonPress);
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

void CMechanicMenu::CLoMenu::Draw(HDC& hdc)
{}