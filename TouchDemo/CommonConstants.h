/*
*	Что бы избежать перекрестного включения заголовков приходится выносить константы сюда
*/

#pragma once
#include <windows.h>

class Display 
{
public:
	static int GetWidthpx() { return widthpx; };
	static int GetHeightpx() { return heightpx; };
	static int GetX0() { return x0_px; };
	static int GetY0() { return y0_px; };

private:
	friend BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

	static int widthpx;
	static int heightpx;
	static int x0_px;
	static int y0_px;
};

#define PI 3.141592653589f

#define WIDTHMM (600) //mm Длинна 
#define HEIGHTMM (300) //mm Высота 
#define INFOLINE_HEIGHTPX			 (TO_PIXEL(60))
#define MECHANIC_MENU_HI_HEIGHTPX	 (TO_PIXEL(45))
#define MECHANIC_MENU_LO_HEIGHTPX	 (TO_PIXEL(30))
#define WIDTHPX		(Display::GetWidthpx())		//px Длинна
#define HEIGHTPX	(Display::GetHeightpx())	//px Высота
#define X0_PX		(Display::GetX0())			//Начальные координаты
#define Y0_PX		(Display::GetY0())			//Начальные координаты

#define TO_PIXEL(a)			(int)((a)*HEIGHTPX/1080.0)
#define TO_MILLIMETER(a)	(int)(HEIGHTPX*(a)/HEIGHTMM)

#define KADR_BORDER_Y_HI			 (MECHANIC_MENU_HI_HEIGHTPX + INFOLINE_HEIGHTPX)
#define KADR_BORDER_Y_LO			 (MECHANIC_MENU_LO_HEIGHTPX)
#define KADR_BORDER_X				 (0)
#define KADR_WORK_AREA_WIDTH		 (WIDTHPX - 2 * KADR_BORDER_X)
#define KADR_WORK_AREA_HEIGHT		 (HEIGHTPX - KADR_BORDER_Y_HI - KADR_BORDER_Y_LO)
