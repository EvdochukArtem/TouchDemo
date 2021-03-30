#pragma once
#include "DrawingObject.h"

class CTouchSymbol : public CDrawingObject
{
public:
	CTouchSymbol();
	~CTouchSymbol();

	void Draw(HDC& hdc);
	void DrawBackground() {};
	void Place() {};
	
	void LeftClickHandle(POINT pt);
private:
	HRGN drawZone;

	POINT touchCoord;
	POINT arcPoints[9];

	void CalculateConstants();
};

