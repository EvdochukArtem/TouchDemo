#include "stdafx.h"
#include "object/auxilary/Arrow.h"
#include "util/Util.h"

CArrow::CArrow(POINT X0Y0, POINT* XY, int numOfPts)
{
	center = X0Y0;
	for (int i = 0; i < numOfPts; i++)
		arrowPts.push_back(XY[i]);
}

CArrow::~CArrow()
{}

void CArrow::Draw(HDC& hdc, float angle)
{	
	std::vector<POINT> tmp(arrowPts.size());
	for (int i = 0; i < arrowPts.size(); i++)
		tmp[i] = CUtil::Rotate(arrowPts[i], angle, center.x, center.y);
	::Polygon(hdc, &tmp[0], tmp.size());
}