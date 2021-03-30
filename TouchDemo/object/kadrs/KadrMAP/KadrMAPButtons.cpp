#include "stdafx.h"
#include "KadrMAPButtons.h"
#include "KadrMAP.h"
#include "../../buttons/touchButtons/SimpleTButtonHandler.h"
#include "../../buttons/touchButtons/SwitchTButtonHandler.h"
#include "../../buttons/touchButtons/RadioTButtonHandler.h"
#include "../../buttons/touchButtons/SetTButtonHandler.h"
#include "../../buttons/touchButtons/MenuTButtonHandler.h"
#include "../../buttons/touchButtons/ChangePageTButton.h"

CKadrMAPButtons::CKadrMAPButtons(CKadrMAP* kadrMAP)
{
	this->kadrMAP = kadrMAP;
	GetRgnBox(kadrMAP->GetKadrRgn(), &kadrRect);
	
	CalculateConstants();
	InitButtons();
}

void CKadrMAPButtons::InitButtons()
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
	
	buttons[3] = new CSimpleTButton(buttonPlaces[3].x, buttonPlaces[3].y, _T("TEST"), CSimpleTButtonHandler::OnSimpleTButtonPress);

	buttons[19] = new CSwitchTButton(buttonPlaces[19].x, buttonPlaces[19].y, _T("PLN"), _T("NRTH"), true, CSwitchTButtonHandler::OnCoordSysButtonPress);
	buttons[18] = new CSwitchTButton(buttonPlaces[18].x, buttonPlaces[18].y, _T("TEST"), false, CSwitchTButtonHandler::OnTestPress);

	buttons[17] = new CChangePageTButton(buttonPlaces[17].x, buttonPlaces[17].y, _T("TEST"), CSimpleTButtonHandler::OnChangePageTButtonPress);

	/*buttons[7] = new CRadioTButton(buttonPlaces[7].x, buttonPlaces[7].y, _T("TEST1"), _T("GROUP1"), CRadioTButtonHandler::OnRadioTButtonPress);
	buttons[8] = new CRadioTButton(buttonPlaces[8].x, buttonPlaces[8].y, _T("TEST2"), _T("GROUP1"), CRadioTButtonHandler::OnRadioTButtonPress);
	buttons[9] = new CRadioTButton(buttonPlaces[9].x, buttonPlaces[9].y, _T("TEST3"), _T("GROUP1"), CRadioTButtonHandler::OnRadioTButtonPress);
	buttons[10] = new CRadioTButton(buttonPlaces[10].x, buttonPlaces[10].y, _T("TEST4"), _T("GROUP1"), CRadioTButtonHandler::OnRadioTButtonPress);*/

	buttons[13] = new CRadioTButton(buttonPlaces[13].x, buttonPlaces[13].y, _T("TEST1"), _T("GROUP2"), kadrMAP, CRadioTButtonHandler::OnRadioTButtonPress);
	buttons[14] = new CRadioTButton(buttonPlaces[14].x, buttonPlaces[14].y, _T("TEST2"), _T("GROUP2"), kadrMAP, CRadioTButtonHandler::OnRadioTButtonPress);
	buttons[15] = new CRadioTButton(buttonPlaces[15].x, buttonPlaces[15].y, _T("TEST3"), _T("GROUP2"), kadrMAP, CRadioTButtonHandler::OnRadioTButtonPress);
	
	CMenuTButton* menuButton;
	for (int i = 1; i < MAX_TBUTTONS - 1; i++)
	{
		if (i != 4 && i != 5 && i != 16)
			continue;
		//if (i == 7 || i == 12)
		//	continue;
		//if (i > 7 && i < 12)
		//	continue;
		//if (i <= 7 || i >= 12)
		//	continue;
		menuButton = new CMenuTButton(buttonPlaces[i].x, buttonPlaces[i].y, i, kadrMAP, CMenuTButtonHandler::OnMenuTButtonPress);
		menuButton->AddButton(_T("TEST1"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST2"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST3"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST4"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST5"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST6"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST7"), CSimpleTButtonHandler::OnSimpleTButtonPress);

		menuButton->AddButton(_T("TEST8"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST9"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST10"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST11"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST12"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST13"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST14"), CSimpleTButtonHandler::OnSimpleTButtonPress);

		menuButton->AddButton(_T("TEST15"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST16"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST17"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST18"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST19"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST20"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST21"), CSimpleTButtonHandler::OnSimpleTButtonPress);

		menuButton->AddButton(_T("TEST22"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST23"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST24"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST25"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST26"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST27"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST28"), CSimpleTButtonHandler::OnSimpleTButtonPress);

		menuButton->AddButton(_T("TEST29"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST30"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST31"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST32"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST33"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST34"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		menuButton->AddButton(_T("TEST35"), CSimpleTButtonHandler::OnSimpleTButtonPress);
		buttons[i] = menuButton;
	}
}

CKadrMAPButtons::~CKadrMAPButtons()
{
	kadrMAP = nullptr;
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

void CKadrMAPButtons::Hide(bool hidden)
{
	if (kadrMAP->SubMenuIsOn())
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

void CKadrMAPButtons::Place()
{
	if (kadrMAP->GetKadrSize() == KADR_SIZE_EIGHTH)
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
			if (kadrMAP->SubMenuIsOn())
			{
				if (subMenuButtons[i] != nullptr)
					subMenuButtons[i]->Hide(false);
			}
			else
			{
				if (buttons[i] != nullptr)
					buttons[i]->Hide(false);
			}
		GetRgnBox(kadrMAP->GetKadrRgn(), &kadrRect);
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

bool CKadrMAPButtons::HandleTouch(POINT& pt)
{
	for (int i = 0; i < MAX_TBUTTONS; i++)
		if (kadrMAP->SubMenuIsOn())
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

CSwitchTButton& CKadrMAPButtons::GetCoordSysButton()
{
	return *(static_cast<CSwitchTButton*>(buttons[19]));
}

void CKadrMAPButtons::CalculateConstants()
{
	CalculateLeftSideButtonsPositions();
	CalculateBottomSideButtonsPositions();
	CalculateRightSideButtonsPositions();
	
}

void CKadrMAPButtons::CalculateLeftSideButtonsPositions()
{
	for (int i = 0; i < MAX_LSIDE_TBUTTONS; i++)
	{
		buttonPlaces[i].x = kadrRect.left + TBUTTON_VERT_INDENT;
		buttonPlaces[i].y = kadrRect.top + i * TBUTTON_SIDE_SIZE + (i + 1) * TBUTTON_VERT_INDENT;
	}
}

void CKadrMAPButtons::CalculateBottomSideButtonsPositions()
{
	int buttonHorIndent = (kadrRect.right - kadrRect.left - 2 * (TBUTTON_SIDE_SIZE + TBUTTON_VERT_INDENT) - TBUTTON_SIDE_SIZE * MAX_BSIDE_TBUTTONS) / (MAX_BSIDE_TBUTTONS + 1);
	for (int i = MAX_LSIDE_TBUTTONS; i < MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS; i++)
	{
		buttonPlaces[i].x = kadrRect.left + TBUTTON_SIDE_SIZE + TBUTTON_VERT_INDENT + (i - MAX_LSIDE_TBUTTONS) * TBUTTON_SIDE_SIZE + (i - MAX_LSIDE_TBUTTONS + 1) * buttonHorIndent;
		buttonPlaces[i].y = kadrRect.bottom - TBUTTON_SIDE_SIZE - TO_PIXEL(15);
	}
}

void CKadrMAPButtons::CalculateRightSideButtonsPositions()
{
	for (int i = MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS; i < MAX_TBUTTONS; i++)
	{
		buttonPlaces[i].x = kadrRect.right - TBUTTON_SIDE_SIZE - TBUTTON_VERT_INDENT;
		buttonPlaces[i].y = kadrRect.top + (MAX_LSIDE_TBUTTONS + (MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS - i) - 1) * TBUTTON_SIDE_SIZE + (MAX_LSIDE_TBUTTONS + (MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS - i)) * TBUTTON_VERT_INDENT;
	}
}

void CKadrMAPButtons::EnableSubmenu()
{
	for (int i = 0; i < MAX_TBUTTONS; i++)
	{
		if (buttons[i] != nullptr)
			buttons[i]->Hide(true);
		if (subMenuButtons[i] != nullptr)
			subMenuButtons[i]->Hide(false);
	}
	if (kadrMAP->GetKadrSize() == KADR_SIZE_EIGHTH)
		for (int i = MAX_LSIDE_TBUTTONS / 2; i < MAX_TBUTTONS - MAX_LSIDE_TBUTTONS / 2; i++)
			if (subMenuButtons[i] != nullptr)
				subMenuButtons[i]->Hide(true);
}

void CKadrMAPButtons::DisableSubmenu()
{
	for (int i = 0; i < MAX_TBUTTONS; i++)
	{
		if (subMenuButtons[i] != nullptr)
			subMenuButtons[i]->Hide(true);
		if (buttons[i] != nullptr)
			buttons[i]->Hide(false);
	}
	if (kadrMAP->GetKadrSize() == KADR_SIZE_EIGHTH)
		for (int i = MAX_LSIDE_TBUTTONS / 2; i < MAX_TBUTTONS - MAX_LSIDE_TBUTTONS / 2; i++)
			if (buttons[i] != nullptr)
				buttons[i]->Hide(true);
}