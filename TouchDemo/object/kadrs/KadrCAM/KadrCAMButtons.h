#pragma once
#include "../AbstractKadr.h"

class CAbstractButton;
class CKadrCAM;

class CKadrCAMButtons
{
public:
	CKadrCAMButtons(CKadrCAM* parent);
	~CKadrCAMButtons();
	
	bool HandleTouch(POINT& pt);
	void Hide(bool hidden);
	void Place();

	void EnableSubmenu();
	void DisableSubmenu();

private:
	CKadrCAM* kadrCAM;
	
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

