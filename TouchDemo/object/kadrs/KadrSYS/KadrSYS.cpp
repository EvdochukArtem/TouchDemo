#include "stdafx.h"
#include "KadrSYS.h"
#include "util/Util.h"

#include "EngineSys.h"

CKadrSYS::CKadrSYS(UINT id, KADR_SIZE kadrSize) : CAbstractKadr(id, kadrSize)
{
	_kadrType = KADR_TYPE_SYST;
	
	engineSysL	= nullptr;
	engineSysR	= nullptr;
	CreatePribors();
}

CKadrSYS::~CKadrSYS()
{
	DeletePribors();
}

void CKadrSYS::CreatePribors()
{
	kadrCenter.x = _x + _cx / 2;
	kadrCenter.y = _y + _cy / 2;
	switch (_kadrSize)
	{
	case KADR_SIZE_HALF:
		{
			shift.x = TO_PIXEL(-265);
			shift.y = TO_PIXEL(-320);
			engineSysL =	new CEngineSys(kadrCenter.x + shift.x, kadrCenter.y + shift.y, TO_PIXEL(160), true);
			shift.x = TO_PIXEL(-55);
			shift.y = TO_PIXEL(-320);
			engineSysR =	new CEngineSys(kadrCenter.x + shift.x, kadrCenter.y + shift.y, TO_PIXEL(160), false);
			break;
		}
	case KADR_SIZE_QUARTER:
		{		
			shift.x = TO_PIXEL(-265);
			shift.y = TO_PIXEL(-320);
			engineSysL =	new CEngineSys(kadrCenter.x + shift.x, kadrCenter.y + shift.y, TO_PIXEL(160), true);
			shift.x = TO_PIXEL(-55);
			shift.y = TO_PIXEL(-320);
			engineSysR =	new CEngineSys(kadrCenter.x + shift.x, kadrCenter.y + shift.y, TO_PIXEL(160), false);
			break;
		}
	case KADR_SIZE_EIGHTH:
		{
			shift.x = TO_PIXEL(-265);
			shift.y = TO_PIXEL(-80);
			engineSysL =	new CEngineSys(kadrCenter.x + shift.x, kadrCenter.y + shift.y, TO_PIXEL(160), true);
			shift.x = TO_PIXEL(-55);
			shift.y = TO_PIXEL(-80);
			engineSysR =	new CEngineSys(kadrCenter.x + shift.x, kadrCenter.y + shift.y, TO_PIXEL(160), false);
		}
	default:
		break;
	}
	if (_blocked)
		SetBlock(true);
}

void CKadrSYS::DeletePribors()
{
	if (engineSysL != nullptr)
	{
		delete engineSysL;
		engineSysL = nullptr;
	}
	if (engineSysR != nullptr)
	{
		delete engineSysR;
		engineSysR = nullptr;
	}
}

void CKadrSYS::ChangeSize(KADR_SIZE newSize)
{
	DeletePribors();
	_kadrSize = newSize;
	Place();
	CreatePribors();
}

CAbstractKadr* CKadrSYS::ChangePos(UINT newPos)
{
	DeletePribors();
	_id = newPos;
	Place();
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
	if (engineSysL != nullptr)
	{
		engineSysL->Hide(blockStatus);
	}
	if (engineSysR != nullptr)
	{
		engineSysR->Hide(blockStatus);
	}
}

