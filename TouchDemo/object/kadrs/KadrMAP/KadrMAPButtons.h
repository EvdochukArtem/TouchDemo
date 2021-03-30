#pragma once
#include "../AbstractKadr.h"

class CAbstractButton;
class CKadrMAP;
class CSwitchTButton;
class CAbstractIndicatorButton;

class CKadrMAPButtons
{
public:
	CKadrMAPButtons(CKadrMAP* parent);
	~CKadrMAPButtons();

	bool HandleTouch(POINT& pt);
	void Hide(bool hidden);
	void Place();

	void EnableSubmenu();
	void DisableSubmenu();

	CSwitchTButton&	GetCoordSysButton();

private:
	CKadrMAP* kadrMAP;
	
	RECT kadrRect;

	CAbstractButton* buttons[MAX_TBUTTONS];
	CAbstractButton* subMenuButtons[MAX_TBUTTONS];
	POINT			 buttonPlaces[MAX_TBUTTONS];
	void CalculateConstants();
	void CalculateLeftSideButtonsPositions();
	void CalculateBottomSideButtonsPositions();
	void CalculateRightSideButtonsPositions();
	void InitButtons();
};