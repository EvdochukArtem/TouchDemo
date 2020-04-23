#pragma once

#include <windows.h>

class CDrawingObject
{
public:
	CDrawingObject() {};
	~CDrawingObject() {};

	virtual void Paint(HDC hdc) = 0;
	virtual void Move(LONG ldx, LONG ldy) = 0;
	virtual void Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy) = 0;
	virtual void Rotate(const double dAngle, const LONG iOx, const LONG iOy) = 0;
};