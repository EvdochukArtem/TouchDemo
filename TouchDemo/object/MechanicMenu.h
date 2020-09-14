#pragma once

#include "object/DrawingObject.h"
#include "buttons/AbstractButton.h"
#include "buttons/SimpleButton.h"
#include "buttons/MenuButton.h"

#define BUTTONS_MAX_NUM 7

class CMechanicMenu// : public CDrawingObject
{
public:
	CMechanicMenu(UINT id);
	~CMechanicMenu();

	void Draw(HDC hdc);
	void DrawBackground();
	bool PointIsMine(const POINT pt);
	void LeftClickHandle(POINT clickCoord);

private:
	UINT _id;

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

	void Draw(HDC hdc);
	void DrawBackground();
	void CreateButtons();
	void LeftClickHandle(POINT clickCoord);

	CMenuButton* buttons[BUTTONS_MAX_NUM];
	UINT curSOI;
	UINT _id;
};

class CMechanicMenu::CLoMenu : public CDrawingObject
{
	friend class CMechanicMenu;
private:
	CLoMenu(UINT id);
	~CLoMenu() {};

	void Draw(HDC hdc);
	void DrawBackground();
	void CreateButtons();
	void LeftClickHandle(POINT clickCoord);

	CSimpleButton* buttons[BUTTONS_MAX_NUM];
	UINT _id;
};