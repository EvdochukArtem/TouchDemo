/*
*	Класс отвечает за создание, управление и доступ к базовым объектам программы.
*/
#pragma once
#include "object/Kadr.h"
#include "object/MechanicMenu.h"
#include "object/Frame.h"

#define DISPLAY_ROWS 2
#define DISPLAY_COLS 4

class CEkranHandler
{
public:
	CKadr* getDisplayCell(UINT row, UINT col) { return displayCells[row][col]; };
	CMechanicMenu* getMechanicMenu(UINT col) { return mechanicMenu[col]; };
	void DivideKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir);
	void MergeKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir);
	void SetSOI(POINT pt);
	void SetSOI(UINT newSOI);

private:
	CEkranHandler();
	~CEkranHandler() {};
	BOOL Create();
	void SwapMenus(UINT leftOne);
	void SwapFrames(UINT leftOne);
	void SwapKadr(UINT leftOne);
	friend class CUtil;

	//TODO: СОИ должны быть сделаны по аналогии с существующими и разещены в commontypes. Тк существующие неподходят пока будет такой имитатор.
	UINT curSOI;

	// Этот массив содержит кадры. Максимум их может быть 8 (два ряда в каждом 4 восьмирушки)
	// У каждого кадра есть ID по которому можно понять его индекс в массиве.
	// Логика присвоения индекса и ID такая:
	// Смотрим какое положение кадр занимает на экране. Его левый верхний угол указывает
	// на ячейку которую он будет занимать в массиве. Например 2 кадра каждый размером в полэкрана
	// будут иметь ID 0 и 2 соотственно, а индексы будут [0][0] и [0][2].
	CKadr* displayCells[DISPLAY_ROWS][DISPLAY_COLS];

	CMechanicMenu* mechanicMenu[DISPLAY_COLS];

	CFrame* frames[DISPLAY_COLS];
};