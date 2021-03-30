#pragma once
#include "../AbstractButton.h"

class CAbstractKadr;
class CSimpleTButton;
const int MAX_MBUTTONS = 32; //ћаксимальное количество выпадающих кнопок меню

class CMenuTButton : public CAbstractButton
{
public:
	CMenuTButton(int x, int y, int buttonPos, CAbstractKadr* parentKadr, void(CALLBACK* handler)(MOUSE_EVNT, CMenuTButton*));
	~CMenuTButton();
	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();
	void AddButton(LPCTSTR caption, void(CALLBACK* handler)(MOUSE_EVNT, CSimpleTButton*));
	void Hide(bool hidden);
	CAbstractButton* ChangePos(int x, int y);
	bool PointIsMine(const POINT& touchCoord);

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CMenuTButton*);
	bool _enabled;
	CAbstractKadr* _parentKadr;
	static std::vector<CMenuTButton*> allMenuTButtons;

	int _buttonPos;
	int maxButtonsForThisMenu;
	int buttonsNum;
	int curSelected;
	CSimpleTButton* dropMenu[MAX_MBUTTONS];
	POINT buttonPlaces[MAX_MBUTTONS];
	void CalculateConstants();
	void CalculateLeftSidePositions();
	void CalculateBottomSidePositions();
	void CalculateRightSidePositions();

	BLENDFUNCTION	blendFunc;
	HDC				tmpHDC;
	HBITMAP			tmpBITMAP;

	POINT lastTouch;

	friend class CMenuTButtonHandler;
};

