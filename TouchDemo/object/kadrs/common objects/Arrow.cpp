#include "stdafx.h"
#include "Arrow.h"
#include "util/Util.h"

CArrow::CArrow(POINT X0Y0, POINT* XY, int numOfPts)
{
	center = X0Y0;
	for (int i = 0; i < numOfPts; i++)
		arrowPts.push_back(XY[i]);
}

CArrow::~CArrow()
{}

void CArrow::Draw(HDC& hdc, double angle)
{	
	std::vector<POINT> tmp(arrowPts.size());
	for (int i = 0; i < (int)arrowPts.size(); i++)
		tmp[i] = Rotate(arrowPts[i], angle, center.x, center.y);
	::Polygon(hdc, &tmp[0], (int)tmp.size());
}