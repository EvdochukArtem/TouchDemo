#include "stdafx.h"
#include "ScaleCircle.h"
#include "util/Util.h"
#include "../KadrMAP.h"

CScaleCircle::CScaleCircle(CKadrMAP* parent) : CDrawingObject(PRIOR_SCALE)
{
	kadrMAP = parent;
	Place();
}

CScaleCircle::~CScaleCircle()
{
	kadrMAP = nullptr;
}

void CScaleCircle::Place()
{
	RECT priborRect;
	GetRgnBox(kadrMAP->GetKadrRgn(), &priborRect);
	_x = priborRect.left;
	_y = priborRect.top;
	_cx = priborRect.right - priborRect.left;
	_cy = priborRect.bottom - priborRect.top;
}

void CScaleCircle::Draw(HDC& hdc)
{
	if (_hidden)
		return;
	SelectClipRgn(hdc, kadrMAP->GetKadrRgn());

	POINT center {_x + _cx / 2, _y + _cy * 2 / 3};

	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.WhitePen);
	oldBrush = (HBRUSH)SelectObject(hdc, DRAW_KIT.WhiteBrush);
	oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial12);
	oldTextAlign = SetTextAlign(hdc, TA_BOTTOM|TA_CENTER);
	oldColor = SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	oldBkColor = SetBkColor(hdc, DRAW_KIT.GetBlackColor());

	MoveToEx(hdc, center.x, _y, NULL);
	LineTo(hdc, center.x, _y + _cy);
	MoveToEx(hdc, _x, center.y, NULL);
	LineTo(hdc, _x + _cx, center.y);

	int i = 1;
	int a = CIRCLE_STEP;
	//TODO: ѕеределать условие. ѕри большом удалении от центра нужно рисовать больше кругов
	while (center.y - i * CIRCLE_STEP >= _y ||
		   center.x - i * CIRCLE_STEP >= _x ||
		   center.y + i * CIRCLE_STEP <= _y + _cy ||
		   center.x + i * CIRCLE_STEP <= _x + _cx)
	{
		Arc(hdc, center.x - i * CIRCLE_STEP, center.y - i * CIRCLE_STEP,
				 center.x + i * CIRCLE_STEP, center.y + i * CIRCLE_STEP, 
				 0, 0, 0, 0);
		if (i % 2 == 1)
		{
			_stprintf_s(buf, _T("%1.0f"), i * CIRCLE_STEP * (kadrMAP->GetSettings().scale / 1000));
			POINT scalePt = {0, - i * CIRCLE_STEP - TO_PIXEL(5)};
			scalePt = Rotate(scalePt, M_PI / 8, center.x, center.y);
			TextOut(hdc, scalePt.x, scalePt.y, buf, (int)_tcslen(buf));
			scalePt.x = 0;
			scalePt.y = - i * CIRCLE_STEP - TO_PIXEL(27);
			scalePt = Rotate(scalePt, M_PI * 9 / 8 , center.x, center.y);
			TextOut(hdc, scalePt.x, scalePt.y, buf, (int)_tcslen(buf));
		}
		i++;
	}

	_stprintf_s(buf, _T("ZOOM: x%d"),  9 - kadrMAP->GetSettings().scaleIndex);
	TextOut(hdc, _x + _cx - TO_PIXEL(80), _y + _cy - TO_PIXEL(30), buf, (int)_tcslen(buf));

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldFont);
	SetTextAlign(hdc, oldTextAlign);
	SetTextColor(hdc, oldColor);
	SetBkMode(hdc, OPAQUE);
	SetBkColor(hdc, oldBkColor);

	SelectClipRgn(hdc, nullptr);
}

void CScaleCircle::DrawBackground()
{
	if (_hidden)
		return;

	SelectClipRgn(DRAW_ENGINE.getBackgroundHDC(), kadrMAP->GetKadrRgn());
	
	SelectClipRgn(DRAW_ENGINE.getBackgroundHDC(), nullptr);
}