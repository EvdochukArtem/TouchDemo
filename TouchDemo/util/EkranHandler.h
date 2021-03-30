/*
*	����� �������� �� ��������, ���������� � ������ � ������� �������� ���������.
*/
#pragma once
#include "object/kadrs/AbstractKadr.h"

class CMechanicMenu;
class CFrame;
class CInfoLine;
class CTouchSymbol;

const int DISPLAY_ROWS = 2; //���-�� ����� � ������� ����� ������������� �����
const int DISPLAY_COLS = 4; //���-�� �������� � ������� ����� ������������� �����
const int KADRS_MAX_NUM = 5;

enum MENU_COMMANDS
{
	MENU_COMM_ENABLE_KADR_TYPE_SELECTION,
	MENU_COMM_DISABLE_KADR_TYPE_SELECTION,
	MENU_COMM_SWITCH_PLD,
	MENU_COMM_SWITCH_SYST,
	MENU_COMM_SWITCH_CAM,
	MENU_COMM_SWITCH_MAP,
	MENU_COMM_SWITCH_RDR,
};

class CEkranHandler
{
public:
	CAbstractKadr*	GetKadr(UINT row, UINT col) ;
	CMechanicMenu*	GetMechanicMenu(UINT col);
	CFrame*			GetFrames(UINT col) { return frames[col]; };
	CTouchSymbol*	GetTouchSymbol() { return touchSymb; };
	void DivideKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir);	//��� ��������� ����������� �� �����
	void MergeKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir);	//��� ��������� ����������� �� �����
	void SetSOI(POINT pt);
	void SetSOI(UINT newSOI);
	void LeftMerge(SWIPE_DIRECTION swipeDir, UINT col);
	void RightMerge(SWIPE_DIRECTION swipeDir, UINT col);
	void ProcessMenuCommand(MENU_COMMANDS cmd, POINT pt);
	void ProcessKadrCommand(KADR_COMMANDS cmd, POINT pt);
	void ProcessKeyboard(UINT key);

private:
	CEkranHandler();
	~CEkranHandler() {};
	BOOL Create();
	BOOL CleanUp();

	void SwapMenus(UINT leftOne);
	void SwapFrames(UINT leftOne);
	void SwapKadr(UINT leftOne);
	friend class CUtil;

	UINT curSOI;

	class KadrsAssembly;
	class MechMenuAssembly;
	//TODO: ���������� ���������
	// ���� ������ �������� �����. �������� �� ����� ���� 8 (��� ���� � ������ 4 ���������)
	// � ������� ����� ���� ID �� �������� ����� ������ ��� ������ � �������.
	// ������ ���������� ������� � ID �����:
	// ������� ����� ��������� ���� �������� �� ������. ��� ����� ������� ���� ���������
	// �� ������ ������� �� ����� �������� � �������. �������� 2 ����� ������ �������� � ���������
	// ����� ����� ID 0 � 2 �����������, � ������� ����� [0][0] � [0][2].
	KadrsAssembly* kadrs[DISPLAY_COLS];

	MechMenuAssembly* mechanicMenu[DISPLAY_COLS];

	CFrame* frames[DISPLAY_COLS];

	CInfoLine* infoLine;

	CTouchSymbol* touchSymb;

	int FindMechMenu(POINT pt);
	int FindFrame(POINT pt);
	std::pair<int, int> FindKadr(POINT pt);	//first : row, second : col
	void SwitchKadr(KADR_TYPE type, POINT pt);

};

class CEkranHandler::KadrsAssembly
{
public:
	KadrsAssembly(UINT id, KADR_SIZE kadrSize, KADR_TYPE type);
	~KadrsAssembly();
	CAbstractKadr*	GetActiveKadr() { return kadrs[curActive]; };
	void InvokeAuxKadr(UINT auxId);
	void InvokeAuxKadr(UINT auxId, KADR_TYPE type);
	void RemoveAuxKadr();
	CAbstractKadr* GetAuxKadr() { return auxKadr; };
	void SwitchKadr(KADR_TYPE type);
	void ChangeSize(KADR_SIZE newSize);
	KadrsAssembly* ChangePos(UINT newPos);

private:
	KADR_TYPE curActive;

	CAbstractKadr* kadrs[KADRS_MAX_NUM];
	CAbstractKadr* auxKadr;
};

class CEkranHandler::MechMenuAssembly
{
public:
	MechMenuAssembly(UINT id, KADR_TYPE type);
	~MechMenuAssembly();
	CMechanicMenu*	GetActiveMenu() { return menus[curActive]; };
	MechMenuAssembly* ChangePos(UINT newPos);
	void SwitchMenu(KADR_TYPE type);

private:
	KADR_TYPE curActive;

	CMechanicMenu* menus[KADRS_MAX_NUM];
};