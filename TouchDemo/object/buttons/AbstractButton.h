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
	virtual void LeftClickHandle() = 0;
	virtual void RightClickHandle() = 0;
	CAbstractButton* ChangePos(int x, int y);
	virtual void Dispose() {};
protected:
	TCHAR _caption [10];
};