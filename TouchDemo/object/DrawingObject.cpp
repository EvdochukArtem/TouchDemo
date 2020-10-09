#include "StdAfx.h"
#include "object/DrawingObject.h"
#include "util/Util.h"

CDrawingObject::CDrawingObject(DRAWOBJ_PRIOR prior)
{
	_prior = prior;
	RegisterDrawingObject();
}

CDrawingObject::~CDrawingObject()
{
	DeleteDrawingObject();
}

void CDrawingObject::RegisterDrawingObject()
{
	DRAW_ENGINE.AddDrawingObject(this);
};

void CDrawingObject::DeleteDrawingObject()
{
	DRAW_ENGINE.DeleteDrawingObject(this);
};

void CDrawingObject::DrawBorders(HDC hdc)
{
	POINT border[5];
	// upper left cofner
	border[0].x = _x;
	border[0].y = _y;
	// upper right corner
	border[1].x = _x + _cx;
	border[1].y = border[0].y;
	// lower right corner
	border[2].x = border[1].x;
	border[2].y = _y + _cy;
	// lower left corner
	border[3].x = border[0].x;
	border[3].y = border[2].y;
	// upper left corner, we are closing the rectangle
	border[4] = border[0];

	Polyline(hdc, border, 5);
}

bool CDrawingObject::PointIsMine(const POINT touchCoord)
{
	bool PointIsMine = false;
	
	if (touchCoord.x >= (LONG)_x &&
		touchCoord.x <= ((LONG)_x + (LONG)_cx) &&
		touchCoord.y >= (LONG)_y &&
		touchCoord.y <= ((LONG)_y + (LONG)_cy))
		PointIsMine = true;

	return PointIsMine;
}