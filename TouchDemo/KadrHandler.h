#pragma once

#include "StdAfx.h"
#include "Kadr.h"
#include "MechanicMenu.h"

#define DISPLAY_ROWS 2
#define DISPLAY_COLS 4

class CKadrHandler
{
public:
	CKadrHandler() {};
	~CKadrHandler() {};

	BOOL Create();
	CKadr* getDisplayCell(int row, int col) { return displayCells[row][col]; };
	void DivideKadr(UINT kadrID, KADR_SIZE kadrSize);
	void MergeKadr(UINT kadrID, KADR_SIZE kadrSize, MERGE_DIRECTION mergeDir);
	//void StartLine(const POINT firstTouchCoord, const bool singleTouch);
	//void FinishLine(const POINT lastTouchCoord);

private:
	// Этот массив содержит кадры. Максимум их может быть 8 (два ряда в каждом 4 восьмирушки)
	// У каждого кадра есть ID по которому можно понять его индекс в массиве.
	// Логика присвоения индекса и ID такая:
	// Смотрим какое положение кадр занимает на экране. Его левый верхний угол указывает
	// на ячейку которую он будет занимать в массиве. Например 2 кадра каждый размером в полэкрана
	// будут иметь ID 0 и 2 соотственно, а индексы будут [0][0] и [0][2].
	CKadr* displayCells[DISPLAY_ROWS][DISPLAY_COLS];

	CMechanicMenu* mechanicMenu[DISPLAY_COLS];
	/*POINT startLine;
	POINT endLine;
	bool multiLine;

	void ClearLines();
	void DrawLine(HDC hdc);*/
};