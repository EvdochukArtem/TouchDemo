#include "StdAfx.h"
#include "MechanicMenu.h"
#include "util/Util.h"
#include "buttons/mechButtons/SimpleButtonHandler.h"
#include "buttons/mechButtons/SwitchButtonHandler.h"
#include "buttons/mechButtons/RadioButtonHandler.h"
#include "buttons/mechButtons/TabButtonHandler.h"
#include "buttons/mechButtons/ParamButton.h"
#include "buttons/mechButtons/RotaryButtonHandler.h"

#define	BUTTON_INDENT		TO_PIXEL(2)
const double SCALE_FACTOR	= 0.98;

CAbstractButton* CMechanicMenu::hiButton[2] = {nullptr, nullptr};
CRotaryButton* CMechanicMenu::loRotary[2] = {nullptr, nullptr};

CMechanicMenu::CMechanicMenu(UINT id, KADR_TYPE type)
{
	_id = id;
	hiMenu = new CHiMenu(id, type);
	loMenu = new CLoMenu(id);
	
	if (CMechanicMenu::hiButton[0] == nullptr)
		CMechanicMenu::hiButton[0] = new CSimpleButton(X0_PX + BUTTON_INDENT,
													   Y0_PX + BUTTON_INDENT,
													   WIDTHPX / 28,
													   MECHANIC_MENU_HI_HEIGHTPX - BUTTON_INDENT,
													   L"ÏÇÊ1",
													   CSimpleButtonHandler::OnPZKPress);
	if (CMechanicMenu::hiButton[1] == nullptr)
		CMechanicMenu::hiButton[1] = new CSimpleButton(X0_PX + WIDTHPX - (int)(WIDTHPX / 28 * SCALE_FACTOR) - 2 * BUTTON_INDENT,
													   Y0_PX + BUTTON_INDENT,
													   WIDTHPX / 28,
													   MECHANIC_MENU_HI_HEIGHTPX,
													   L"ÏÇÊ2",
													   CSimpleButtonHandler::OnPZKPress);
	
	if (CMechanicMenu::loRotary[0] == nullptr)
		CMechanicMenu::loRotary[0] = new CRotaryButton(X0_PX + BUTTON_INDENT,
													   Y0_PX + HEIGHTPX - MECHANIC_MENU_LO_HEIGHTPX + BUTTON_INDENT,
													   WIDTHPX / 28,
													   MECHANIC_MENU_LO_HEIGHTPX - BUTTON_INDENT);
	if (CMechanicMenu::loRotary[1] == nullptr)
		CMechanicMenu::loRotary[1] = new CRotaryButton(X0_PX + WIDTHPX - (int)(WIDTHPX / 28 * SCALE_FACTOR) - 2 * BUTTON_INDENT,
													   Y0_PX + HEIGHTPX - MECHANIC_MENU_LO_HEIGHTPX + BUTTON_INDENT,
													   WIDTHPX / 28,
													   MECHANIC_MENU_LO_HEIGHTPX - BUTTON_INDENT);
}

CMechanicMenu::~CMechanicMenu()
{
	delete hiMenu;
	delete loMenu;
}

void CMechanicMenu::SetSOIStatus(bool soiStatus)
{
	hiMenu->_isSOI = soiStatus;
	hiMenu->buttons[hiMenu->_curActive]->SwitchSOI(hiMenu->_isSOI);
}

bool CMechanicMenu::GetSOIStatus()
{
	return hiMenu->_isSOI;
};

bool CMechanicMenu::PointIsMine(const POINT& pt)
{
	bool cornerButtonsPoint = false;
	if (_id == 0) 
		cornerButtonsPoint = hiButton[0]->PointIsMine(pt) || loRotary[0]->PointIsMine(pt);
	if (_id == DISPLAY_COLS - 1)
		cornerButtonsPoint = loRotary[1]->PointIsMine(pt) || hiButton[1]->PointIsMine(pt);
							
	return hiMenu->PointIsMine(pt) || loMenu->PointIsMine(pt) || cornerButtonsPoint;
}

void CMechanicMenu::LeftClickHandle(POINT clickCoord)
{
	if (hiMenu->PointIsMine(clickCoord))
	{
		hiMenu->LeftClickHandle(clickCoord);
		return;
	}
	else if (loMenu->PointIsMine(clickCoord))
	{
		loMenu->LeftClickHandle(clickCoord);
		return;
	}
}

