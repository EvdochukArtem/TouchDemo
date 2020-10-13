#include "stdafx.h"
#include "Frame.h"
#include "util/Util.h"

CFrame::CFrame(UINT id, UINT activeButton, KADR_SIZE frameSize) : CDrawingObject(ACTIVE)
{
	_id = id;
	_activeButton = activeButton;
	_isSOI = false;
	_blocked = false;
	_frameSize = frameSize;
	PlaceFrame();
}

void CFrame::PlaceFrame()
{
	switch (_frameSize)
	{
	case FULL:
		_cx = WIDTHPX;
		_cy = HEIGHTPX;
		_x = 0;
		_y = 0;
		break;
	case HALF:
		_cx = WIDTHPX / 2;
		_cy = HEIGHTPX;
		_x = _id * _cx / 2;
		_y = 0;
		break;
	case QUATER:
	case EIGHTH:
		_cx = WIDTHPX / 4;
		_cy = HEIGHTPX;
		_x = (_id % 4) * _cx;
		_y =0;
		break;
	default:
		break;
	}
}

void CFrame::DrawBackground()
{
	if (_blocked)
		return;
	if (_isSOI)
		oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.YellowPen3);
	else
		oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
	DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CFrame::ChangeSOIStatus()
{
	if (_isSOI)
		_prior = ACTIVE;
	else
		_prior = SOI;
	_isSOI = !_isSOI;
	DRAW_ENGINE.ResetDrawingObject(this);
}

void CFrame::ChangeSize(KADR_SIZE newSize)
{
	_frameSize = newSize;
	PlaceFrame();
}

CFrame* CFrame::ChangePos(UINT newPos)
{
	_id = newPos;
	PlaceFrame();
	return this;
}