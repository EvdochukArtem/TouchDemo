#include "StdAfx.h"
#include "Kadr.h"
#include "util/Util.h"

// Нет ли смысла уйти от тяжкого наследия Си и заменить макроопределения на константы?
#define KADR_BORDER_Y			MECHANIC_MENU_HEIGHTPX
#define KADR_BORDER_X			0
#define KADR_WORK_AREA_WIDTH	(WIDTHPX - 2 * KADR_BORDER_X)
#define KADR_WORK_AREA_HEIGHT	(HEIGHTPX - 2 * KADR_BORDER_Y)
#define DEAD_ZONE				TO_PIXEL(100)
#define INNER_KADR_INDENT		TO_PIXEL(10)
#define TIMER_ID				(001)

// This macro is used to round double and cast it to LONG
#define ROUND_DOUBLE_TO_LONG(x) ((LONG)floor(0.5 + (x)))

CKadr* CKadr::pKadr = nullptr;

CKadr::CKadr(UINT id, KADR_SIZE kadrSize) : CDrawingObject(MIN)
{
	oldBrush = nullptr;
	oldPen = nullptr;
	_id = id;
	_kadrSize = kadrSize;
	_kadrType = EMPTY;

	ID = id;

	for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
		btn[i] = nullptr;

	PlaceKadr();

	_rotationAngle = 0;
	_scalingFactor = 1;

	InitInteractiveObj();

	_isSOI = false;
	_blocked = false;
}

CKadr::~CKadr()
{
	for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
	{
		delete btn[i];
		btn[i] = nullptr;
	}
}

void CKadr::PlaceKadr()
{
	switch (_kadrSize)
	{
	case HALF:
		_cx = KADR_WORK_AREA_WIDTH / 2;
		_cy = KADR_WORK_AREA_HEIGHT;
		_y = KADR_BORDER_Y;
		_x = KADR_BORDER_X + _id * _cx / 2;
		break;
	case QUARTER:
		_cy = KADR_WORK_AREA_HEIGHT;
		_cx = KADR_WORK_AREA_WIDTH / 4;
		_y = KADR_BORDER_Y;
		_x = KADR_BORDER_X + (_id % 4) * _cx;
		break;
	case EIGHTH:
		if (_id / 4 == 0)
		{
			_cx = KADR_WORK_AREA_WIDTH / 4;
			_cy = KADR_WORK_AREA_HEIGHT / 2;
			_x = KADR_BORDER_X + (_id % 4) * _cx;
			_y = KADR_BORDER_Y;
		} else {
			_cx = KADR_WORK_AREA_WIDTH / 4 - 2 * INNER_KADR_INDENT;
			_cy = (KADR_WORK_AREA_HEIGHT) / 2 - 2 * INNER_KADR_INDENT;
			_x = KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4) + INNER_KADR_INDENT;
			_y = KADR_BORDER_Y + KADR_WORK_AREA_HEIGHT / 2 + INNER_KADR_INDENT;
		}
		break;
	default:
		break;
	}
}

void CKadr::InitInteractiveObj()
{
	interactiveObj[0].x = _x + _cx / 2;
	interactiveObj[0].y = _y + _cy / 2;
	interactiveObj[1].x = interactiveObj[0].x - 30;
	interactiveObj[1].y = interactiveObj[0].y + 30;
	interactiveObj[2].x = interactiveObj[0].x + 30;
	interactiveObj[2].y = interactiveObj[0].y + 30;
	interactiveObj[3] = interactiveObj[0];
}

void CKadr::BtnInit()
{
	btn[0] = new CMenuButton(_x + _cx / 2 - TO_PIXEL(25), _y + _cy / 7.0,
							 TO_PIXEL(100), TO_PIXEL(50),
							 _T("PLD"), CMenuButtonHandler::OnPLDButtonPress);
	
	btn[1] = new CMenuButton(_x + _cx / 2 - TO_PIXEL(25), _y + 2 * _cy / 7.0,
							 TO_PIXEL(100), TO_PIXEL(50),
							 _T("SYST"), CMenuButtonHandler::OnSYSTButtonPress);
	
	btn[2] = new CMenuButton(_x + _cx / 2 - TO_PIXEL(25), _y + 3 * _cy / 7.0,
							 TO_PIXEL(100), TO_PIXEL(50),
							 _T("CAM"), CMenuButtonHandler::OnCAMButtonPress);
	
	btn[3] = new CMenuButton(_x + _cx / 2 - TO_PIXEL(25), _y + 4 * _cy / 7.0,
							 TO_PIXEL(100), TO_PIXEL(50),
							 _T("MAP"), CMenuButtonHandler::OnMAPButtonPress);
	
	btn[4] = new CMenuButton(_x + _cx / 2 - TO_PIXEL(25), _y + 5 * _cy / 7.0,
							 TO_PIXEL(100), TO_PIXEL(50),
							 _T("RDR"), CMenuButtonHandler::OnRDRButtonPress);
}

void CKadr::DrawBackground()
{
	if (_blocked)
		return;
	//Фон
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	if (_id / 4 == 1 && _kadrSize == EIGHTH)
	{
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
		DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	}
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CKadr::Draw(HDC& hdc)
{
	if (_blocked)
		return;
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreyPen2);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.LightGreyBrush);
	
	if (btn[0] == nullptr)
		BtnInit();

	for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
		btn[i]->DrawBorders(hdc);
	//DrawInteractiveObj(hdc);
	SelectObject(hdc, DRAW_KIT.WhitePen2);
	if (_paintClickZone)
		Arc(hdc, _ptCoords.x - 10, _ptCoords.y - 10, _ptCoords.x + 10, _ptCoords.y + 10, 0, 0, 0, 0);
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
}

