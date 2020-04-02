#include "Kadr.h"
#include "math.h"

#define CAPTION_CORRECTION 24;

CKadr::CKadr(KADR_SIZE kadrType)
{
	switch (kadrType)
	{
	case FULL_SC:
		_cx = 20;
		_cy = 20;
		_width = GetSystemMetrics(SM_CXSCREEN) - 40;
		_height = GetSystemMetrics(SM_CYSCREEN) - 40;
		_rotationAngle = 0;
		_scalingFactor = 1;
		break;
	}
}

void CKadr::Paint(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	HGDIOBJ hPenOld = SelectObject(hdc, hPen);

	POINT ptRect[5];
	// upper left cofner
	ptRect[0].x = _cx;
	ptRect[0].y = _cy;
	// upper right corner
	ptRect[1].x = _cx + _width;
	ptRect[1].y = ptRect[0].y;
	// lower right corner
	ptRect[2].x = ptRect[1].x;
	ptRect[2].y = _cy + _height - CAPTION_CORRECTION;
	// lower left corner
	ptRect[3].x = ptRect[0].x;
	ptRect[3].y = ptRect[2].y;
	// upper left corner, we are closing the rectangle
	ptRect[4] = ptRect[0];

	Polyline(hdc, ptRect, 5);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void CKadr::Move(LONG ldx, LONG ldy) {};
void CKadr::Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy) {};
void CKadr::Rotate(const double dAngle, const LONG iOx, const LONG iOy) {};