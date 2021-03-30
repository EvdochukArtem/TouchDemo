#include "stdafx.h"
#include "TouchSymbol.h"
#include "util/Util.h"

CTouchSymbol::CTouchSymbol() : CDrawingObject(PRIOR_SOI)
{
	drawZone = CreateRectRgn(X0_PX, Y0_PX, X0_PX + WIDTHPX, Y0_PX + HEIGHTPX);
	CalculateConstants();
}

CTouchSymbol::~CTouchSymbol()
{
	if (drawZone != nullptr)
		DeleteObject(drawZone);
}

void CTouchSymbol::Draw(HDC& hdc)
{
	SelectClipRgn(hdc, drawZone);
	oldPen = (HPEN)SelectObject(hdc, DRAW_KIT.YellowPen2);

	bool a = GESTURE_EMULATOR.GetLButtonStatus();
	bool b = GESTURE_EMULATOR.GetLClickSteady();

	if (a && b)
	{
		int symbSize = 320;
		MoveToEx(hdc, touchCoord.x - TO_PIXEL(symbSize / 2), touchCoord.y, NULL);
		LineTo(hdc, touchCoord.x + TO_PIXEL(symbSize / 2), touchCoord.y);
		MoveToEx(hdc, touchCoord.x, touchCoord.y - TO_PIXEL(symbSize / 2), NULL);
		LineTo(hdc, touchCoord.x, touchCoord.y + TO_PIXEL(symbSize / 2));
		Arc(hdc, touchCoord.x - TO_PIXEL(arcPoints[0].x), touchCoord.y - TO_PIXEL(arcPoints[0].y),
				 touchCoord.x + TO_PIXEL(arcPoints[0].x), touchCoord.y + TO_PIXEL(arcPoints[0].y),
				 TO_PIXEL(arcPoints[1].x) + touchCoord.x, TO_PIXEL(arcPoints[1].y) + touchCoord.y,
				 TO_PIXEL(arcPoints[2].x )+ touchCoord.x, TO_PIXEL(arcPoints[2].y) + touchCoord.y);
		Arc(hdc, touchCoord.x - TO_PIXEL(arcPoints[0].x), touchCoord.y - TO_PIXEL(arcPoints[0].y),
				 touchCoord.x + TO_PIXEL(arcPoints[0].x), touchCoord.y + TO_PIXEL(arcPoints[0].y),
				 TO_PIXEL(arcPoints[3].x) + touchCoord.x, TO_PIXEL(arcPoints[3].y) + touchCoord.y,
				 TO_PIXEL(arcPoints[4].x )+ touchCoord.x, TO_PIXEL(arcPoints[4].y) + touchCoord.y);
		Arc(hdc, touchCoord.x - TO_PIXEL(arcPoints[0].x), touchCoord.y - TO_PIXEL(arcPoints[0].y),
				 touchCoord.x + TO_PIXEL(arcPoints[0].x), touchCoord.y + TO_PIXEL(arcPoints[0].y),
				 TO_PIXEL(arcPoints[5].x) + touchCoord.x, TO_PIXEL(arcPoints[5].y) + touchCoord.y,
				 TO_PIXEL(arcPoints[6].x )+ touchCoord.x, TO_PIXEL(arcPoints[6].y) + touchCoord.y);
		Arc(hdc, touchCoord.x - TO_PIXEL(arcPoints[0].x), touchCoord.y - TO_PIXEL(arcPoints[0].y),
				 touchCoord.x + TO_PIXEL(arcPoints[0].x), touchCoord.y + TO_PIXEL(arcPoints[0].y),
				 TO_PIXEL(arcPoints[7].x) + touchCoord.x, TO_PIXEL(arcPoints[7].y) + touchCoord.y,
				 TO_PIXEL(arcPoints[8].x )+ touchCoord.x, TO_PIXEL(arcPoints[8].y) + touchCoord.y);

		double fingerTouchKoef = (CLICK_TIME - GESTURE_EMULATOR.GetLButtonTimer()) / CLICK_TIME;
		fingerTouchKoef = (fingerTouchKoef > 0) ? fingerTouchKoef : 0;
		int sphinkterSize = TO_PIXEL(arcPoints[0].x) + int((TO_PIXEL(symbSize / 2) - TO_PIXEL(arcPoints[0].x)) * fingerTouchKoef);
		Arc(hdc, touchCoord.x - sphinkterSize, touchCoord.y - sphinkterSize,
				 touchCoord.x + sphinkterSize, touchCoord.y + sphinkterSize,
				 0, 0, 0, 0);
	}

	SelectObject(hdc, oldPen);
	SelectClipRgn(hdc, nullptr);
}

void CTouchSymbol::LeftClickHandle(POINT clickCoord)
{
	touchCoord = clickCoord;
}

void CTouchSymbol::CalculateConstants()
{
	int arcRadius = 110 / 2;
	arcPoints[0].x = arcRadius;
	arcPoints[0].y = arcRadius;

	arcPoints[1] = Rotate(arcRadius, 0, double(PI / 12.0), 0, 0);
	arcPoints[2] = Rotate(arcRadius, 0, double(23.0 * PI / 12.0), 0, 0);

	arcPoints[3] = Rotate(arcRadius, 0, double(7.0 * PI / 12.0), 0, 0);
	arcPoints[4] = Rotate(arcRadius, 0, double(5.0 * PI / 12.0), 0, 0);

	arcPoints[5] = Rotate(arcRadius, 0, double(13.0 * PI / 12.0), 0, 0);
	arcPoints[6] = Rotate(arcRadius, 0, double(11.0 * PI / 12.0), 0, 0);

	arcPoints[7] = Rotate(arcRadius, 0, double(19.0 * PI / 12.0), 0, 0);
	arcPoints[8] = Rotate(arcRadius, 0, double(17.0 * PI / 12.0), 0, 0);
}