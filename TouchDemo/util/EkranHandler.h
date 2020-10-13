/*
*	����� �������� �� ��������, ���������� � ������ � ������� �������� ���������.
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

	//TODO: ��� ������ ���� ������� �� �������� � ������������� � �������� � commontypes. �� ������������ ���������� ���� ����� ����� ��������.
	UINT curSOI;

	// ���� ������ �������� �����. �������� �� ����� ���� 8 (��� ���� � ������ 4 �����������)
	// � ������� ����� ���� ID �� �������� ����� ������ ��� ������ � �������.
	// ������ ���������� ������� � ID �����:
	// ������� ����� ��������� ���� �������� �� ������. ��� ����� ������� ���� ���������
	// �� ������ ������� �� ����� �������� � �������. �������� 2 ����� ������ �������� � ���������
	// ����� ����� ID 0 � 2 �����������, � ������� ����� [0][0] � [0][2].
	CKadr* displayCells[DISPLAY_ROWS][DISPLAY_COLS];

	CMechanicMenu* mechanicMenu[DISPLAY_COLS];

	CFrame* frames[DISPLAY_COLS];
};