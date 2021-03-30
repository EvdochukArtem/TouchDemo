#include "StdAfx.h"
#include "BlankAuxKadr.h"
#include "util/Util.h"
#include "../../buttons/touchButtons/SimpleTButtonHandler.h"

CBlankAuxKadr::CBlankAuxKadr(UINT id, KADR_SIZE kadrSize) : CAbstractKadr(id, kadrSize)
{
	_kadrType = KADR_TYPE_AUX;
	for (int i = 0; i < AUX_KADRS_MAX_NUM; i++)
		btn[i] = nullptr;
	BtnInit();
}

CBlankAuxKadr::~CBlankAuxKadr()
{
	for (int i = 0; i < AUX_KADRS_MAX_NUM; i++)
	{
		delete btn[i];
		btn[i] = nullptr;
	}
}

void CBlankAuxKadr::BtnInit()
{
	btn[0] = new CSimpleTButton(_x + _cx / 2 - TBUTTON_HOR_INDENT - TBUTTON_SIDE_SIZE,
								_y + _cy / 2 - TBUTTON_HOR_INDENT - TBUTTON_SIDE_SIZE,
								_T("RDR"), CSimpleTButtonHandler::OnRDRButtonPress);
	
	btn[1] = new CSimpleTButton(_x + _cx / 2 + TBUTTON_HOR_INDENT,
								_y + _cy / 2 - TBUTTON_HOR_INDENT - TBUTTON_SIDE_SIZE,
								_T("CAM"), CSimpleTButtonHandler::OnCAMButtonPress);
	
	btn[2] = nullptr;
	
	btn[3] = new CSimpleTButton(_x + _cx / 2 + TBUTTON_HOR_INDENT,
								_y + _cy / 2 + TBUTTON_HOR_INDENT,
								_T("KBRD"), CSimpleTButtonHandler::OnKBRDButtonPress);
}

void CBlankAuxKadr::DrawBackground()
{
	if (_blocked)
		return;
	//Ôîí
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	if (_id / 4 == 1 && _kadrSize == KADR_SIZE_EIGHTH)
	{
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
		DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	}
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CBlankAuxKadr::Draw(HDC& hdc)
{
	if (_blocked)
		return;
}

void CBlankAuxKadr::Hide(bool hidden)
{
	_hidden = hidden;
	if (btn[0] != nullptr)
		for (int i = 0; i < AUX_KADRS_MAX_NUM; i++)
			btn[i]->Hide(hidden);
}

void CBlankAuxKadr::LeftClickHandle(POINT clickCoord)
{
	if (btn[0] != nullptr)
		for (int i = 0; i < AUX_KADRS_MAX_NUM; i++)
			if (btn[i]->PointIsMine(clickCoord))
			{
				btn[i]->LeftClickHandle();
				return;
			}
}