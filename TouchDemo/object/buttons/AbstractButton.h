#pragma once
#include "../DrawingObject.h"

class CAbstractButton : public CDrawingObject
{
public:
	CAbstractButton(UINT x, UINT y, UINT cx, UINT cy, LPCWSTR caption);
	~CAbstractButton() {};
	virtual void Draw(HDC hdc) = 0;
	virtual void DrawBackground() = 0;
	virtual void LeftClickHandle() {};
	virtual void RightClickHandle() {};
protected:
	TCHAR _caption [10];
};