#include "stdafx.h"
#include "EngineSys.h"
#include "../../../util/Util.h"

const int MAX_TEMP = 900;

CEngineSys::CEngineSys(int x, int y, int cx, int cy, bool left) : CDrawingObject(MID)
{
	_x = x;
	_y = y;
	_cx = cx;
	_cy = cy;
	_left = left;

	if (left)
	{
		rud = nullptr;//&SomeStruct.leftRPM;
		temper = nullptr;//&SomeStruct.TempLeft;
	} else {
		rud = nullptr;//&SomeStruct.rightRPM;
		temper = nullptr;//&SomeStruct.TempRight;
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
	float phi = *rud * M_PI / 50;

	strelka->Draw(hdc, phi);

	//Отрисовываем цифровое значение оборотов
	_stprintf_s(buf, _T("%d"), (int)*rud);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 - TO_PIXEL(10), buf, _tcslen(buf));

	//Отрисовываем цифровое температуры
	SetTextAlign(hdc, TA_TOP|TA_CENTER);
	if (MAX_TEMP < (int)*temper)
	{
		SetTextColor(hdc, DRAW_KIT.GetRedColor());
		phi = MAX_TEMP * M_PI / 500;
	}
	else
	{
		SetTextColor(hdc, DRAW_KIT.GetYellowColor());
		phi = *temper * M_PI / 500;
	}
	_stprintf_s(buf, _T("%d"), (int)*temper);
	TextOut(hdc, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(5), buf, _tcslen(buf));

	//Отрисовываем признак форсажа
	bool ab = true;//(_left) ? SomeStruct.leftAB : SomeStruct.rightAB;
	if (ab)
	{
		SetTextAlign(hdc, TA_LEFT|TA_BASELINE);
		SetTextColor(hdc, DRAW_KIT.GetGreenColor());
		TextOut(hdc, _x + _cx / 2 + TO_PIXEL(10), _y + _cy / 2 + TO_PIXEL(10), _T("AB"), 2);
	}

	//Рисуем температуру
	SelectObject(hdc, DRAW_KIT.YellowPen3);
	POINT temperPt;
	temperPt = CUtil::Rotate(0.0f, -_cy / 2.0f, phi, 0, 0);
	Arc(hdc, _x, _y, _x + _cx, _y + _cy, _x + _cx / 2 + temperPt.x, _y + _cy / 2 + temperPt.y, _x + _cx / 2, _y);

	if (MAX_TEMP < (int)*temper)
	{
		SelectObject(hdc, DRAW_KIT.RedPen3);
		POINT tmp;
		tmp = CUtil::Rotate(0.0f, -_cy / 2.0f, *temper * M_PI / 500.0f, 0, 0);
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
	HPEN OldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	HBRUSH OldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	HFONT OldFont = (HFONT)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.Arial12);
	COLORREF OldColor = (COLORREF)SetTextColor(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GetWhiteColor());
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
			tmpPt = CUtil::Rotate(point[0], i * M_PI/50, _x + _cx / 2, _y + _cy / 2);
			MoveToEx(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y, NULL);
			tmpPt = CUtil::Rotate(point[1], i*M_PI/50, _x+_cx/2, _y+_cy/2);
			LineTo(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y);
		}
		else
		{
			//Рисуем короткие линии разметки
			tmpPt = CUtil::Rotate(point[3], i*M_PI/50, _x+_cx/2, _y+_cy/2);
			MoveToEx(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y, NULL);
			tmpPt = CUtil::Rotate(point[4], i*M_PI/50, _x+_cx/2, _y+_cy/2);
			LineTo(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y);
		}
	}
	SetTextAlign(DRAW_ENGINE.getBackgroundHDC(), TA_BASELINE|TA_CENTER);
	for (int i = 0; i < 100; i+=10)
	{
		//Оцифровываем линии разметки
		tmpPt = CUtil::Rotate(0, -_cy / 2 + TO_PIXEL(25), i * M_PI/50, _x + _cx / 2, _y + _cy / 2 + TO_PIXEL(10));
		_stprintf_s(buf, _T("%d"), i/10);
		TextOut(DRAW_ENGINE.getBackgroundHDC(), tmpPt.x, tmpPt.y, buf, _tcslen(buf));
	}

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), OldPen);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), OldFont);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), OldBrush);
	SetTextColor(DRAW_ENGINE.getBackgroundHDC(), OldColor);
	SetBkMode(DRAW_ENGINE.getBackgroundHDC(), OPAQUE);
}