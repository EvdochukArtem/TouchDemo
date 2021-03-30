#include "stdafx.h"
#include "EngineSys.h"
#include "util/Util.h"
#include "../common objects/Arrow.h"

const int MAX_TEMP = 900;

CEngineSys::CEngineSys(int x, int y, int radius, bool left) : CDrawingObject(PRIOR_MID)
{
	_x = x;
	_y = y;
	_cx = radius;
	_cy = radius;
	_left = left;

	if (left)
	{
		rud = 0;
		temper = 0;
	} else {
		rud = 0;
		temper = 0;
	}
	POINT Strelka [5];
	Strelka[0].x	= _cx / 50;
	Strelka[0].y	= -(long)(_cy / 4);
	Strelka[1].x	= _cx / 30;
	Strelka[1].y	= -(long)(_cy / 3);
	Strelka[2].x	= 0;
	Strelka[2].y	= -(long)(_cy / 2);
	Strelka[3].x	= -(long)_cx / 30;
	Strelka[3].y	= -(long)(_cy / 3);
	Strelka[4].x	= -(long)_cx / 50;
	Strelka[4].y	= -(long)(_cy / 4);
	POINT center = {_x + _cx / 2, _y + _cy / 2};
	
	strelka = new CArrow(center, Strelka, 5);
}

CEngineSys::~CEngineSys()
{
	delete strelka;
}

void CEngineSys::Draw(HDC& hdc)
{
	if (_hidden)
		return;
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.GreyPen);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.WhiteBrush);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial12);
	oldTextAlign = SetTextAlign(hdc, TA_BOTTOM|TA_CENTER);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);

	double a = 50;
	float b = 500;
	rud = &a;
	temper = &b;

	//Рисуем стрелку
	double phi = *rud * PI / 50;

	strelka->Draw(hdc, phi);

	//Отрисовываем цифровое значение оборотов
	_stprintf_s(buf, _T("%d"), (int)*rud);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 - TO_PIXEL(10), buf, (int)_tcslen(buf));

	//Отрисовываем цифровое температуры
	SetTextAlign(hdc, TA_TOP|TA_CENTER);
	if (MAX_TEMP < (int)*temper)
	{
		SetTextColor(hdc, DRAW_KIT.GetRedColor());
		phi = MAX_TEMP * PI / 500;
	}
	else
	{
		SetTextColor(hdc, DRAW_KIT.GetYellowColor());
		phi = *temper * PI / 500;
	}
	_stprintf_s(buf, _T("%d"), (int)*temper);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), buf, (int)_tcslen(buf));

	//Отрисовываем признак форсажа
	bool ab = /*true;//*/IsABOn(_left);
	if (ab)
	{
		SetTextAlign(hdc, TA_LEFT|TA_BASELINE);
		SetTextColor(hdc, DRAW_KIT.GetGreenColor());
		TextOut(hdc, _x + _cx / 2 + TO_PIXEL(10), _y + _cy / 2 + TO_PIXEL(10), _T("AB"), 2);
	}

	//Рисуем температуру
	SelectObject(hdc, DRAW_KIT.YellowPen3);
	POINT temperPt;
	temperPt = Rotate(0, -_cy / 2, phi, 0, 0);
	Arc(hdc, _x, _y, _x + _cx, _y + _cy, _x + _cx / 2 + temperPt.x, _y + _cy / 2 + temperPt.y, _x + _cx / 2, _y);

	if (MAX_TEMP < (int)*temper)
	{
		SelectObject(hdc, DRAW_KIT.RedPen3);
		POINT tmp;
		tmp = Rotate(0, -_cy / 2, (*temper * PI) / 500.0f, 0, 0);
		Arc(hdc, _x - TO_PIXEL(2), _y - TO_PIXEL(2), _x + _cx + TO_PIXEL(1), _y + _cy + TO_PIXEL(1), 
			_x + _cx / 2 + tmp.x, _y + _cy / 2 + tmp.y, _x + _cx / 2 + temperPt.x, _y + _cy / 2 + temperPt.y);
		temperPt.x = tmp.x;
		temperPt.y = tmp.y;
	}
	Ellipse(hdc, _x + _cx / 2 + temperPt.x - TO_PIXEL(3), _y + _cy / 2 + temperPt.y - TO_PIXEL(3),
		    _x + _cx / 2 + temperPt.x + TO_PIXEL(2), _y + _cy / 2 + temperPt.y + TO_PIXEL(2));
	
	SetTextAlign(hdc, oldTextAlign);
	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldFont);
	SelectObject(hdc, oldBrush);
	SetBkMode(hdc, OPAQUE);
}