void CKadrSYS::DrawBackground()
{
	if (_blocked)
		return;
	//‘ÓÌ
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	if (_id / 4 == 1 && _kadrSize == KADR_SIZE_EIGHTH)
	{
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
		DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	}
	DrawPlane();

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CKadrSYS::DrawPlane()
{
	switch(_kadrSize)
	{
	case KADR_SIZE_HALF:
		{
			shift.x = TO_PIXEL(-80);
			shift.y = TO_PIXEL(-240);
			SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhitePen2);

			POINT ptsPlane[] = {{_x + _cx / 2 + TO_PIXEL(55) + shift.x,  _y + _cy / 2 - TO_PIXEL(103) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(237) + shift.x, _y + _cy / 2 - TO_PIXEL(72) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(242) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y}, 
							{_x + _cx / 2 + TO_PIXEL(182) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(55) + shift.x,  _y + _cy / 2 - TO_PIXEL(103) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(237) + shift.x, _y + _cy / 2 - TO_PIXEL(72) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(242) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y}, 
							{_x + _cx / 2 - TO_PIXEL(182) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(30) + shift.x,  _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(30) + shift.x,  _y + _cy / 2 - TO_PIXEL(60) + shift.y}};
					
	
			Polyline(DRAW_ENGINE.getBackgroundHDC(), ptsPlane, 4);
			Polyline(DRAW_ENGINE.getBackgroundHDC(), &ptsPlane[4], 4);
			Polyline(DRAW_ENGINE.getBackgroundHDC(), &ptsPlane[8], 2);

			Arc(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2 - TO_PIXEL(58) + shift.x, _y + _cy / 2 - TO_PIXEL(145) + shift.y, 
												_x + _cx / 2 + TO_PIXEL(58) + shift.x, _y + _cy / 2 - TO_PIXEL(5) + shift.y, 
												_x + _cx / 2 + TO_PIXEL(60) + shift.x, _y + _cy / 2 - TO_PIXEL(105) + shift.y,
												_x + _cx / 2 - TO_PIXEL(60) + shift.x, _y + _cy / 2 - TO_PIXEL(105) + shift.y);
			break;
		}
	case KADR_SIZE_QUARTER:
		{
			shift.x = TO_PIXEL(-80);
			shift.y = TO_PIXEL(-240);
			SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhitePen2);

			POINT ptsPlane[] = {{_x + _cx / 2 + TO_PIXEL(55) + shift.x,  _y + _cy / 2 - TO_PIXEL(103) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(237) + shift.x, _y + _cy / 2 - TO_PIXEL(72) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(242) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y}, 
							{_x + _cx / 2 + TO_PIXEL(182) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(55) + shift.x,  _y + _cy / 2 - TO_PIXEL(103) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(237) + shift.x, _y + _cy / 2 - TO_PIXEL(72) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(242) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y}, 
							{_x + _cx / 2 - TO_PIXEL(182) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(30) + shift.x,  _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(30) + shift.x,  _y + _cy / 2 - TO_PIXEL(60) + shift.y}};
					
	
			Polyline(DRAW_ENGINE.getBackgroundHDC(), ptsPlane, 4);
			Polyline(DRAW_ENGINE.getBackgroundHDC(), &ptsPlane[4], 4);
			Polyline(DRAW_ENGINE.getBackgroundHDC(), &ptsPlane[8], 2);

			Arc(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2 - TO_PIXEL(58) + shift.x, _y + _cy / 2 - TO_PIXEL(145) + shift.y, 
												_x + _cx / 2 + TO_PIXEL(58) + shift.x, _y + _cy / 2 - TO_PIXEL(5) + shift.y, 
												_x + _cx / 2 + TO_PIXEL(60) + shift.x, _y + _cy / 2 - TO_PIXEL(105) + shift.y,
												_x + _cx / 2 - TO_PIXEL(60) + shift.x, _y + _cy / 2 - TO_PIXEL(105) + shift.y);
			break;
		}
	case KADR_SIZE_EIGHTH:
		{
			shift.x = TO_PIXEL(-80);
			shift.y = TO_PIXEL(0);
			SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhitePen2);

			POINT ptsPlane[] = {{_x + _cx / 2 + TO_PIXEL(55) + shift.x,  _y + _cy / 2 - TO_PIXEL(103) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(237) + shift.x, _y + _cy / 2 - TO_PIXEL(72) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(242) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y}, 
							{_x + _cx / 2 + TO_PIXEL(182) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(55) + shift.x,  _y + _cy / 2 - TO_PIXEL(103) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(237) + shift.x, _y + _cy / 2 - TO_PIXEL(72) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(242) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y}, 
							{_x + _cx / 2 - TO_PIXEL(182) + shift.x, _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 - TO_PIXEL(30) + shift.x,  _y + _cy / 2 - TO_PIXEL(60) + shift.y},
							{_x + _cx / 2 + TO_PIXEL(30) + shift.x,  _y + _cy / 2 - TO_PIXEL(60) + shift.y}};
					
	
			Polyline(DRAW_ENGINE.getBackgroundHDC(), ptsPlane, 4);
			Polyline(DRAW_ENGINE.getBackgroundHDC(), &ptsPlane[4], 4);
			Polyline(DRAW_ENGINE.getBackgroundHDC(), &ptsPlane[8], 2);

			Arc(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2 - TO_PIXEL(58) + shift.x, _y + _cy / 2 - TO_PIXEL(145) + shift.y, 
												_x + _cx / 2 + TO_PIXEL(58) + shift.x, _y + _cy / 2 - TO_PIXEL(5) + shift.y, 
												_x + _cx / 2 + TO_PIXEL(60) + shift.x, _y + _cy / 2 - TO_PIXEL(105) + shift.y,
												_x + _cx / 2 - TO_PIXEL(60) + shift.x, _y + _cy / 2 - TO_PIXEL(105) + shift.y);
			break;
		}
	}
}