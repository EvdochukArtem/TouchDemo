#pragma once

#include "StdAfx.h"
#include "DrawingObject.h"

#define INTERACTIVE_OBJ_LENGTH 4

enum KADR_SIZE
{
	FULL,
	HALF,
	QUATER,
	EIGHTH,
};

enum MERGE_DIRECTION
{
	LEFT,
	RIGHT,
};

class CKadr : CDrawingObject
{
public: 
	CKadr(UINT id, KADR_SIZE kadrSize);
	~CKadr();
	   
	void Draw(HDC hdc);
	void DrawBackground();

	void ResetInteractiveObject();
	void Move(const POINT firstTouchCoord, const LONG ldx, const LONG ldy);
	void Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy);
	void Rotate(const double dAngle, const LONG iOx, const LONG iOy);
	void Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord);
	bool PointIsMine(const POINT touchCoord);

private:
	UINT _id;										//(0-7)
	KADR_SIZE _kadrSize;
	UINT _x;										//x координата верхнего левого угла
	UINT _y;										//y координата верхнего левого угла
	UINT _width;
	UINT _height;
	double  _scalingFactor;
	double  _rotationAngle;
	POINT ptRect[5];
	HGDIOBJ hOld;

	POINT interactiveObj[INTERACTIVE_OBJ_LENGTH];
	void CreateKadr();
	void DrawBorders(HDC hdc);
	void InitInteractiveObj();
	void DrawInteractiveObj(HDC hdc);
};