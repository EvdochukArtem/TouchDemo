#pragma once
#include "../AbstractButton.h"

class CTabButton : public CAbstractButton
{
public:
	CTabButton(int x, int y, int cx, int cy, LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CTabButton*));
	~CTabButton() {};
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();
	void SwitchSOI(bool soi);
	void Activate();
	void Disactivate();

private:
	bool isActive;
	bool isSOI;
	void(CALLBACK* _handler)(MOUSE_EVNT, CTabButton*);

	friend class CTabButtonHandler;
};