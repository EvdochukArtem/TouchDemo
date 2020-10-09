#pragma once
#include "object/buttons/AbstractButton.h"

class CMenuButton : public CAbstractButton
{
public:
	CMenuButton(UINT x, UINT y, UINT cx, UINT cy, LPCWSTR caption);
	~CMenuButton() {};
	virtual void Draw(HDC hdc);
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
};