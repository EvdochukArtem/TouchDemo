#include "Kadr.h"
#include "KadrHandler.h"
#include "DrawEngine.h"

#define KADR_BORDER_Y 25
#define KADR_BORDER_X 0
#define KADR_WORK_AREA_WIDTH (int)(WIDTHPX - 2 * KADR_BORDER_X)
#define KADR_WORK_AREA_HEIGHT (int)(HEIGHTPX - 2 * KADR_BORDER_Y)
#define CAPTION_CORRECTION GetSystemMetrics(SM_CYCAPTION)
#define DEAD_ZONE 100

// This macro is used to round double and cast it to LONG
#define ROUND_DOUBLE_TO_LONG(x) ((LONG)floor(0.5 + (x)))

CKadr::CKadr(UINT id, KADR_SIZE kadrSize)
{
	hOld = NULL;
	_id = id;
	_kadrSize = kadrSize;

	CreateKadr();
	RegisterDrawingObject();

	_rotationAngle = 0;
	_scalingFactor = 1;

	InitInteractiveObj();
}

CKadr::~CKadr()
{
	DeleteDrawingObject();
}

void CKadr::CreateKadr()
{
	switch (_kadrSize)
	{
	case FULL:
		_width = KADR_WORK_AREA_WIDTH;
		_height = KADR_WORK_AREA_HEIGHT + KADR_BORDER_Y;
		_x = KADR_BORDER_X;
		_y = KADR_BORDER_Y;
		break;
	case HALF:
		_width =  KADR_WORK_AREA_WIDTH/2;
		_height = KADR_WORK_AREA_HEIGHT + KADR_BORDER_Y;
		_x = KADR_BORDER_X + _id * _width / 2;
		_y = KADR_BORDER_Y;
		break;
	case QUATER:
		_width = KADR_WORK_AREA_WIDTH / 4;
		_height = KADR_WORK_AREA_HEIGHT + KADR_BORDER_Y;
		_x = KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4);
		_y = KADR_BORDER_Y;
		break;
	case EIGHTH:
		_width = KADR_WORK_AREA_WIDTH / 4;
		_height = (KADR_WORK_AREA_HEIGHT + KADR_BORDER_Y) / 2;
		_x = KADR_BORDER_X + (_id % 4) * (KADR_WORK_AREA_WIDTH / 4);
		_y = KADR_BORDER_Y + (_id / 4) * _height;
		break;
	default:
		break;
	}
}

void CKadr::InitInteractiveObj()
{
	interactiveObj[0].x = _x + _width / 2;
	interactiveObj[0].y = _y + _height / 2;
	interactiveObj[1].x = interactiveObj[0].x - 30;
	interactiveObj[1].y = interactiveObj[0].y + 30;
	interactiveObj[2].x = interactiveObj[0].x + 30;
	interactiveObj[2].y = interactiveObj[0].y + 30;
	interactiveObj[3] = interactiveObj[0];
}

void CKadr::DrawBorders(HDC hdc)
{
	// upper left cofner
	ptRect[0].x = _x;
	ptRect[0].y = _y;
	// upper right corner
	ptRect[1].x = _x + _width;
	ptRect[1].y = ptRect[0].y;
	// lower right corner
	ptRect[2].x = ptRect[1].x;
	ptRect[2].y = _y + _height - CAPTION_CORRECTION;
	// lower left corner
	ptRect[3].x = ptRect[0].x;
	ptRect[3].y = ptRect[2].y;
	// upper left corner, we are closing the rectangle
	ptRect[4] = ptRect[0];

	Polyline(hdc, ptRect, 5);
}

void CKadr::DrawBackground()
{
	extern CDrawEngine drawEngine;
	hOld = (HBRUSH)SelectObject(drawEngine.getBackgroundHDC(), CDrawKit::WhiteBrush);
	Rectangle(drawEngine.getBackgroundHDC(), _x, _y, _x + _width, _y + _height - CAPTION_CORRECTION);
	SelectObject(drawEngine.getBackgroundHDC(), hOld);
	
	hOld = SelectObject(drawEngine.getBackgroundHDC(), CDrawKit::BlackPen2);
	DrawBorders(drawEngine.getBackgroundHDC());
	SelectObject(drawEngine.getBackgroundHDC(), hOld);
}

