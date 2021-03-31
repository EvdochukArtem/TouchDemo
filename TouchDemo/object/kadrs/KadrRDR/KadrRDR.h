#pragma once
#include "../BlankKadr.h"

class CKadrRDR : public CBlankKadr
{
public:
	CKadrRDR(UINT id, KADR_SIZE kadrSize);
	~CKadrRDR() {};
	//Пока для демонстрации работы с интерактивным объектом кадр отыгрывает роль BlankKadr
	/*
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();

	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CAbstractKadr* ChangePos(UINT newPos);
	virtual void Move(const POINT firstTouchCoord, const POINT delta) {};
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter) {};
	virtual void DoRotate(const double dAngle, const POINT rotateCenter) {};
	virtual void Reset() {};
	virtual void LeftClickHandle(POINT pt) {};
	virtual void ProcessKeyboard(UINT key) {};
	virtual void ProcessCommand(KADR_COMMANDS cmd) {};*/
};