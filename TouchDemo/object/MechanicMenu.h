/*
*	Класс оболочка, содержащий в себе внутренние классы hiMenu и loMenu, символизиующие 
*	механиническое меню кадра.
*/
#pragma once
#include "DrawingObject.h"
#include "kadrs/AbstractKadr.h"

const int MECH_MENU_BUTTONS_MAX_NUM = 6;

class CAbstractButton;
class CSwitchButton;
class CRadioButton;
class CTabButton;
class CAbstractKadr;
class CRotaryButton;

class CMechanicMenu
{
public:
	CMechanicMenu(UINT id, KADR_TYPE type);
	~CMechanicMenu();

	void Hide(bool hidden);
	bool PointIsMine(const POINT& pt);
	void LeftClickHandle(POINT clickCoord);
	void MouseWheelHandle(double scrollFactor, POINT scrollCoord);
	bool GetBlockStatus();
	void SetBlock(bool blockStatus, SWIPE_DIRECTION swipeDir);
	void SetSOIStatus(bool soiStatus);
	bool GetSOIStatus();
	UINT GetActiveButtonPosition();
	CMechanicMenu* ChangePos(UINT newPos);
	void EnableKadrTypeSelection();
	void DisableKadrTypeSelection();
	CAbstractButton* GetRightHiButton() { return hiButton[1]; };
	CAbstractButton* GetLeftHiButton() { return hiButton[0]; };
	CRotaryButton* GetRightLoRotary() { return loRotary[1]; };
	CRotaryButton* GetLeftLoRotary() { return loRotary[0]; };

	class CLoMenu;
	class CHiMenu;

private:
	UINT _id;
	static CAbstractButton* hiButton[2];
	static CRotaryButton* loRotary[2];


	CHiMenu* hiMenu;
	CLoMenu* loMenu;
};

class CMechanicMenu::CHiMenu : public CDrawingObject
{
private:
	friend class CMechanicMenu;
	CHiMenu(UINT id, KADR_TYPE type);
	~CHiMenu();
	void Place();

	void Draw(HDC& hdc);
	void DrawBackground();
	void CreateButtons(KADR_TYPE type);
	void LeftClickHandle(POINT clickCoord);
	void EnableKadrTypeSelection();
	void DisableKadrTypeSelection();
	void Hide(bool hidden);

	CTabButton* buttons [MECH_MENU_BUTTONS_MAX_NUM];
	CTabButton* tmp [MECH_MENU_BUTTONS_MAX_NUM];
	UINT _curActive;
	bool _isSOI;
	UINT _id;
	bool _blocked;
	bool kadrSelection;
	SWIPE_DIRECTION _blockerSide;
};

class CMechanicMenu::CLoMenu : public CDrawingObject
{
private:
	friend class CMechanicMenu;
	CLoMenu(UINT id);
	~CLoMenu();
	void Place();

	void Draw(HDC& hdc);
	void DrawBackground();
	void CreateButtons();
	void LeftClickHandle(POINT clickCoord);
	void Hide(bool hidden);

	CAbstractButton* buttons [MECH_MENU_BUTTONS_MAX_NUM];
	UINT _id;
	LPCTSTR groupName;
};