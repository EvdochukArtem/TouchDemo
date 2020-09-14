#include "StdAfx.h"
#include "object/Kadr.h"
#include "util/Util.h"

#define KADR_BORDER_Y MECHANIC_MENU_HEIGHTPX
#define KADR_BORDER_X 0
#define KADR_WORK_AREA_WIDTH (int)(WIDTHPX - 2 * KADR_BORDER_X)
#define KADR_WORK_AREA_HEIGHT (int)(HEIGHTPX - 2 * KADR_BORDER_Y)
#define DEAD_ZONE 100

// This macro is used to round double and cast it to LONG
#define ROUND_DOUBLE_TO_LONG(x) ((LONG)floor(0.5 + (x)))

CKadr::CKadr(UINT id, KADR_SIZE kadrSize)
{
	oldBrush = NULL;
	oldPen = NULL;
	_id = id;
	_kadrSize = kadrSize;

	CreateKadr();

	_rotationAngle = 0;
	_scalingFactor = 1;

	InitInteractiveObj();
}

void CKadr::CreateKadr()
{
	switch (_kadrSize)
	{
	case FULL:
		_cx = KADR_WORK_AREA_WIDTH;
		_cy = KADR_WORK_AREA_HEIGHT;
		_x = KADR_BORDER_X;
		_y = KADR_BORDER_Y;
		break;
	case HALF:
		_cx = KADR_WORK_AREA_WIDTH / 2;
		_cy = KADR_WORK_AREA_HEIGHT;
		_x = KADR_BORDER_X + _id * _cx / 2;
		_y = KADR_BORDER_Y;
		break;
	case QUATER:
		_cx = KADR_WORK_AREA_WIDTH / 4;
		_cy = KADR_WORK_AREA_HEIGHT;
		_x = KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4);
		_y = KADR_BORDER_Y;
		break;
	case EIGHTH:
		_cx = KADR_WORK_AREA_WIDTH / 4;
		_cy = (KADR_WORK_AREA_HEIGHT) / 2;
		_x = KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4);
		_y = KADR_BORDER_Y + (_id / 4) * _cy;
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
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhiteBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);

	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen2);
	DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CKadr::Draw(HDC hdc)
{
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.BlackPen2);

	DrawInteractiveObj(hdc);

	SelectObject(hdc, oldPen);
}

void CKadr::DrawInteractiveObj(HDC hdc)
{
	Polyline(hdc, interactiveObj, 4);
}

void CKadr::Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
{
	if (PointIsMine(secondTouchCoord))
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize < QUATER) //TODO: мб это стоит переделать лаконичнее
			EKRAN_HANDLER.DivideKadr(_id, _kadrSize);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && this->_kadrSize == QUATER)
			EKRAN_HANDLER.DivideKadr(_id, _kadrSize);
	}
	else
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize <= QUATER)
			if (firstTouchCoord.x < secondTouchCoord.x)
				EKRAN_HANDLER.MergeKadr(_id, _kadrSize, RIGHT);
			else
				EKRAN_HANDLER.MergeKadr(_id, _kadrSize, LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && this->_kadrSize == EIGHTH)
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