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
	// ���� ������ �������� �����. �������� �� ����� ���� 8 (��� ���� � ������ 4 �����������)
	// � ������� ����� ���� ID �� �������� ����� ������ ��� ������ � �������.
	// ������ ���������� ������� � ID �����:
	// ������� ����� ��������� ���� �������� �� ������. ��� ����� ������� ���� ���������
	// �� ������ ������� �� ����� �������� � �������. �������� 2 ����� ������ �������� � ���������
	// ����� ����� ID 0 � 2 �����������, � ������� ����� [0][0] � [0][2].
	CKadr* displayCells[DISPLAY_ROWS][DISPLAY_COLS];

	CMechanicMenu* mechanicMenu[DISPLAY_COLS];
	/*POINT startLine;
	POINT endLine;
	bool multiLine;

	void ClearLines();
	void DrawLine(HDC hdc);*/
};