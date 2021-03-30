#include "stdafx.h"
#include "InfoLine.h"
#include "../util/Util.h"
#include "MechanicMenu.h"

#define BORDER TO_PIXEL(0)

CInfoLine::CInfoLine() : CDrawingObject(PRIOR_MAX)
{
	Place();
}

void CInfoLine::Place()
{
	_x = X0_PX + BORDER;
	_y = Y0_PX + MECHANIC_MENU_HI_HEIGHTPX;
	_cx = WIDTHPX - BORDER;
	_cy = INFOLINE_HEIGHTPX;
}

void CInfoLine::Draw(HDC& hdc)
{
	oldTextAlign = SetTextAlign(hdc, TA_BASELINE | TA_LEFT);
	oldColor = (COLORREF)SetTextColor(hdc, DRAW_KIT.GetWhiteColor());
	SetBkMode(hdc, TRANSPARENT);
	DrawNavInfo(hdc);
	if (false/*≈ÒÚ¸ ÒÓÓ·˘ÂÌËˇ ÓÚ ”—“–Œ…—“¬¿ œ–Œ¬≈– » Œÿ»¡Œ */)
		DrawSVSInfo(hdc);
	else
		DrawSystemInfo(hdc);
	DrawAdviceZone1(hdc);
	DrawAdviceZone2(hdc);

	SetTextAlign(hdc, oldTextAlign);
	SetTextColor(hdc, oldColor);
	SetBkMode(hdc, OPAQUE);
}

void CInfoLine::DrawBackground()
{
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);

	SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2	);

	MoveToEx(DRAW_ENGINE.getBackgroundHDC(), _x, _y + _cy, NULL);
	LineTo(DRAW_ENGINE.getBackgroundHDC(), _x + _cx, _y + _cy);
	
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CInfoLine::DrawNavInfo(HDC& hdc)
{
	_tcscpy_s(buf, _T("NAV INFO | NAV INFO | NAV INFO | NAV INFO"));
	TextOut(hdc, _x + TO_PIXEL(25), _y + _cy / 2 + TO_PIXEL(7), buf, (int)_tcslen(buf));
}

void CInfoLine::DrawSystemInfo(HDC& hdc)
{
	_tcscpy_s(buf, _T("SYS INFO | SYS INFO | SYS INFO | SYS INFO"));
	TextOut(hdc, _x + TO_PIXEL(25) + _cx / 4, _y + _cy / 2 + TO_PIXEL(7), buf, (int)_tcslen(buf));
}

void CInfoLine::DrawSVSInfo(HDC& hdc)
{
	_tcscpy_s(buf, _T("KARAT INFO | KARAT INFO | KARAT INFO | KARAT INFO"));
	TextOut(hdc, _x + TO_PIXEL(25) + _cx / 4, _y + _cy / 2 + TO_PIXEL(7), buf, (int)_tcslen(buf));
}

void CInfoLine::DrawAdviceZone1(HDC& hdc)
{
	_tcscpy_s(buf, _T("ADVICE 1 | ADVICE 1 | ADVICE 1 | ADVICE 1"));
	TextOut(hdc, _x + TO_PIXEL(25) + 2 * _cx / 4, _y + _cy / 2 + TO_PIXEL(7), buf, (int)_tcslen(buf));
}

void CInfoLine::DrawAdviceZone2(HDC& hdc)
{
	_tcscpy_s(buf, _T("ADVICE 2 | ADVICE 2 | ADVICE 2 | ADVICE 2"));
	TextOut(hdc, _x + TO_PIXEL(25) + 3 * _cx / 4, _y + _cy / 2 + TO_PIXEL(7), buf, (int)_tcslen(buf));
}