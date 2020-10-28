#include "stdafx.h"
#include "AbstractButton.h"

CAbstractButton::CAbstractButton(UINT x, UINT y, UINT cx, UINT cy, LPCTSTR caption) : CDrawingObject(MAX)
{
	_x = x;
	_y = y;
	_cx = cx;
	_cy = cy;
	_tcscpy_s(_caption, caption);
}