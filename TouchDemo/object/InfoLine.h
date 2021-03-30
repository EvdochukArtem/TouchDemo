/*
*	 ласс преставл€ющий информационную строку
*/
#pragma once
#include "DrawingObject.h"

class CInfoLine : public CDrawingObject
{
public:
	CInfoLine();
	~CInfoLine() {};

	void Draw(HDC& hdc);
	void DrawBackground();

private:
	void Place();
	void DrawNavInfo(HDC& hdc);
	void DrawSystemInfo(HDC& hdc);
	void DrawSVSInfo(HDC& hdc);
	void DrawAdviceZone1(HDC& hdc);
	void DrawAdviceZone2(HDC& hdc);
};

