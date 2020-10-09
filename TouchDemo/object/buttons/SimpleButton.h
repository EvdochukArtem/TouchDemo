#pragma once
#include "object/buttons/AbstractButton.h"

class CSimpleButton : public CAbstractButton
{
public:
	CSimpleButton(UINT x, UINT y, UINT cx, UINT cy, LPCWSTR caption);
	~CSimpleButton() {};
	virtual void Draw(HDC hdc);
	virtual void DrawBackground();
	virtual void LeftClickHandle();
	CSimpleButton* ChangePos(UINT x, UINT y);
};