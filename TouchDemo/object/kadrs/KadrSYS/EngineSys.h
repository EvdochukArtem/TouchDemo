#pragma once
#include "../../DrawingObject.h"
#include "../../auxilary/Arrow.h"

class CEngineSys : public CDrawingObject
{
public:
	CEngineSys(int x, int y, int cx, int cy, bool left);
	~CEngineSys();

	void DrawBackground();
	void Draw(HDC& hdc);
	void Dispose() {};

private:
	double* rud;
	float* temper;

	bool _left;

	CArrow* strelka;
};