void CEngineSys::DrawBackground()
{
	if (_hidden)
		return;
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	oldFont = (HFONT)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.Arial12);
	oldColor = (COLORREF)SetTextColor(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GetWhiteColor());
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), TRANSPARENT);

	Ellipse(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhitePen2);
 	SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhiteBrush);
	Ellipse(DRAW_ENGINE.getBackgroundHDC(), _x + _cx / 2 - _cx / 40, _y + _cy / 2 - _cy / 40, _x + _cx / 2 + _cx / 40, _y + _cy / 2 + _cy / 40);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.WhitePen);

	//Рисуем циферблат
	POINT point[] = {{0, -_cy / 2 + TO_PIXEL(3)}, {0, (int)(-_cy / 2.3 + TO_PIXEL(3))}, {0, (long)(-_cy / 2.5 + TO_PIXEL(3))},
					{0, -_cy / 2 + TO_PIXEL(3)}, {0, (int)(-_cy / 2.1 + TO_PIXEL(3))}, {0, -_cy / 2}, {0, (int)(-_cy / 1.8)}};
	POINT tmpPt;
	for (int i = 0; i < 100; i++)
	{
		if ((i % 5) == 0)
		{
			//Рисуем длинные линии разметки
			tmpPt = Rotate(point[0], double(i * PI / 50), _x + _cx / 2, _y + _cy / 2);
			MoveToEx(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y, NULL);
			tmpPt = Rotate(point[1], double(i * PI / 50), _x+_cx/2, _y+_cy/2);
			LineTo(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y);
		}
		else
		{
			//Рисуем короткие линии разметки
			tmpPt = Rotate(point[3], double(i * PI / 50), _x+_cx/2, _y+_cy/2);
			MoveToEx(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y, NULL);
			tmpPt = Rotate(point[4], double(i * PI / 50), _x+_cx/2, _y+_cy/2);
			LineTo(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y);
		}
	}
	SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), TA_BASELINE|TA_CENTER);
	for (int i = 0; i < 100; i+=10)
	{
		//Оцифровываем линии разметки
		tmpPt = Rotate(0, -_cy / 2 + TO_PIXEL(25), double(i * PI/50), _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10));
		_stprintf_s(buf, _T("%d"), i/10);
		TextOut(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y, buf, (int)_tcslen(buf));
	}

	//Отрисовываем метку максимальных оборотов
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.RedPen2);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.RedBrush);

	POINT tpts[2];
	POINT pts[] = {{0, TO_PIXEL(-4) + _cy / 2}, {0, TO_PIXEL(-10) + _cy / 2}};
	tpts[0] = Rotate(pts[0], double(-PI / 20.0f + PI), _x + _cx / 2, _y + _cy / 2);
	tpts[1] = Rotate(pts[1], double(-PI / 20.0f + PI), _x + _cx / 2, _y + _cy / 2);

	MoveToEx(DRAW_ENGINE.getBackgroundHDC(), tpts[0].x, tpts[0].y, NULL);
	LineTo(DRAW_ENGINE.getBackgroundHDC(), tpts[1].x, tpts[1].y);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldFont);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SetTextColor(DRAW_ENGINE.getBackgroundHDC(), oldColor);
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), OPAQUE);
}

bool CEngineSys::IsABOn(bool isLeft)
{
	if (isLeft)
		return true;//данные из внешнего источника
	else
		return false;//данные из внешнего источника
}