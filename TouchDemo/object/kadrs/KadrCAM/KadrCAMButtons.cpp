#include "stdafx.h"
#include "KadrCAMButtons.h"
#include "KadrCAM.h"
#include "../../buttons/touchButtons/SimpleTButtonHandler.h"
#include "../../buttons/touchButtons/SetTButtonHandler.h"


CKadrCAMButtons::CKadrCAMButtons(CKadrCAM* parent)
{
	this->kadrCAM = parent;
	GetRgnBox(kadrCAM->GetKadrRgn(), &kadrRect);
	
	CalculateConstants();
	InitButtons();
}


CKadrCAMButtons::~CKadrCAMButtons()
{
	kadrCAM = nullptr;
	delete buttons[0];
	buttons[0] = nullptr;
	subMenuButtons[0] = nullptr;
	for (int i = 1; i < MAX_TBUTTONS; i++)
	{
		if (buttons[i] != nullptr)
			delete buttons[i];
		if (subMenuButtons[i] != nullptr)
			delete subMenuButtons[i];
	}
}

void CKadrCAMButtons::InitButtons()
{	
	for (int i = 0; i < MAX_TBUTTONS; i++)
	{
		buttons[i] = nullptr;
		subMenuButtons[i] = nullptr;
	}	
	for (int i = 1; i < MAX_TBUTTONS; i++)
	{
		subMenuButtons[i] = new CSimpleTButton(buttonPlaces[i].x, buttonPlaces[i].y,
							_T("TEST"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		subMenuButtons[i]->Hide(true);
	}
	buttons[0] = new CSetTButton(buttonPlaces[0].x, buttonPlaces[0].y, CSetTButtonHandler::OnSetTButtonPress);
	subMenuButtons[0] = buttons[0];


}

void CKadrCAMButtons::Hide(bool hidden)
{
	if (kadrCAM->SubMenuIsOn())
	{
		for (int i = 0; i < MAX_TBUTTONS; i++)
			if (subMenuButtons[i] != nullptr)
				subMenuButtons[i]->Hide(hidden);
	}
	else
	{
		for (int i = 0; i < MAX_TBUTTONS; i++)
			if (buttons[i] != nullptr)
				buttons[i]->Hide(hidden);
	}
}

void CKadrCAMButtons::Place()
{
	if (kadrCAM->GetKadrSize() == KADR_SIZE_EIGHTH)
	{
		for (int i = MAX_LSIDE_TBUTTONS / 2; i < MAX_TBUTTONS - MAX_LSIDE_TBUTTONS / 2; i++)
		{
			if (buttons[i] != nullptr)
				buttons[i]->Hide(true);
			if (subMenuButtons[i] != nullptr)
				subMenuButtons[i]->Hide(true);

		}
	}
	else
	{
		for (int i = MAX_LSIDE_TBUTTONS / 2; i < MAX_TBUTTONS - MAX_LSIDE_TBUTTONS / 2; i++)
			if (kadrCAM->SubMenuIsOn())
			{
				if (subMenuButtons[i] != nullptr)
					subMenuButtons[i]->Hide(false);
			}
			else
			{
				if (buttons[i] != nullptr)
					buttons[i]->Hide(false);
			}
		GetRgnBox(kadrCAM->GetKadrRgn(), &kadrRect);
		CalculateConstants();
		for (int i = 0; i < MAX_TBUTTONS; i++)
		{
			if (buttons[i] != nullptr)
				buttons[i]->ChangePos(buttonPlaces[i].x, buttonPlaces[i].y);
			if (subMenuButtons[i] != nullptr)
				subMenuButtons[i]->ChangePos(buttonPlaces[i].x, buttonPlaces[i].y);
		}
	}
}

bool CKadrCAMButtons::HandleTouch(POINT& pt)
{
	for (int i = 0; i < MAX_TBUTTONS; i++)
		if (kadrCAM->SubMenuIsOn())
		{
			if (subMenuButtons[i] != nullptr && subMenuButtons[i]->PointIsMine(pt))
			{
				subMenuButtons[i]->LeftClickHandle();
				return true;
			}
		}
		else
		{
			if (buttons[i] != nullptr && buttons[i]->PointIsMine(pt))
			{
				buttons[i]->LeftClickHandle();
				return true;
			}
		}
	return false;
}

void CKadrCAMButtons::CalculateConstants()
{
	CalculateLeftSideButtonsPositions();
	CalculateBottomSideButtonsPositions();
	CalculateRightSideButtonsPositions();
	
}

void CKadrCAMButtons::CalculateLeftSideButtonsPositions()
{
	for (int i = 0; i < MAX_LSIDE_TBUTTONS; i++)
	{
		buttonPlaces[i].x = kadrRect.left + TBUTTON_VERT_INDENT;
		buttonPlaces[i].y = kadrRect.top + i * TBUTTON_SIDE_SIZE + (i + 1) * TBUTTON_VERT_INDENT;
	}
}

void CKadrCAMButtons::CalculateBottomSideButtonsPositions()
{
	int buttonHorIndent = (kadrRect.right - kadrRect.left - 2 * (TBUTTON_SIDE_SIZE + TBUTTON_VERT_INDENT) - TBUTTON_SIDE_SIZE * MAX_BSIDE_TBUTTONS) / (MAX_BSIDE_TBUTTONS + 1);
	for (int i = MAX_LSIDE_TBUTTONS; i < MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS; i++)
	{
		buttonPlaces[i].x = kadrRect.left + TBUTTON_SIDE_SIZE + TBUTTON_VERT_INDENT + (i - MAX_LSIDE_TBUTTONS) * TBUTTON_SIDE_SIZE + (i - MAX_LSIDE_TBUTTONS + 1) * buttonHorIndent;
		buttonPlaces[i].y = kadrRect.bottom - TBUTTON_SIDE_SIZE - TO_PIXEL(15);
	}
}

void CKadrCAMButtons::CalculateRightSideButtonsPositions()
{
	for (int i = MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS; i < MAX_TBUTTONS; i++)
	{
		buttonPlaces[i].x = kadrRect.right - TBUTTON_SIDE_SIZE - TBUTTON_VERT_INDENT;
		buttonPlaces[i].y = kadrRect.top + (MAX_LSIDE_TBUTTONS + (MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS - i) - 1) * TBUTTON_SIDE_SIZE + (MAX_LSIDE_TBUTTONS + (MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS - i)) * TBUTTON_VERT_INDENT;
	}
}

void CKadrCAMButtons::EnableSubmenu()
{
	for (int i = 0; i < MAX_TBUTTONS; i++)
	{
		if (buttons[i] != nullptr)
			buttons[i]->Hide(true);
		if (subMenuButtons[i] != nullptr)
			subMenuButtons[i]->Hide(false);
	}
	if (kadrCAM->GetKadrSize() == KADR_SIZE_EIGHTH)
		for (int i = MAX_LSIDE_TBUTTONS / 2; i < MAX_TBUTTONS - MAX_LSIDE_TBUTTONS / 2; i++)
			if (subMenuButtons[i] != nullptr)
				subMenuButtons[i]->Hide(true);
}

void CKadrCAMButtons::DisableSubmenu()
{
	for (int i = 0; i < MAX_TBUTTONS; i++)
	{
		if (subMenuButtons[i] != nullptr)
			subMenuButtons[i]->Hide(true);
		if (buttons[i] != nullptr)
			buttons[i]->Hide(false);
	}
	if (kadrCAM->GetKadrSize() == KADR_SIZE_EIGHTH)
		for (int i = MAX_LSIDE_TBUTTONS / 2; i < MAX_TBUTTONS - MAX_LSIDE_TBUTTONS / 2; i++)
			if (buttons[i] != nullptr)
				buttons[i]->Hide(true);
}