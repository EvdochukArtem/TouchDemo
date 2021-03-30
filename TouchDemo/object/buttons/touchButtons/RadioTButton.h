#pragma once
#include "../AbstractButton.h"

class CAbstractKadr;

class CRadioTButton : public CAbstractButton
{
public:
	CRadioTButton(int x, int y, LPCTSTR caption, LPCTSTR groupName, CAbstractKadr* parentKadr, void(CALLBACK* handler)(MOUSE_EVNT, CRadioTButton*));
	~CRadioTButton();
	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();


private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CRadioTButton*);
	bool _enabled;
	TCHAR _groupName[128];
	CAbstractKadr* _parentKadr;
	static std::vector<CRadioTButton*> allRadioTButtons;

	BLENDFUNCTION	blendFunc;
	HDC				tmpHDC;
	HBITMAP			tmpBITMAP;

	friend class CRadioTButtonHandler;
};