void CKadr::SetSOIStatus(bool soiStatus)
{
	_isSOI = soiStatus;
}

void CKadr::ChangeSize(KADR_SIZE newSize)
{
	_kadrSize = newSize;
	PlaceKadr();
	InitInteractiveObj();
	if (btn[0] != nullptr)
		for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
			btn[i]->ChangePos(_x + _cx / 2 - TO_PIXEL(25), _y + (i + 1) * (_cy / 7.0));
}

CKadr* CKadr::ChangePos(UINT newPos)
{
	_id = newPos;
	PlaceKadr();
	InitInteractiveObj();
	if (btn[0] != nullptr)
		for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
			btn[i]->ChangePos(_x + _cx / 2 - TO_PIXEL(25), _y + (i + 1) * (_cy / 7.0));
	return this;
}

void CKadr::DrawInteractiveObj(HDC& hdc)
{
	_stprintf_s(buf, _T("%d"), ID + 1);
	Polygon(hdc, interactiveObj, 4);
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, interactiveObj[0].x, interactiveObj[0].y + TO_PIXEL(25), buf, (int)_tcslen(buf));
	SetTextAlign(hdc, oldTextAlign);
}

void CKadr::Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
{
	if (PointIsMine(secondTouchCoord))
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize < QUARTER) //TODO: мб это стоит переделать лаконичнее
			if (firstTouchCoord.x < secondTouchCoord.x)
				EKRAN_HANDLER.DivideKadr(_id, _kadrSize, RIGHT);
			else
				EKRAN_HANDLER.DivideKadr(_id, _kadrSize, LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && firstTouchCoord.y > secondTouchCoord.y && this->_kadrSize == QUARTER)
			EKRAN_HANDLER.DivideKadr(_id, _kadrSize, RIGHT); //тут направление не важно на самом деле
	}
	else
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize <= QUARTER)
			if (firstTouchCoord.x < secondTouchCoord.x)
				EKRAN_HANDLER.MergeKadr(_id, _kadrSize, RIGHT);
			else
				EKRAN_HANDLER.MergeKadr(_id, _kadrSize, LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && firstTouchCoord.y < secondTouchCoord.y && this->_kadrSize == EIGHTH)
			EKRAN_HANDLER.MergeKadr(_id, _kadrSize, RIGHT); //тут направление не важно на самом деле
	}
}

void CKadr::Reset()
{
	ResetInteractiveObject();
}

void CKadr::ResetInteractiveObject()
{
	_rotationAngle = 0;
	_scalingFactor = 1;
	InitInteractiveObj();
}

void CKadr::Move(const POINT firstTouchCoord, const POINT delta)
{
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		if ((interactiveObj[i].x + delta.x) > (LONG)(_x + _cx) ||
			(interactiveObj[i].x + delta.x) < (LONG)_x ||
			(interactiveObj[i].y + delta.y) > (LONG)(_y + _cy) ||
			(interactiveObj[i].y + delta.y) < (LONG)_y)
			return;
	}
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		interactiveObj[i].x += delta.x;
		interactiveObj[i].y += delta.y;
	}
}

void CKadr::Zoom(const double dZoomFactor, const POINT zoomCenter) 
{
	POINT tmpPoint[INTERACTIVE_OBJ_LENGTH];
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		tmpPoint[i].x = ROUND_DOUBLE_TO_LONG(zoomCenter.x * (1.0 - dZoomFactor) + interactiveObj[i].x * dZoomFactor);
		tmpPoint[i].y = ROUND_DOUBLE_TO_LONG(zoomCenter.y * (1.0 - dZoomFactor) + interactiveObj[i].y * dZoomFactor);
	}
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
		if (PointIsMine(tmpPoint[i]) == false)
			return;
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		interactiveObj[i].x = tmpPoint[i].x;
		interactiveObj[i].y = tmpPoint[i].y;
	}
	_scalingFactor *= dZoomFactor;
}

void CKadr::Rotate(const double dAngle, const POINT rotateCenter)
{
	double dCos = cos(dAngle);
	double dSin = sin(dAngle);

	POINT tmpPoint[INTERACTIVE_OBJ_LENGTH];
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		LONG lDX = interactiveObj[i].x - rotateCenter.x;
		LONG lDY = interactiveObj[i].y - rotateCenter.y;
		tmpPoint[i].x = rotateCenter.x + ROUND_DOUBLE_TO_LONG(lDX * dCos + lDY * dSin);
		tmpPoint[i].y = rotateCenter.y + ROUND_DOUBLE_TO_LONG(lDY * dCos - lDX * dSin);
	}
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
		if (PointIsMine(tmpPoint[i]) == false)
			return;
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		interactiveObj[i].x = tmpPoint[i].x;
		interactiveObj[i].y = tmpPoint[i].y;
	}
	_rotationAngle += dAngle;
}

void CKadr::Hide(bool hidden)
{
	_hidden = hidden;
	if (btn[0] != nullptr)
		for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
			btn[i]->Hide(hidden);
}

void CKadr::LeftClickHandle(POINT clickCoord)
{
	if (_hidden)
		return;
	if (btn[0] != nullptr)
		for (int i = 0; i < MAX_KADR_TYPE - 1; i++)
			if (btn[i]->PointIsMine(clickCoord))
			{
				btn[i]->LeftClickHandle();
				return;
			}
	_ptCoords = clickCoord;
	_paintClickZone = true;
	CKadr::pKadr = this;
	SetTimer(NULL, TIMER_ID, 150, (TIMERPROC) TimerProc);
}

void CKadr::TimerProc(HWND hWnd, UINT message, UINT idTimer, DWORD dwTime)
{
	CKadr::pKadr->_paintClickZone = false;
	KillTimer(hWnd, TIMER_ID);
}