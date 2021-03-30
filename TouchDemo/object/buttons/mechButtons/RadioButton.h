#pragma once
#include "../AbstractButton.h"
#include "../../MechanicMenu.h"

class CRadioButton : public CAbstractButton
{
public:
	CRadioButton(int x, int y, int cx, int cy, LPCTSTR caption, LPCTSTR groupName, CMechanicMenu::CLoMenu* parentMenu, void(CALLBACK* handler)(MOUSE_EVNT, CRadioButton*));
	~CRadioButton();
	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CRadioButton*);
	bool _enabled;
	TCHAR _groupName[128];
	CMechanicMenu::CLoMenu* _parentMenu;
	static std::vector<CRadioButton*> allRadioButtons;

	friend class CRadioButtonHandler;
};