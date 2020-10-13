/*
*	Родительский класс для всех кадров используемых в приложении. Содержит интерактивный объект
*	для отработки жестов (в будущем необходимо заменить на меню выбора кадра) и методы взаимодействия
*	с ним. Дочерние классы должны переопределить объект, заменяя их на объекты символизирующие
*	индикацию приборов и другие объекты кадра.
*/
#pragma once

#include "object/DrawingObject.h"

#define INTERACTIVE_OBJ_LENGTH 4

enum KADR_SIZE
{
	FULL,
	HALF,
	QUATER,
	EIGHTH,
};

enum SWIPE_DIRECTION
{
	LEFT,
	RIGHT,
};

class CKadr : public CDrawingObject
{
public:
	CKadr(UINT id, KADR_SIZE kadrSize);
	~CKadr() {};

	virtual void Draw(HDC hdc);
	virtual void DrawBackground();
	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CKadr* ChangePos(UINT newPos);

	virtual void Move(const POINT firstTouchCoord, const POINT delta);
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter);
	virtual void Rotate(const double dAngle, const POINT rotateCenter);
	virtual void Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord);
	virtual void Reset();
	virtual void ChangeSOIStatus();
	virtual bool GetBlockStatus() { return _blocked; };
	virtual void SetBlock(bool blockStatus) { _blocked = blockStatus; };

protected:
	UINT _id;										//(0-7)
	bool _isSOI;
	bool _blocked;
	KADR_SIZE _kadrSize;
	double  _scalingFactor;
	double  _rotationAngle;

	void PlaceKadr();

private:
	UINT ID;
	POINT interactiveObj[INTERACTIVE_OBJ_LENGTH];
	void InitInteractiveObj();
	void DrawInteractiveObj(HDC hdc);
	void ResetInteractiveObject();
};