void CKadr::Draw(HDC hdc)
{
	hOld = SelectObject(hdc, CDrawKit::BlackPen2);

	DrawInteractiveObj(hdc);

	SelectObject(hdc, hOld);
}

void CKadr::DrawInteractiveObj(HDC hdc)
{
	Polyline(hdc, interactiveObj, 4);
}

void CKadr::Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord)
{
	extern CKadrHandler kadrHandler;
	if (PointIsMine(secondTouchCoord))
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize < QUATER) //TODO: мб это стоит переделать лаконичнее
			kadrHandler.DivideKadr(_id, _kadrSize);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && this->_kadrSize == QUATER)
			kadrHandler.DivideKadr(_id, _kadrSize);
	}
	else
	{
		if (abs(firstTouchCoord.y - secondTouchCoord.y) < DEAD_ZONE && this->_kadrSize <= QUATER)
			if (firstTouchCoord.x < secondTouchCoord.x)
				kadrHandler.MergeKadr(_id, _kadrSize, RIGHT);
			else
				kadrHandler.MergeKadr(_id, _kadrSize, LEFT);
		if (abs(firstTouchCoord.x - secondTouchCoord.x) < DEAD_ZONE && this->_kadrSize == EIGHTH)
			kadrHandler.MergeKadr(_id, _kadrSize, RIGHT); //тут направление не важно на самом деле
	}
}

void CKadr::ResetInteractiveObject()
{
	_rotationAngle = 0;
	_scalingFactor = 1;
	InitInteractiveObj();
}

void CKadr::Move(const POINT firstTouchCoord, const LONG ldx, const LONG ldy)
{
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		if ((interactiveObj[i].x + ldx) > (LONG)(_x + _width) ||
			(interactiveObj[i].x + ldx) < (LONG)_x ||
			(interactiveObj[i].y + ldy) > (LONG)(_y + _height - CAPTION_CORRECTION)||
			(interactiveObj[i].y + ldy) < (LONG)_y)
			return;
	}
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		interactiveObj[i].x += ldx;
		interactiveObj[i].y += ldy;
	}
}
void CKadr::Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy) 
{
	POINT tmpPoint[INTERACTIVE_OBJ_LENGTH];
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		tmpPoint[i].x = ROUND_DOUBLE_TO_LONG(iZx * (1.0 - dZoomFactor) + interactiveObj[i].x * dZoomFactor);
		tmpPoint[i].y = ROUND_DOUBLE_TO_LONG(iZy * (1.0 - dZoomFactor) + interactiveObj[i].y * dZoomFactor);
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
void CKadr::Rotate(const double dAngle, const LONG iOx, const LONG iOy)
{
	double dCos = cos(dAngle);
	double dSin = sin(dAngle);

	POINT tmpPoint[INTERACTIVE_OBJ_LENGTH];
	for (int i = 0; i < INTERACTIVE_OBJ_LENGTH; i++)
	{
		LONG lDX = interactiveObj[i].x - iOx;
		LONG lDY = interactiveObj[i].y - iOy;
		tmpPoint[i].x = iOx + ROUND_DOUBLE_TO_LONG(lDX * dCos + lDY * dSin);
		tmpPoint[i].y = iOy + ROUND_DOUBLE_TO_LONG(lDY * dCos - lDX * dSin);
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

bool CKadr::PointIsMine(const POINT touchCoord)
{
	bool PointIsMine = false;
	
	if (touchCoord.x >= (LONG)_x &&
		touchCoord.x <= ((LONG)_x + (LONG)_width) &&
		touchCoord.y >= (LONG)_y &&
		touchCoord.y <= ((LONG)_y + (LONG)_height))
		PointIsMine = true;

	return PointIsMine;
}