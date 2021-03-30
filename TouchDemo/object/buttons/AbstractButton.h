#pragma once
#include "../DrawingObject.h"

#define TBUTTON_SIDE_SIZE TO_MILLIMETER(22) //Длинна ребра сивола сенсорной кнопки

enum MOUSE_EVNT
{
	M_EVNT_LB_DOWN,
	M_EVNT_LB_UP,
	M_EVNT_WHEEL_DOWN,
	M_EVNT_WHEEL_UP,
};

class CAbstractButton : public CDrawingObject
{
public:
	CAbstractButton(int x, int y, int cx, int cy, LPCTSTR caption);
	virtual ~CAbstractButton() {};
	virtual void LeftClickHandle() = 0;
	virtual void MouseWheelHandle(double scrollFactor) {};
	virtual CAbstractButton* ChangePos(int x, int y);
	virtual void Place() {};
	LPCTSTR GetCaption() { return _caption; };
protected:
	TCHAR _caption [10];

	friend class CAbstractIndicatorButton;
};