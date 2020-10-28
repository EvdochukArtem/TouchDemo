#pragma once
#include "AbstractButton.h"

class CMenuButton : public CAbstractButton
{
public:
	CMenuButton(UINT x, UINT y, UINT cx, UINT cy, LPCTSTR caption, void(CALLBACK* handler)(BUTTON_EVENT, CMenuButton*));
	~CMenuButton() {};
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();
	void SwitchSOI(bool soi);
	void Activate();
	void Disactivate();
	bool getStatus() { return isActive; };
	CMenuButton* ChangePos(UINT x, UINT y);
private:
	bool isActive;
	bool isSOI;
	void(CALLBACK* _handler)(BUTTON_EVENT, CMenuButton*);

	friend class CMenuButtonHandler;
};