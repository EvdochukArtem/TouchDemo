#pragma once
#include "../AbstractKadr.h"

class CKadrRDR : public CAbstractKadr
{
public:
	CKadrRDR(UINT id, KADR_SIZE kadrSize);
	~CKadrRDR() {};
	
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();

	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CAbstractKadr* ChangePos(UINT newPos);
	virtual void Move(const POINT firstTouchCoord, const POINT delta) {};
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter) {};
	virtual void Rotate(const double dAngle, const POINT rotateCenter) {};
	virtual void Reset() {};
	virtual void LeftClickHandle(POINT pt) {};
};