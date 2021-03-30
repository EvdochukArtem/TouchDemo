#include "stdafx.h"
#include "AbstractKadr.h"
#include "util/Util.h"

#define DEAD_ZONE				TO_PIXEL(100)

CAbstractKadr::CAbstractKadr(UINT id, KADR_SIZE kadrSize) : CDrawingObject(PRIOR_MIN)
{
	oldBrush = nullptr;
	oldPen = nullptr;
	_id = id;
	_isSOI = false;
	_blocked = false;
	_kadrSize = kadrSize;
	_rotationAngle = 0;
	_scalingFactor = 1;
	_subMenu = false;
	Place();
}

void CAbstractKadr::SetSOIStatus(bool soiStatus)
{
	_isSOI = soiStatus;
}

void CAbstractKadr::Place()
{
	switch (_kadrSize)
	{
	case KADR_SIZE_HALF:
		_cx	= KADR_WORK_AREA_WIDTH / 2;
		_cy	= KADR_WORK_AREA_HEIGHT;
		_y	= Y0_PX + KADR_BORDER_Y_HI;
		_x	= X0_PX + KADR_BORDER_X + _id * _cx / 2;
		break;
	case KADR_SIZE_QUARTER:
		_cy	= KADR_WORK_AREA_HEIGHT;
		_cx	= KADR_WORK_AREA_WIDTH / 4;
		_y	= Y0_PX + KADR_BORDER_Y_HI;
		_x	= X0_PX + KADR_BORDER_X + (_id % 4) * _cx;
		break;
	case KADR_SIZE_EIGHTH:
		if (_id / 4 == 0)
		{
			_cx = KADR_WORK_AREA_WIDTH / 4;
			_cy = KADR_WORK_AREA_HEIGHT / 2;
			_x = X0_PX + KADR_BORDER_X + (_id % 4) * _cx;
			_y = Y0_PX + KADR_BORDER_Y_HI;
		} else {
			_cx = KADR_WORK_AREA_WIDTH / 4 - 2 * INNER_KADR_INDENT;
			_cy = KADR_WORK_AREA_HEIGHT / 2 - 2 * INNER_KADR_INDENT;
			_x = X0_PX + KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4) + INNER_KADR_INDENT;
			_y = Y0_PX + KADR_BORDER_Y_HI + KADR_WORK_AREA_HEIGHT / 2 + INNER_KADR_INDENT;
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
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize < KADR_SIZE_QUARTER) //TODO: мб это стоит переделать лаконичнее
			if (firstTouchCoord.x < secondTouchCoord.x)
				EKRAN_HANDLER.DivideKadr(_id, _kadrSize, SWIPE_DIR_RIGHT);
			else
				EKRAN_HANDLER.DivideKadr(_id, _kadrSize, SWIPE_DIR_LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && firstTouchCoord.y > secondTouchCoord.y && this->_kadrSize == KADR_SIZE_QUARTER)
			EKRAN_HANDLER.DivideKadr(_id, _kadrSize, SWIPE_DIR_RIGHT); //тут направление не важно на самом деле
	}
	else
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize <= KADR_SIZE_QUARTER)
			if (firstTouchCoord.x < secondTouchCoord.x)
				EKRAN_HANDLER.MergeKadr(_id, _kadrSize, SWIPE_DIR_RIGHT);
			else
				EKRAN_HANDLER.MergeKadr(_id, _kadrSize, SWIPE_DIR_LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && firstTouchCoord.y < secondTouchCoord.y && this->_kadrSize == KADR_SIZE_EIGHTH)
			EKRAN_HANDLER.MergeKadr(_id, _kadrSize, SWIPE_DIR_RIGHT); //тут направление не важно на самом деле
	}
}