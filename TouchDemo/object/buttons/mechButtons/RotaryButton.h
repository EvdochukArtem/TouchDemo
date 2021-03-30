#pragma once
#include "../AbstractButton.h"

class CParamButton;

class CRotaryButton : public CAbstractButton
{
public:
	CRotaryButton(int x, int y, int cx, int cy);
	~CRotaryButton() {};

	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();
	void MouseWheelHandle(double scrollFactor);
	
	void AttachParamButton(CParamButton* btn);
	void DeAttachParamButton();

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CRotaryButton*);
	bool enabled;

	CParamButton* paramBtn;

	friend class CRotaryButtonHandler;
};