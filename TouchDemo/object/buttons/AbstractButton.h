#pragma once
#include "../DrawingObject.h"

enum BUTTON_EVENT
{
	LM_DOWN,
	LM_UP,
	MW_DOWM,
	MW_UP,
};

class CAbstractButton : public CDrawingObject
{
public:
	CAbstractButton(int x, int y, int cx, int cy, LPCTSTR caption);
	~CAbstractButton() {};
	//virtual void Draw(HDC& hdc) = 0;
	//virtual void DrawBackground() = 0;
	virtual void LeftClickHandle() = 0;
	virtual void RightClickHandle() = 0;
protected:
	TCHAR _caption [10];
};