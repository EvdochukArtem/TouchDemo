#include "stdafx.h"
#include "AbstractButton.h"

CAbstractButton::CAbstractButton(int x, int y, int cx, int cy, LPCTSTR caption) : CDrawingObject(PRIOR_BUTTONS)
{
	_x = x;
	_y = y;
	_cx = cx;
	_cy = cy;
	_tcscpy_s(_caption, caption);
}

CAbstractButton* CAbstractButton::ChangePos(int x, int y)
{
	_x = x;
	_y = y;
	return this;
}