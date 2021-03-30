#pragma once
#include "../../../DrawingObject.h"

class CKadrMAP;

const int TACT_SCALE_CIRCLES = 5; //���-�� ������ �� �����
#define CIRCLE_STEP (KADR_WORK_AREA_WIDTH / 4/*DISPLAY_COLS*/ / 6/*NUM_OF_CIRCLES * 2*/ - TO_PIXEL(10)) //��������� ����� ������� �� �����

class CScaleCircle : public CDrawingObject
{
public:
	CScaleCircle(CKadrMAP* parent);
	~CScaleCircle();

	void Draw(HDC& hdc);
	void DrawBackground();
	void Place();

private:
	CKadrMAP* kadrMAP;
};