void CMechanicMenu::MouseWheelHandle(double scrollFactor, POINT scrollCoord)
{
	if (_id == 0)
		if (hiButton[0]->PointIsMine(scrollCoord))
		{
			hiButton[0]->MouseWheelHandle(scrollFactor);
			return;
		}
		else if (loRotary[0]->PointIsMine(scrollCoord))
		{
			loRotary[0]->MouseWheelHandle(scrollFactor);
			return;
		}
	if (_id == DISPLAY_COLS - 1)
		if (hiButton[1]->PointIsMine(scrollCoord))
		{
			hiButton[1]->MouseWheelHandle(scrollFactor);
			return;
		}
		else if (loRotary[1]->PointIsMine(scrollCoord))
		{
			loRotary[1]->MouseWheelHandle(scrollFactor);
			return;
		}
}

void CMechanicMenu::SetBlock(bool blockStatus, SWIPE_DIRECTION swipeDir)
{
	if (blockStatus)
	{
		hiMenu->buttons[hiMenu->_curActive]->Disactivate();
		hiMenu->_blockerSide = (swipeDir == SWIPE_DIR_LEFT) ? SWIPE_DIR_RIGHT : SWIPE_DIR_LEFT;
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

void CMechanicMenu::Hide(bool hidden)
{
	hiMenu->Hide(hidden);
	loMenu->Hide(hidden);
}

CMechanicMenu* CMechanicMenu::ChangePos(UINT newPos)
{
	_id = newPos;
	hiMenu->_id = newPos;
	loMenu->_id = newPos;
	hiMenu->Place();
	loMenu->Place();
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
		if (_id % 2 == 0)
		{
			hiMenu->buttons[i]->ChangePos(hiMenu->_x + BUTTON_INDENT + (i + 1) * (hiMenu->_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), hiMenu->_y + BUTTON_INDENT);
			loMenu->buttons[i]->ChangePos(loMenu->_x + BUTTON_INDENT + (i + 1) * (loMenu->_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), loMenu->_y + BUTTON_INDENT);
		} else {
			hiMenu->buttons[i]->ChangePos(hiMenu->_x + BUTTON_INDENT + i * (hiMenu->_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), hiMenu->_y + BUTTON_INDENT);
			loMenu->buttons[i]->ChangePos(loMenu->_x + BUTTON_INDENT + i * (loMenu->_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), loMenu->_y + BUTTON_INDENT);
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
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
	{
		buttons[i]->Hide(true);
		tmp[i] = buttons[i];
		buttons[i] = nullptr;
	}
	CreateButtons(KADR_TYPE_AUX);
	kadrSelection = true;
}

void CMechanicMenu::CHiMenu::DisableKadrTypeSelection()
{
	if (!kadrSelection)
		return;
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
	{
		delete buttons[i];
		buttons[i] = tmp[i];
		tmp[i] = nullptr;
		buttons[i]->Hide(false);
	}
	kadrSelection = false;
}

CMechanicMenu::CHiMenu::CHiMenu(UINT id, KADR_TYPE type) : CDrawingObject(PRIOR_MAX)
{
	_id = id;
	_blocked = false;
	_blockerSide = SWIPE_DIR_LEFT;
	Place();
	_curActive = 1;
	CreateButtons(type);
	_isSOI = false;
	kadrSelection = false;
	buttons[_curActive]->Activate();
}

CMechanicMenu::CHiMenu::~CHiMenu()
{
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
		delete buttons[i];
}

void CMechanicMenu::CHiMenu::Place()
{
	_cy = MECHANIC_MENU_HI_HEIGHTPX;
	_x = X0_PX + _id * WIDTHPX / 4;
	_y = Y0_PX;
	_cx = WIDTHPX / 4;
}

void CMechanicMenu::CHiMenu::CreateButtons(KADR_TYPE type)
{
	switch (type)
	{
	case KADR_TYPE_AUX:
	{
		_stprintf_s(buf, _T("ESC"));
		buttons[0] = new CTabButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 buf, CTabButtonHandler::OnEscButtonPress);
		buttons[1] = new CTabButton(_x + BUTTON_INDENT + (2 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("PLD"), CTabButtonHandler::OnPLDButtonPress);
		buttons[2] = new CTabButton(_x + BUTTON_INDENT + (3 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYST"), CTabButtonHandler::OnSYSTButtonPress);
		buttons[3] = new CTabButton(_x + BUTTON_INDENT + (4 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM"), CTabButtonHandler::OnCAMButtonPress);
		buttons[4] = new CTabButton(_x + BUTTON_INDENT + (5 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("MAP"), CTabButtonHandler::OnMAPButtonPress);
		buttons[5] = new CTabButton(_x + BUTTON_INDENT + (6 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("RDR"), CTabButtonHandler::OnRDRButtonPress);
	}
		break;
	case KADR_TYPE_PLD:
		_stprintf_s(buf, _T("PLD"));
		break;
	case KADR_TYPE_SYST:
	{
		_stprintf_s(buf, _T("SYST"));
		buttons[0] = new CTabButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 buf, CTabButtonHandler::OnSetButtonPress);
		buttons[1] = new CTabButton(_x + BUTTON_INDENT + (2 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYS1"), CTabButtonHandler::OnSYS1ButtonPress);
		buttons[2] = new CTabButton(_x + BUTTON_INDENT + (3 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYS2"), CTabButtonHandler::OnSYS2ButtonPress);
		buttons[3] = new CTabButton(_x + BUTTON_INDENT + (4 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYS3"), CTabButtonHandler::OnSYS3ButtonPress);
		buttons[4] = new CTabButton(_x + BUTTON_INDENT + (5 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYS4"), CTabButtonHandler::OnSYS4uttonPress);
		buttons[5] = new CTabButton(_x + BUTTON_INDENT + (6 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("SYS5"), CTabButtonHandler::OnSYS5ButtonPress);
	}
		break;
	case KADR_TYPE_CAM:
	{
		_stprintf_s(buf, _T("CAM"));
		buttons[0] = new CTabButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 buf, CTabButtonHandler::OnSetButtonPress);
		buttons[1] = new CTabButton(_x + BUTTON_INDENT + (2 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM1"), CTabButtonHandler::OnCAM1ButtonPress);
		buttons[2] = new CTabButton(_x + BUTTON_INDENT + (3 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM2"), CTabButtonHandler::OnCAM2ButtonPress);
		buttons[3] = new CTabButton(_x + BUTTON_INDENT + (4 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM3"), CTabButtonHandler::OnCAM3ButtonPress);
		buttons[4] = new CTabButton(_x + BUTTON_INDENT + (5 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM4"), CTabButtonHandler::OnCAM4ButtonPress);
		buttons[5] = new CTabButton(_x + BUTTON_INDENT + (6 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("CAM5"), CTabButtonHandler::OnCAM5ButtonPress);
	}
		break;
	case KADR_TYPE_MAP:
	{
		_stprintf_s(buf, _T("MAP"));
		buttons[0] = new CTabButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 buf, CTabButtonHandler::OnSetButtonPress);
		buttons[1] = new CTabButton(_x + BUTTON_INDENT + (2 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("NAV"), CTabButtonHandler::OnNAVButtonPress);
		buttons[2] = new CTabButton(_x + BUTTON_INDENT + (3 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("AIR"), CTabButtonHandler::OnAIRButtonPress);
		buttons[3] = new CTabButton(_x + BUTTON_INDENT + (4 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("GRND"), CTabButtonHandler::OnGROUNDButtonPress);
		buttons[4] = new CTabButton(_x + BUTTON_INDENT + (5 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("MD1"), CTabButtonHandler::OnMODE1ButtonPress);
		buttons[5] = new CTabButton(_x + BUTTON_INDENT + (6 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
									 _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
									 _T("MD2"), CTabButtonHandler::OnMODE2ButtonPress);
	}
		break;
	case KADR_TYPE_RDR:
		_stprintf_s(buf, _T("RDR"));
		break;
	default:
		break;
	}
	if (type == KADR_TYPE_RDR || type == KADR_TYPE_PLD)
	{
		buttons[0] = new CTabButton(_x + BUTTON_INDENT + (1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)), _y + BUTTON_INDENT,
										_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
										buf, CTabButtonHandler::OnSetButtonPress);
		for (int i = 1; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
		{
			_stprintf_s(buf, _T("Â%d"), (_id + 1) * 10 + i);
			buttons[i] = new CTabButton(_x + BUTTON_INDENT + (i + 1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)),
											_y + BUTTON_INDENT,
											_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1), _cy - BUTTON_INDENT,
											buf, CTabButtonHandler::OnTabButtonPress);
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
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
	{
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
				UINT kadrID = (_blockerSide == SWIPE_DIR_LEFT) ? _id - 1 : _id;
				EKRAN_HANDLER.DivideKadr(kadrID, KADR_SIZE_HALF, _blockerSide);
				buttons[_curActive]->Disactivate();
				buttons[i]->LeftClickHandle();
			} else {
				if (kadrSelection)
					buttons[i]->LeftClickHandle();
				else
				{
					buttons[i]->LeftClickHandle();
					if (i != 0)
						buttons[i]->Activate();
					if (!kadrSelection && _isSOI)
						buttons[_curActive]->SwitchSOI(true);
				}
			}
			return;
		}
	}
	if (_id == 0)
	{
		if (hiButton[0]->PointIsMine(clickCoord))
		{
			hiButton[0]->LeftClickHandle();
			return;
		}
	}
	if (_id == DISPLAY_COLS - 1)
	{
		if (hiButton[1]->PointIsMine(clickCoord))
		{
			hiButton[1]->LeftClickHandle();
			return;
		}
	}
}

void CMechanicMenu::CHiMenu::Hide(bool hidden)
{
	_hidden = hidden;
	DisableKadrTypeSelection();
	for (CTabButton* btn : buttons)
		btn->Hide(hidden);
}

CMechanicMenu::CLoMenu::CLoMenu(UINT id) : CDrawingObject(PRIOR_MID)
{
	_id = id;
	Place();
	CreateButtons();
}

CMechanicMenu::CLoMenu::~CLoMenu()
{
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
		delete buttons[i];
}

void CMechanicMenu::CLoMenu::Place()
{
	_cy = MECHANIC_MENU_LO_HEIGHTPX;
	_x = X0_PX + _id * WIDTHPX / 4;
	_y = Y0_PX + HEIGHTPX - _cy;
	_cx = WIDTHPX / 4;
}

void CMechanicMenu::CLoMenu::LeftClickHandle(POINT clickCoord)
{
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
	{
		if (buttons[i] != nullptr && buttons[i]->PointIsMine(clickCoord))
		{
			buttons[i]->LeftClickHandle();
			return;
		}
	}
	if (_id == 0)
	{
		if (loRotary[0]->PointIsMine(clickCoord))
		{
			loRotary[0]->LeftClickHandle();
			return;
		}
	}
	if (_id == DISPLAY_COLS - 1)
	{
		if (loRotary[1]->PointIsMine(clickCoord))
		{
			loRotary[1]->LeftClickHandle();
			return;
		}
	}
}

void CMechanicMenu::CLoMenu::CreateButtons()
{
	buttons[0] = nullptr;
	for (int i = 0; i < MECH_MENU_BUTTONS_MAX_NUM; i++)
	{
		if (i < (MECH_MENU_BUTTONS_MAX_NUM - 1) / 2)
			groupName = _T("GROUP1");
		else
			groupName = _T("GROUP2");
		_stprintf_s(buf, _T("Í%d"), i);
		/*buttons[i] = new CSimpleButton(_x + BUTTON_INDENT + (i + 1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)),
									   _y + BUTTON_INDENT,
									   _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1),
									   _cy - BUTTON_INDENT,
									   buf,
									   CSimpleButtonHandler::OnSimpleButtonPress);*/
		buttons[i] = new CSwitchButton(_x + BUTTON_INDENT + (i + 1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)),
									   _y + BUTTON_INDENT,
									   _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1),
									   _cy - BUTTON_INDENT,
									   buf,
									   CSwitchButtonHandler::OnSwitchButtonPress);
		/*buttons[i] = new CRadioButton(_x + BUTTON_INDENT + (i + 1 - _id % 2) * (_cx / (MECH_MENU_BUTTONS_MAX_NUM + 1)),
									   _y + BUTTON_INDENT,
									   _cx / (MECH_MENU_BUTTONS_MAX_NUM + 1),
									   _cy - BUTTON_INDENT,
									   buf, groupName, this,
									   CRadioButtonHandler::OnRadioButtonPress);*/
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

void CMechanicMenu::CLoMenu::Hide(bool hidden)
{
	_hidden = hidden;
	for (CAbstractButton* btn : buttons)
		if (btn != nullptr)
			btn->Hide(hidden);
}