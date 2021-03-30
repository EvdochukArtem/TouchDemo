#pragma once
#include "../../DrawingObject.h"

class CArrow;

class CEngineSys : public CDrawingObject
{
public:
	CEngineSys(int x, int y, int diametr, bool left);
	~CEngineSys();

	void DrawBackground();
	void Draw(HDC& hdc);
	void Place() {};

private:
	double* rud;
	float* temper;

	bool _left;
	bool IsABOn(bool isLeft);

	CArrow* strelka;
};

