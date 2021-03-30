#pragma once
#include "../AbstractButton.h"

class CSwitchButton : public CAbstractButton
{
public:
	CSwitchButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSwitchButton*));
	~CSwitchButton() {};
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CSwitchButton*);
	bool enabled;

	friend class CSwitchButtonHandler;
};