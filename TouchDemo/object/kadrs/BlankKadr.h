/*
*	Класс-пример. Содержит интерактивный объект для отработки жестов и методы
*	для взаимодействия с ним.
*/
#pragma once
#include "AbstractKadr.h"

const int INTERACTIVE_OBJ_LENGTH = 4; //Кол-во точек интерактивного объекта

class CBlankKadr : public CAbstractKadr
{
public:
	CBlankKadr(UINT id, KADR_SIZE kadrSize);
	~CBlankKadr() {};

	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CAbstractKadr* ChangePos(UINT newPos);

	virtual void Move(const POINT firstTouchCoord, const POINT delta);
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter);
	virtual void DoRotate(const double dAngle, const POINT rotateCenter);
	virtual void Reset();

	virtual void LeftClickHandle(POINT pt) {};
	virtual void ProcessKeyboard(UINT key) {};
	void ProcessCommand(KADR_COMMANDS cmd) {};

protected:

	UINT ID; //Удалить потом вместе с интерактивным объектом
	POINT interactiveObj[INTERACTIVE_OBJ_LENGTH];
	void InitInteractiveObj();
	void DrawInteractiveObj(HDC& hdc);
	void ResetInteractiveObject();
};