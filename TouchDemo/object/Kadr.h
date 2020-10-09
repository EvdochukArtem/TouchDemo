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

protected:
	UINT _id;										//(0-7)
	bool isSOI;
	KADR_SIZE _kadrSize;
	double  _scalingFactor;
	double  _rotationAngle;

	void CreateKadr();

private:
	POINT interactiveObj[INTERACTIVE_OBJ_LENGTH];
	void InitInteractiveObj();
	void DrawInteractiveObj(HDC hdc);
	void ResetInteractiveObject();
};