/*
*	Класс оболочка, содержащий в себе внутренние классы hiMenu и loMenu, символизиующие 
*	механиническое меню кадра.
*/
#pragma once
#include "object/DrawingObject.h"
#include "buttons/AbstractButton.h"
#include "buttons/SimpleButton.h"
#include "buttons/MenuButton.h"

#define BUTTONS_MAX_NUM 6

class CMechanicMenu// : public CDrawingObject
{
public:
	CMechanicMenu(UINT id);
	~CMechanicMenu();
	
	void Draw(HDC hdc);
	void DrawBackground();
	bool PointIsMine(const POINT pt);
	void LeftClickHandle(POINT clickCoord);
	bool GetBlockStatus();
	void SetBlock(bool blockStatus);
	UINT GetActiveButtonPosition();
	CMechanicMenu* ChangePos(UINT newPos);
	void ChangeSOIStatus();

private:
	UINT _id;
	static CSimpleButton* hiButton[2];
	static CSimpleButton* loRotary[2];//TODO: Тут должны быть крутилки

	class CHiMenu;
	class CLoMenu;

	CHiMenu* hiMenu;
	CLoMenu* loMenu;
};

class CMechanicMenu::CHiMenu : public CDrawingObject
{
	friend class CMechanicMenu;
private:
	CHiMenu(UINT id);
	~CHiMenu() {};
	void PlaceMenu();

	void Draw(HDC hdc);
	void DrawBackground();
	//void DrawBorders(HDC hdc);
	void CreateButtons();
	void LeftClickHandle(POINT clickCoord);

	CMenuButton* buttons [BUTTONS_MAX_NUM];
	UINT _curActive;
	bool _isSOI;
	UINT _id;
	bool _blocked;
};

class CMechanicMenu::CLoMenu : public CDrawingObject
{
	friend class CMechanicMenu;
private:
	CLoMenu(UINT id);
	~CLoMenu() {};
	void PlaceMenu();

	void Draw(HDC hdc);
	void DrawBackground();
	void CreateButtons();
	void LeftClickHandle(POINT clickCoord);

	CSimpleButton* buttons [BUTTONS_MAX_NUM];
	UINT _id;
};