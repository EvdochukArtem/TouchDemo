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
	virtual void RightClickHandle();
	void SwitchSOI();
	bool getSOIStatus() { return isSOI; };
private:
	bool isSOI;
};