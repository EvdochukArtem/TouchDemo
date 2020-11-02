#include "stdafx.h"
#include "KadrSYS.h"
#include "util/Util.h"

CKadrSYS::CKadrSYS(UINT id, KADR_SIZE kadrSize) : CAbstractKadr(id, kadrSize)
{
	_kadrType = SYST;
	CreatePribors();
}

CKadrSYS::~CKadrSYS()
{
	DeletePribors();
}

void CKadrSYS::CreatePribors()
{
switch (_kadrSize)
	{
	case HALF:
		engineSysL = new CEngineSys(_x + _cx / 2 - TO_PIXEL(160), _y + _cy / 2 - TO_PIXEL(70), TO_PIXEL(140), TO_PIXEL(140), true);
		engineSysR = new CEngineSys(_x + _cx / 2 + TO_PIXEL(20), _y + _cy / 2 - TO_PIXEL(70), TO_PIXEL(140), TO_PIXEL(140), false);
		break;
	case QUARTER:
		engineSysL = new CEngineSys(_x + _cx / 2 - TO_PIXEL(180), _y + _cy / 2 - TO_PIXEL(80), TO_PIXEL(160), TO_PIXEL(160), true);
		engineSysR = new CEngineSys(_x + _cx / 2 + TO_PIXEL(20), _y + _cy / 2 - TO_PIXEL(80), TO_PIXEL(160), TO_PIXEL(160), false);
		break;
	case EIGHTH:
		engineSysL = new CEngineSys(_x + _cx / 2 - TO_PIXEL(180), _y + _cy / 2 - TO_PIXEL(80), TO_PIXEL(160), TO_PIXEL(160), true);
		engineSysR = new CEngineSys(_x + _cx / 2 + TO_PIXEL(20), _y + _cy / 2 - TO_PIXEL(80), TO_PIXEL(160), TO_PIXEL(160), false);
		break;
	default:
		break;
	}
}

void CKadrSYS::DeletePribors()
{
	delete engineSysL;
	delete engineSysR;
}

void CKadrSYS::ChangeSize(KADR_SIZE newSize)
{
	_kadrSize = newSize;
	Dispose();
	DeletePribors();
	CreatePribors();
}

CAbstractKadr* CKadrSYS::ChangePos(UINT newPos)
{
	_id = newPos;
	Dispose();
	DeletePribors();
	CreatePribors();
	return this;
}

void CKadrSYS::Draw(HDC& hdc)
{
	if (_blocked)
		return;
	//::TextOut(hdc, _x+_cx/2, _y+_cy/2, L"SYSTEM KADR", 12);
	
}

void CKadrSYS::SetBlock(bool blockStatus)
{
	_blocked = blockStatus;
	Hide(blockStatus);
	engineSysL->Hide(blockStatus);
	engineSysR->Hide(blockStatus);
}

void CKadrSYS::DrawBackground()
{
	if (_blocked)
		return;
	//Ôîí
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	if (_id / 4 == 0 && _kadrSize == EIGHTH)
		Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y + _cy, _x + _cx, _y + _cy + INNER_KADR_INDENT - TO_PIXEL(2));
	if (_id / 4 == 1 && _kadrSize == EIGHTH)
	{
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
		DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	}
	
	//engineSys->DrawBackground(DRAW_ENGINE.getBackgroundHDC());

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}