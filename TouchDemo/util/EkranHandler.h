#pragma once
#include "object/Kadr.h"
#include "object/MechanicMenu.h"

#define DISPLAY_ROWS 2
#define DISPLAY_COLS 4

class CEkranHandler
{
public:
	CKadr* getDisplayCell(UINT row, UINT col) { return displayCells[row][col]; };
	CMechanicMenu* getMechanicMenu(UINT col) { return mechanicMenu[col]; };
	void DivideKadr(UINT kadrID, KADR_SIZE kadrSize);
	void MergeKadr(UINT kadrID, KADR_SIZE kadrSize, MERGE_DIRECTION mergeDir);
	void SetSOI(UINT newSOI);

private:
	CEkranHandler() {};
	~CEkranHandler() {};
	BOOL Create();
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
};