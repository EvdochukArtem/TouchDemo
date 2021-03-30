#include "stdafx.h"
#include "KadrMAP.h"
#include "util/Util.h"
#include "../../buttons/touchButtons/SwitchTButton.h"

#include "KadrMAPButtons.h"
#include "Map/MapPage.h"
#include "Database/DatabasePage.h"
#include "Map/ScaleCircle.h"

CKadrMAP::CKadrMAP(UINT id, KADR_SIZE kadrSize) : CAbstractKadr(id, kadrSize)
{
	_kadrType = KADR_TYPE_MAP;

	priborRgn = nullptr;
	
	mapCenterCoord.x = 0;
	mapCenterCoord.y = 0;
	planePoint.x = 0;
	planePoint.y = 0;
	mapMove.x = 0;
	mapMove.y = 0;

	settings.declutterState = 4;
	settings.scaleIndex = 3;
	
	dataBaseIsOn	= false;
	oldScale = 0.0f;

	myPlane = new MyPlane(this);
	coordSys = COORD_SYS_PLN;

	buttons = nullptr;
	for (int i = 0; i < MAP_PAGES_MAX; i++)
		pages[i] = nullptr;

	CalculateConstants();
	CreatePribors();
}

CKadrMAP::~CKadrMAP()
{
	DeletePribors();
	delete myPlane;
	if (priborRgn != nullptr)
	{
		DeleteObject(priborRgn);
		priborRgn = nullptr;
	}
}

void CKadrMAP::CreatePribors()
{
	buttons		= new CKadrMAPButtons(this);
	pages[0] = new CMapPage(this, PAGE_MAP);
	//pages[1] = new CDatabasePage(this, PAGE_BD);
}

void CKadrMAP::DeletePribors()
{
	if (buttons != nullptr)
	{
		delete buttons;
		buttons = nullptr;
	}
	for (int i = 0; i < MAP_PAGES_MAX; i++)
		if (pages[i] != nullptr)
		{
			delete pages[i];
			pages[i] = nullptr;
		}
}

void CKadrMAP::DisposePribors()
{	
	if (buttons != nullptr)
		buttons->Place();
	if (_blocked)
		SetBlock(true);
}

void CKadrMAP::SetBlock(bool blockStatus)
{
	_blocked = blockStatus;
	Hide(blockStatus);
	
	if (buttons != nullptr)
		buttons->Hide(blockStatus);
	if (myPlane != nullptr)
		myPlane->Hide(blockStatus);
	if (dataBaseIsOn)
	{
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_BD)
				page->Hide(blockStatus);
	} else 
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_MAP)
				page->Hide(blockStatus);


}

void CKadrMAP::CalculateConstants()
{
	mapCenterPoint.x = _x + _cx / 2;
	mapCenterPoint.y = _y + _cy * 2 / 3;
	settings.scale = (float)MapScale[settings.scaleIndex] * 1000 / float(CIRCLE_STEP * TACT_SCALE_CIRCLES);
	if (priborRgn != nullptr)
	{
		DeleteObject(priborRgn);
		priborRgn = nullptr;
	}
	priborRgn = CreateRectRgn(_x + TO_PIXEL(4), _y + TO_PIXEL(4), _x + _cx - TO_PIXEL(4), _y + _cy - TO_PIXEL(4));
}

void CKadrMAP::Draw(HDC& hdc)
{
	if (_blocked)
		return;

	POINT planePt{ 0, 0 };//Позиция самолета из внешнего прибора
	planePoint.x = (LONG)(planePt.x + 0.5f);
	planePoint.y = (LONG)(planePt.y + 0.5f);
	mapCenterCoord = MapScreenToGeo(mapCenterPoint);

	//::TextOut(hdc, _x+_cx/2, _y+_cy/2, _T("Kadr KADR_TYPE_MAP"), 9);
}

