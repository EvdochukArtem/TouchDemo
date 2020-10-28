/*
*	Класс оболочка, содержащий в себе внутренние классы hiMenu и loMenu, символизиующие 
*	механиническое меню кадра.
*/
#pragma once
#include "DrawingObject.h"
#include "buttons/SimpleButtonHandler.h"
#include "buttons/MenuButtonHandler.h"
#include "Kadr.h"

const int BUTTONS_MAX_NUM = 6;

class CMechanicMenu
{
public:
	CMechanicMenu(UINT id, KADR_TYPE type);
	~CMechanicMenu();

	void Draw(HDC& hdc);
	void DrawBackground();
	bool PointIsMine(const POINT pt);
	void LeftClickHandle(POINT clickCoord);
	bool GetBlockStatus();
	void SetBlock(bool blockStatus, SWIPE_DIRECTION swipeDir);
	void SetSOIStatus(bool soiStatus);
	UINT GetActiveButtonPosition();
	CMechanicMenu* ChangePos(UINT newPos);
	void EnableKadrTypeSelection();
	void DisableKadrTypeSelection();

private:
	UINT _id;
	static CSimpleButton* hiButton[2];
	static CSimpleButton* loRotary[2]; //TODO: Тут должны быть крутилки

	class CHiMenu;
	class CLoMenu;

	CHiMenu* hiMenu;
	CLoMenu* loMenu;
};

class CMechanicMenu::CHiMenu : public CDrawingObject
{
	friend class CMechanicMenu;
private:
	CHiMenu(UINT id, KADR_TYPE type);
	~CHiMenu();
	void PlaceMenu();

	void Draw(HDC& hdc);
	void DrawBackground();
	void CreateButtons(KADR_TYPE type);
	void LeftClickHandle(POINT clickCoord);
	void EnableKadrTypeSelection();
	void DisableKadrTypeSelection();

	CMenuButton* buttons [BUTTONS_MAX_NUM];
	CMenuButton* tmp [BUTTONS_MAX_NUM];
	UINT _curActive;
	bool _isSOI;
	UINT _id;
	bool _blocked;
	bool kadrSelection;
	SWIPE_DIRECTION _blockerSide;
};

class CMechanicMenu::CLoMenu : public CDrawingObject
{
	friend class CMechanicMenu;
private:
	CLoMenu(UINT id);
	~CLoMenu();
	void PlaceMenu();

	void Draw(HDC& hdc);
	void DrawBackground();
	void CreateButtons();
	void LeftClickHandle(POINT clickCoord);

	CSimpleButton* buttons [BUTTONS_MAX_NUM];
	UINT _id;
};