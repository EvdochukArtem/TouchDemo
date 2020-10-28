/*
*	Класс отвечает за создание, управление и доступ к базовым объектам программы.
*/
#pragma once
#include "object/Kadr.h"
#include "object/KadrSYS/KadrSYS.h"
#include "object/KadrMAP/KadrMAP.h"
#include "object/KadrPIL/KadrPIL.h"
#include "object/KadrRDR/KadrRDR.h"
#include "object/KadrCAM/KadrCAM.h"
#include "object/MechanicMenu.h"
#include "object/Frame.h"

const int DISPLAY_ROWS = 2;
const int DISPLAY_COLS = 4;

enum EKRAN_HANDLER_COMMANDS;

class CEkranHandler
{
public:
	CKadr* GetKadr(UINT row, UINT col) { return kadrs[row][col]; };
	CMechanicMenu* GetMechanicMenu(UINT col) { return mechanicMenu[col]; };
	CFrame* GetFrames(UINT col) { return frames[col]; };
	void DivideKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir);	//Для восьмушек направление не важно
	void MergeKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir);	//Для восьмушек направление не важно
	void SetSOI(POINT pt);
	void SetSOI(UINT newSOI);
	void LeftMerge(SWIPE_DIRECTION swipeDir, UINT col);
	void RightMerge(SWIPE_DIRECTION swipeDir, UINT col);
	void ProcessCommand(EKRAN_HANDLER_COMMANDS cmd, POINT pt);

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

	// Этот массив содержит кадры. Максимум их может быть 8 (два ряда в каждом 4 восьмушки)
	// У каждого кадра есть ID по которому можно понять его индекс в массиве.
	// Логика присвоения индекса и ID такая:
	// Смотрим какое положение кадр занимает на экране. Его левый верхний угол указывает
	// на ячейку которую он будет занимать в массиве. Например 2 кадра каждый размером в полэкрана
	// будут иметь ID 0 и 2 соотственно, а индексы будут [0][0] и [0][2].
	CKadr* kadrs[DISPLAY_ROWS][DISPLAY_COLS];

	CMechanicMenu* mechanicMenu[DISPLAY_COLS];

	CFrame* frames[DISPLAY_COLS];

	UINT FindMechMenu(POINT pt);
	UINT FindFrame(POINT pt);
	std::pair<UINT, UINT> FindKadr(POINT pt);
	void SwitchKadr(KADR_TYPE type, POINT pt);
};

enum EKRAN_HANDLER_COMMANDS
{
	ENABLE_KADR_TYPE_SELECTION,
	DISABLE_KADR_TYPE_SELECTION,
	SWITCH_PLD,
	SWITCH_SYST,
	SWITCH_CAM,
	SWITCH_MAP,
	SWITCH_RDR,
};