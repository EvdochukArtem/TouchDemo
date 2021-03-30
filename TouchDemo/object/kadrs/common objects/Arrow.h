#pragma once

class CArrow
{
public:
	CArrow(POINT X0Y0, POINT* XY, int numOfPts);
	~CArrow();
	void Draw(HDC& hdc, double angle/*, POINT &X0Y0, int h, POINT &XY, int numOfPts, float angle*/);	//Стрелка по окружности
private:
	POINT center;
	std::vector<POINT> arrowPts;
};