void CKadrMAP::DrawBackground()
{
	if (_blocked)
		return;
	//Фон
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

void CKadrMAP::ChangeSize(KADR_SIZE newSize)
{
	_kadrSize = newSize;
	Place();
	CalculateConstants();
	DisposePribors();
	for (CPage* page : pages)
		if (page != nullptr)
		{
			page->DisposePribors();
			if (_blocked)
				page->Hide(true);
		}
}

CAbstractKadr* CKadrMAP::ChangePos(UINT newPos)
{
	_id = newPos;
	Place();
	CalculateConstants();
	DisposePribors();
	for (CPage* page : pages)
		if (page != nullptr)
		{
			page->DisposePribors();
			if (_blocked)
				page->Hide(true);
		}
	return this;
}

void CKadrMAP::Zoom(const double dZoomFactor, const POINT zoomCenter)
{
	if (dZoomFactor > 1)
		NextScale();
	else
		PrevScale();
}

void CKadrMAP::NextScale()
{
	settings.scaleIndex++;
	if (sizeof(MapScale)/sizeof(MapScale[0]) == settings.scaleIndex)
		settings.scaleIndex = sizeof(MapScale)/sizeof(MapScale[0])-1;

    settings.scale = (float)MapScale[settings.scaleIndex] * 1000 / float(CIRCLE_STEP * TACT_SCALE_CIRCLES);
}

void CKadrMAP::PrevScale()
{
	settings.scaleIndex--;
	if (-1 == settings.scaleIndex)
		settings.scaleIndex = 0;

	settings.scale = (float)MapScale[settings.scaleIndex] * 1000 / float(CIRCLE_STEP * TACT_SCALE_CIRCLES);
}

POINT CKadrMAP::MapScreenToGeo(POINT position)
{
	POINT tmp{ position.y, position.x };
	return tmp;
}

POINT CKadrMAP::MapGeoToScreen(POINT position)
{
	POINT tmp{ position.y, position.x };
	return tmp;
}

CKadrMAP::MyPlane::MyPlane(CKadrMAP* kadr) : CDrawingObject(PRIOR_PLANE)
{
	kadrMAP = kadr;
}

void CKadrMAP::MyPlane::Draw(HDC &hdc)
{
	if(_hidden)
		return;

	SelectClipRgn(hdc, kadrMAP->GetKadrRgn());
	double Angle;
	Angle = kadrMAP->AngleZeroIfPLN();

	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.GreyBrush);
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreyPen);

	DrawPlane(hdc, kadrMAP, kadrMAP->GetPlanePoint().x, kadrMAP->GetPlanePoint().y, Angle, DRAW_KIT.GreenPen, DRAW_KIT.GreenBrush);
	
	
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);	
	SelectClipRgn(hdc, nullptr);
}


double CKadrMAP::AngleZeroIfPLN()
{
	return (COORD_SYS_PLN == coordSys) ? 0 : /*информация о азимуте из внешнего источника*/ 30;
}

double CKadrMAP::AnglePsiIfPLN()
{
	return (COORD_SYS_PLN == coordSys) ? /*информация о азимуте из внешнего источника*/ 30 : 0;
}

void CKadrMAP::DrawPlane(HDC &hdc, CKadrMAP* kadr, int x, int y, double Kurs, HPEN  pen_Plan, HBRUSH brush_Plan)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, pen_Plan);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush_Plan);

	POINT pts[17];
	POINT plane[] = {{0, -13},
					{2, -6},
					{8, 1},
					{8, 3},
					{3, 2},
					{3, 4},
					{6, 8},
					{5, 9},
					{2, 7},
					{-2, 7},
					{-5, 9},
					{-6, 8},
					{-3, 4},
					{-3, 2},
					{-8, 3},
					{-8, 1},
					{-2, -6}};

	for (int i = 0; i < sizeof(plane)/sizeof(POINT); i++)
		pts[i] = Rotate(plane[i], (double)Kurs, x, y);
	Polygon(hdc, pts, sizeof(plane)/sizeof(POINT));
	
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

void CKadrMAP::LeftClickHandle(POINT pt)
{
	if (buttons->HandleTouch(pt))
		return;
}

void CKadrMAP::Move(const POINT firstTouchCoord, const POINT delta)
{
	mapMove.x += delta.x;
	mapMove.y += delta.y;
}

void CKadrMAP::Reset()
{
	coordSys = COORD_SYS_PLN;
	mapMove.x = 0;
	mapMove.y = 0;
	buttons->GetCoordSysButton().SetFirstStatus();
}

void CKadrMAP::ProcessKeyboard(UINT key)
{
}

void CKadrMAP::ProcessCommand(KADR_COMMANDS cmd)
{
	switch (cmd)
	{
	case KADR_COMM_ENABLE_SUBMENU:
		_subMenu = true;
		buttons->EnableSubmenu();
		break;
	case KADR_COMM_DISABLE_SUBMENU:
		_subMenu = false;
		buttons->DisableSubmenu();
		break;
	case KADR_COMM_SWITCH_COORD_SYS:
		if (coordSys == COORD_SYS_PLN)
		{
			coordSys = COORD_SYS_NRTH;
		} else {
			coordSys = COORD_SYS_PLN;
		}
		break;
	default:
		break;
	}
}