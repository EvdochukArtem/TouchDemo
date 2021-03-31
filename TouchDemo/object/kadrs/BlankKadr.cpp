#include "StdAfx.h"
#include "BlankKadr.h"
#include "util/Util.h"

#define TIMER_ID (001)

// This macro is used to round double and cast it to LONG
#define ROUND_DOUBLE_TO_LONG(x) ((LONG)floor(0.5 + (x)))


CBlankKadr::CBlankKadr(UINT id, KADR_SIZE kadrSize) : CAbstractKadr(id, kadrSize)
{
	_kadrType = KADR_TYPE_AUX;
	ID = id;
	InitInteractiveObj();
}

void CBlankKadr::InitInteractiveObj()
{
	interactiveObj[0].x = _x + _cx / 2;
	interactiveObj[0].y = _y + _cy / 2;
	interactiveObj[1].x = interactiveObj[0].x - 30;
	interactiveObj[1].y = interactiveObj[0].y + 30;
	interactiveObj[2].x = interactiveObj[0].x + 30;
	interactiveObj[2].y = interactiveObj[0].y + 30;
	interactiveObj[3] = interactiveObj[0];
}

void CBlankKadr::DrawBackground()
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
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CBlankKadr::Draw(HDC& hdc)
{
	if (_blocked)
		return;
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreyPen2);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.LightGreyBrush);
	
	DrawInteractiveObj(hdc);
	
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
}

void CBlankKadr::ChangeSize(KADR_SIZE newSize)
{
	_kadrSize = newSize;
	Place();
	InitInteractiveObj();
}

CAbstractKadr* CBlankKadr::ChangePos(UINT newPos)
{
	_id = newPos;
	Place();
	InitInteractiveObj();
	return this;
}

void CBlankKadr::DrawInteractiveObj(HDC& hdc)
{
	_stprintf_s(buf, _T("%d"), ID + 1);
	Polygon(hdc, interactiveObj, 4);
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	TextOut(hdc, interactiveObj[0].x, interactiveObj[0].y + TO_PIXEL(35), buf, (int)_tcslen(buf));
	SetTextAlign(hdc, oldTextAlign);
}

void CBlankKadr::Reset()
{
	ResetInteractiveObject();
}

void CBlankKadr::ResetInteractiveObject()
{
	_rotationAngle = 0;
	_scalingFactor = 1;
	InitInteractiveObj();
}

void CBlankKadr::Move(const POINT firstTouchCoord, const POINT delta)
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

void CBlankKadr::Zoom(const double dZoomFactor, const POINT zoomCenter) 
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

void CBlankKadr::DoRotate(const double dAngle, const POINT rotateCenter)
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