#include "stdafx.h"
#include "AbstractKadr.h"
#include "util/Util.h"

// Ќет ли смысла уйти от т€жкого наследи€ —и и заменить макроопределени€ на константы?
#define KADR_BORDER_Y_HI		MECHANIC_MENU_HEIGHTPX //* 2
#define KADR_BORDER_Y_LO		MECHANIC_MENU_HEIGHTPX
#define KADR_BORDER_X			0
#define KADR_WORK_AREA_WIDTH	(WIDTHPX - 2 * KADR_BORDER_X)
#define KADR_WORK_AREA_HEIGHT	(HEIGHTPX - KADR_BORDER_Y_HI - KADR_BORDER_Y_LO)
#define DEAD_ZONE				TO_PIXEL(100)

CAbstractKadr::CAbstractKadr(UINT id, KADR_SIZE kadrSize) : CDrawingObject(MIN)
{
	oldBrush = nullptr;
	oldPen = nullptr;
	_id = id;
	_isSOI = false;
	_blocked = false;
	_kadrSize = kadrSize;
	_rotationAngle = 0;
	_scalingFactor = 1;
	PlaceKadr();
}

void CAbstractKadr::SetSOIStatus(bool soiStatus)
{
	_isSOI = soiStatus;
}

void CAbstractKadr::PlaceKadr()
{
	switch (_kadrSize)
	{
	case HALF:
		_cx = KADR_WORK_AREA_WIDTH / 2;
		_cy = KADR_WORK_AREA_HEIGHT;
		_y = KADR_BORDER_Y_HI;
		_x = KADR_BORDER_X + _id * _cx / 2;
		break;
	case QUARTER:
		_cy = KADR_WORK_AREA_HEIGHT;
		_cx = KADR_WORK_AREA_WIDTH / 4;
		_y = KADR_BORDER_Y_HI;
		_x = KADR_BORDER_X + (_id % 4) * _cx;
		break;
	case EIGHTH:
		if (_id / 4 == 0)
		{
			_cx = KADR_WORK_AREA_WIDTH / 4;
			_cy = KADR_WORK_AREA_HEIGHT / 2;
			_x = KADR_BORDER_X + (_id % 4) * _cx;
			_y = KADR_BORDER_Y_HI;
		} else {
			_cx = KADR_WORK_AREA_WIDTH / 4 - 2 * INNER_KADR_INDENT;
			_cy = (KADR_WORK_AREA_HEIGHT) / 2 - 2 * INNER_KADR_INDENT;
			_x = KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4) + INNER_KADR_INDENT;
			_y = KADR_BORDER_Y_HI + KADR_WORK_AREA_HEIGHT / 2 + INNER_KADR_INDENT;
		}
		break;
	default:
		break;
	}
}

void CAbstractKadr::Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
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