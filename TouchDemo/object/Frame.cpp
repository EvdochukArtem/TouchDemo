#include "stdafx.h"
#include "Frame.h"
#include "util/Util.h"

const int BUTTON_SHIFT = TO_PIXEL(3);

CFrame::CFrame(UINT id, UINT activeButton, KADR_SIZE frameSize) : CDrawingObject(ACTIVE)
{
	_id = id;
	_activeButton = activeButton;
	_isSOI = false;
	_blocked = false;
	kadrSelection = false;
	_frameSize = frameSize;
	Dispose();
}

void CFrame::Dispose()
{
	switch (_frameSize)
	{
	case HALF:
		_cx = WIDTHPX / 2;
		_cy = HEIGHTPX;
		_x = _id * _cx / 2;
		_y = 0;
		break;
	case QUARTER:
	case EIGHTH:
		_cx = WIDTHPX / 4;
		_cy = HEIGHTPX;
		_x = (_id % 4) * _cx;
		_y =0;
		break;
	default:
		break;
	}
}

void CFrame::DrawBackground()
{
	if (_blocked)
		return;
	if (_isSOI)
		oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.YellowPen3);
	else
		oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
	DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

/*
          (2)__(3)
 (0)___(1)/      \(4)____(5)
  |                       |
  |                       |
  |         FRAME         |
  |                       |
 (5)_(4)             (1)_(0)
      \ ____________ /
      (3)          (2)
*/
void CFrame::DrawBorders(HDC& hdc)
{
	bool blockStatus = EKRAN_HANDLER.GetMechanicMenu(_id)->GetBlockStatus();

	UINT activeButton;
	if (EKRAN_HANDLER.GetMechanicMenu(_id)->GetBlockStatus())	
		activeButton = EKRAN_HANDLER.GetMechanicMenu(_id + 1)->GetActiveButtonPosition();
	else	
		activeButton = EKRAN_HANDLER.GetMechanicMenu(_id)->GetActiveButtonPosition();

	int shift = (_id % 2 == 0) ? 1 : 0;
	UINT neatIndent = TO_PIXEL(6);
	POINT border[13];
	switch(_frameSize)
	{
	case QUARTER: case EIGHTH:
		{
			//0, верхн€€ часть
			border[0].x = _id * WIDTHPX / 4;
			border[0].y = MECHANIC_MENU_HEIGHTPX;
			//1
			border[1].x = _id * WIDTHPX / 4 + (activeButton + shift) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) - neatIndent + BUTTON_SHIFT;
			border[1].y = MECHANIC_MENU_HEIGHTPX;
			//2
			border[2].x = _id * WIDTHPX / 4 + (activeButton + shift) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) + neatIndent + BUTTON_SHIFT;
			if (kadrSelection)
				border[2].y = MECHANIC_MENU_HEIGHTPX;
			else
				border[2].y = 0 + neatIndent;
			//3
			border[3].x = _id * WIDTHPX / 4 + (activeButton + shift + 1) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) - neatIndent - BUTTON_SHIFT;
			if (kadrSelection)
				border[3].y = MECHANIC_MENU_HEIGHTPX;
			else
				border[3].y = 0 + neatIndent;
			//4
			border[4].x = _id * WIDTHPX / 4 + (activeButton + shift + 1) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) + neatIndent - BUTTON_SHIFT;
			border[4].y = MECHANIC_MENU_HEIGHTPX;
			//5
			border[5].x = _id * WIDTHPX / 4 + WIDTHPX / 4;
			border[5].y = MECHANIC_MENU_HEIGHTPX;
			//0, нижн€€ часть
			border[6].x = _id * WIDTHPX / 4 + WIDTHPX / 4;
			border[6].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//1
			if (_id % 2 == 0)	border[7].x = _id * WIDTHPX / 4 + WIDTHPX / 4;
			else				border[7].x = _id * WIDTHPX / 4 + WIDTHPX / 4 - WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			border[7].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//2
			if (_id % 2 == 0)	border[8].x = _id * WIDTHPX / 4 + WIDTHPX / 4 - 2 * neatIndent;
			else				border[8].x = _id * WIDTHPX / 4 + WIDTHPX / 4 - WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1) - 2 * neatIndent;
			border[8].y = HEIGHTPX - neatIndent;
			//3
			if (_id % 2 == 0)	border[9].x = _id * WIDTHPX / 4 + WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1) + 2 * neatIndent;
			else				border[9].x = _id * WIDTHPX / 4 + 2 * neatIndent;
			border[9].y = HEIGHTPX - neatIndent;
			//4
			if (_id % 2 == 0)	border[10].x = _id * WIDTHPX / 4 + WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			else				border[10].x = _id * WIDTHPX / 4;
			border[10].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//5
			border[11].x = _id * WIDTHPX / 4;
			border[11].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//замыкание
			border[12] = border[0];
			Polyline(hdc, border, 13);

			break;
		}
	case HALF:
		{
			//0, верхн€€ часть
			border[0].x = _id * WIDTHPX / 4;
			border[0].y = MECHANIC_MENU_HEIGHTPX;
			//1
			if (blockStatus)
				border[1].x = _id * WIDTHPX / 4 + (activeButton + _id % 2) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) - neatIndent + BUTTON_SHIFT + WIDTHPX / 4;
			else
				border[1].x = _id * WIDTHPX / 4 + (activeButton + shift) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) - neatIndent + BUTTON_SHIFT;
			border[1].y = MECHANIC_MENU_HEIGHTPX;
			//2
			if (blockStatus)
				border[2].x = _id * WIDTHPX / 4 + (activeButton + _id % 2) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) + neatIndent + BUTTON_SHIFT + WIDTHPX / 4;
			else
				border[2].x = _id * WIDTHPX / 4 + (activeButton + shift) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) + neatIndent + BUTTON_SHIFT;
			if (kadrSelection)
				border[2].y = MECHANIC_MENU_HEIGHTPX;
			else
				border[2].y = 0 + neatIndent;
			//3
			if (blockStatus)
				border[3].x = _id * WIDTHPX / 4 + (activeButton + _id % 2 + 1) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) - neatIndent - BUTTON_SHIFT + WIDTHPX / 4;
			else
				border[3].x = _id * WIDTHPX / 4 + (activeButton + shift + 1) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) - neatIndent - BUTTON_SHIFT;
			if (kadrSelection)
				border[3].y = MECHANIC_MENU_HEIGHTPX;
			else
				border[3].y = 0 + neatIndent;
			//4
			if (blockStatus)
				border[4].x = _id * WIDTHPX / 4 + (activeButton + _id % 2 + 1) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) + neatIndent - BUTTON_SHIFT + WIDTHPX / 4;
			else
				border[4].x = _id * WIDTHPX / 4 + (activeButton + shift + 1) * (WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1)) + neatIndent - BUTTON_SHIFT;
			border[4].y = MECHANIC_MENU_HEIGHTPX;
			//5
			border[5].x = _id * WIDTHPX / 4 + WIDTHPX / 2;
			border[5].y = MECHANIC_MENU_HEIGHTPX;
			//0, нижн€€ часть
			border[6].x = _id * WIDTHPX / 4 + WIDTHPX / 2;
			border[6].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//1
			if (_id % 2 == 0 && blockStatus == true)		border[7].x = _id * WIDTHPX / 4 + WIDTHPX / 2 - WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			else if (_id % 2 == 1 && blockStatus == true)	border[7].x = _id * WIDTHPX / 4	+ WIDTHPX / 2;
			if (_id % 2 == 0 && blockStatus == false)		border[7].x = _id * WIDTHPX / 4 + WIDTHPX / 4;
			else if (_id % 2 == 1 && blockStatus == false)	border[7].x = _id * WIDTHPX / 4	+ WIDTHPX / 4 - WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			border[7].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//2
			if (_id % 2 == 0 && blockStatus == true)		border[8].x = _id * WIDTHPX / 4 + WIDTHPX / 2 - 2 * neatIndent - WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			else if (_id % 2 == 1 && blockStatus == true)	border[8].x = _id * WIDTHPX / 4 + WIDTHPX / 2 - 2 * neatIndent;
			if (_id % 2 == 0 && blockStatus == false)		border[8].x = _id * WIDTHPX / 4 + WIDTHPX / 4 - 2 * neatIndent;
			else if (_id % 2 == 1 && blockStatus == false)	border[8].x = _id * WIDTHPX / 4 + WIDTHPX / 4 - 2 * neatIndent - WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			border[8].y = HEIGHTPX - neatIndent;
			//3
			if (_id % 2 == 0 && blockStatus == true)		border[9].x = _id * WIDTHPX / 4 + WIDTHPX / 4 + 2 * neatIndent;
			else if (_id % 2 == 1 && blockStatus == true)	border[9].x = _id * WIDTHPX / 4 + WIDTHPX / 4 + 2 * neatIndent + WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			if (_id % 2 == 0 && blockStatus == false)		border[9].x = _id * WIDTHPX / 4 + 2 * neatIndent + WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			else if (_id % 2 == 1 && blockStatus == false)	border[9].x = _id * WIDTHPX / 4 + 2 * neatIndent;
			border[9].y = HEIGHTPX - neatIndent;
			//4
			if (_id % 2 == 0 && blockStatus == true)		border[10].x = _id * WIDTHPX / 4 + WIDTHPX / 4;
			else if (_id % 2 == 1 && blockStatus == true)	border[10].x = _id * WIDTHPX / 4 + WIDTHPX / 4 + WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			if (_id % 2 == 0 && blockStatus == false)		border[10].x = _id * WIDTHPX / 4 + WIDTHPX / 4 / (BUTTONS_MAX_NUM + 1);
			else if (_id % 2 == 1 && blockStatus == false)	border[10].x = _id * WIDTHPX / 4;
			border[10].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//5
			border[11].x = _id * WIDTHPX / 4;
			border[11].y = HEIGHTPX - MECHANIC_MENU_HEIGHTPX;
			//замыкание
			border[12] = border[0];
			Polyline(hdc, border, 13);
			break;
		}
	}
}

void CFrame::SetSOIStatus(bool soiStatus)
{
	if (soiStatus)
		_prior = SOI;
	else
		_prior = ACTIVE;
	_isSOI = soiStatus;
	DRAW_ENGINE.ResetDrawingObject(this);
}

void CFrame::ChangeSize(KADR_SIZE newSize)
{
	_frameSize = newSize;
	Dispose();
}

CFrame* CFrame::ChangePos(UINT newPos)
{
	_id = newPos;
	Dispose();
	return this;
}

void CFrame::EnableKadrTypeSelection()
{
	kadrSelection = true;
}

void CFrame::DisableKadrTypeSelection()
{
	kadrSelection = false;
}