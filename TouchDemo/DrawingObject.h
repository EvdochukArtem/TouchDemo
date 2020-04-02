#pragma once

#include <windows.h>

class CDrawingObject
{
public:
	CDrawingObject() {};
	~CDrawingObject() {};

	virtual void Paint(HDC hdc);
	virtual void Move(LONG ldx, LONG ldy);
	virtual void Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy);
	virtual void Rotate(const double dAngle, const LONG iOx, const LONG iOy);
};