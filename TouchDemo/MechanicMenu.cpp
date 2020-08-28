#include "MechanicMenu.h"
#include "DrawEngine.h"

#define KADR_BORDER_Y 25
#define KADR_BORDER_X 0
#define EKRAN_WIDTH (int)(WIDTHPX - 2 * KADR_BORDER_X)
#define EKRAN_HEIGHT (int)(HEIGHTPX)

CMechanicMenu::CMechanicMenu(UINT id, UINT kadrBorder)
{
	_id = id;
	_height = kadrBorder;
	_x = _id * EKRAN_WIDTH / 4;
	RegisterDrawingObject();
}

CMechanicMenu::~CMechanicMenu()
{
	DeleteDrawingObject();
}

void CMechanicMenu::DrawBackground()
{}

void CMechanicMenu::Draw(HDC hdc)
{
	oldPen = SelectObject(hdc, CDrawKit::BlackPen2);
	oldBrush = SelectObject(hdc, CDrawKit::LightGreyBrush);
	
	Rectangle(hdc, _x, 0, _x + EKRAN_WIDTH / 4, _height);
	Rectangle(hdc, _x, EKRAN_HEIGHT - _height, _x + EKRAN_WIDTH / 4, EKRAN_HEIGHT);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}