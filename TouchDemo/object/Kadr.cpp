#include "StdAfx.h"
#include "object/Kadr.h"
#include "util/Util.h"

#define KADR_BORDER_Y MECHANIC_MENU_HEIGHTPX
#define KADR_BORDER_X 0
#define KADR_WORK_AREA_WIDTH (int)(WIDTHPX - 2 * KADR_BORDER_X)
#define KADR_WORK_AREA_HEIGHT (int)(HEIGHTPX - 2 * KADR_BORDER_Y)
#define DEAD_ZONE TO_PIXEL(100)
#define INNER_KADR_INDENT TO_PIXEL(10)

// This macro is used to round double and cast it to LONG
#define ROUND_DOUBLE_TO_LONG(x) ((LONG)floor(0.5 + (x)))

CKadr::CKadr(UINT id, KADR_SIZE kadrSize) : CDrawingObject(MIN)
{
	oldBrush = nullptr;
	oldPen = nullptr;
	_id = id;
	_kadrSize = kadrSize;

	ID = id;

	PlaceKadr();

	_rotationAngle = 0;
	_scalingFactor = 1;

	InitInteractiveObj();

	_isSOI = false;
	_blocked = false;
}

void CKadr::PlaceKadr()
{
	switch (_kadrSize)
	{
	case FULL:
		_x = KADR_BORDER_X;
		_y = KADR_BORDER_Y;
		_cx = KADR_WORK_AREA_WIDTH;
		_cy = KADR_WORK_AREA_HEIGHT;
		break;
	case HALF:
		_cx = KADR_WORK_AREA_WIDTH / 2;
		_cy = KADR_WORK_AREA_HEIGHT;
		_y = KADR_BORDER_Y;
		_x = KADR_BORDER_X + _id * _cx / 2;
		break;
	case QUATER:
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
	//Рамки
	/*if (_isSOI)
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.YellowPen3);
	else
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
	MoveToEx(DRAW_ENGINE.getBackgroundHDC(), _x, _y, NULL);
	LineTo(DRAW_ENGINE.getBackgroundHDC(), _x, _y + _cy);
	MoveToEx(DRAW_ENGINE.getBackgroundHDC(), _x + _cx, _y, NULL);
	LineTo(DRAW_ENGINE.getBackgroundHDC(), _x +_cx, _y + _cy);
	if (_kadrSize == EIGHTH && _id / 4 == 0)
	{
		MoveToEx(DRAW_ENGINE.getBackgroundHDC(), _x, _y + _cy, NULL);
		LineTo(DRAW_ENGINE.getBackgroundHDC(), _x +_cx, _y + _cy);
	}*/
}

void CKadr::Draw(HDC hdc)
{
	if (_blocked)
		return;
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreyPen2);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.LightGreyBrush);

	DrawInteractiveObj(hdc);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
}

void CKadr::ChangeSOIStatus()
{
	_isSOI = !_isSOI;
}

void CKadr::ChangeSize(KADR_SIZE newSize)
{
	_kadrSize = newSize;
	PlaceKadr();
	InitInteractiveObj();
}

CKadr* CKadr::ChangePos(UINT newPos)
{
	_id = newPos;
	PlaceKadr();
	InitInteractiveObj();
	return this;
}

void CKadr::DrawInteractiveObj(HDC hdc)
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
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize < QUATER) //TODO: мб это стоит переделать лаконичнее
			if (firstTouchCoord.x < secondTouchCoord.x)
				EKRAN_HANDLER.DivideKadr(_id, _kadrSize, RIGHT);
			else
				EKRAN_HANDLER.DivideKadr(_id, _kadrSize, LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && firstTouchCoord.y > secondTouchCoord.y && this->_kadrSize == QUATER)
			EKRAN_HANDLER.DivideKadr(_id, _kadrSize, RIGHT); //тут направление не важно на самом деле
	}
	else
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize <= QUATER)
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