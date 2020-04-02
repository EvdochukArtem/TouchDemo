#pragma once

#include "DrawingObject.h"
//#define DISPLAY_ROWS 2;
//#define DISPLAY_COLS 4;

enum KADR_SIZE
{
	FULL_SC,
	HALF_SC,
	QUATER_SC,
	EIGHTH_SC,
};

class CKadr// : CDrawingObject
{
public:
	CKadr(KADR_SIZE kadrType);
	~CKadr() { /*Count()--;*/ };
	   
	void Paint(HDC hdc);
	void Move(LONG ldx, LONG ldy);
	void Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy);
	void Rotate(const double dAngle, const LONG iOx, const LONG iOy);

private:
	//BOOL KadrInit(KADR_SIZE kadrType);

	UINT _cx;										//x координата верхнего левого угла
	UINT _cy;										//y координата верхнего левого угла
	UINT _width;
	UINT _height;
	double  _scalingFactor;
	double  _rotationAngle;
	KADR_SIZE kadrType;

	//static CKadr displayCells[DISPLAY_ROWS][DISPLAY_COLS];
	//UINT& Count() { static UINT c = 0; return c; }	//счетчик кадров
};