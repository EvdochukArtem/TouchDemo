/*
*	Класс для выбора дополнительного кадра.
*/
#pragma once
#include "../AbstractKadr.h"

const int AUX_KADRS_MAX_NUM = 4;

class CSimpleTButton;

class CBlankAuxKadr : public CAbstractKadr
{
public:
	CBlankAuxKadr(UINT id, KADR_SIZE kadrSize);
	~CBlankAuxKadr();

	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void ChangeSize(KADR_SIZE newSize) {};
	virtual CAbstractKadr* ChangePos(UINT newPos) { return this; };

	virtual void Move(const POINT firstTouchCoord, const POINT delta) {};
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter) {};
	virtual void DoRotate(const double dAngle, const POINT rotateCenter) {};
	virtual void Reset() {};

	virtual void LeftClickHandle(POINT pt);
	virtual void ProcessKeyboard(UINT key) {};
	void ProcessCommand(KADR_COMMANDS cmd) {};

private:

	void Hide(bool hidden);

	CSimpleTButton* btn [AUX_KADRS_MAX_NUM];
	void BtnInit();
};