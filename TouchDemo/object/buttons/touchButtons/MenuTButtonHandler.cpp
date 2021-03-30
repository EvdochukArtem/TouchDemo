#include "stdafx.h"
#include "MenuTButtonHandler.h"
#include "SimpleTButton.h"

void CALLBACK CMenuTButtonHandler::OnMenuTButtonPress(MOUSE_EVNT bEvent, CMenuTButton* btn)
{
	std::vector<CMenuTButton*> mButtonsGroup;
	for (CMenuTButton* button : CMenuTButton::allMenuTButtons)
		if (button->_parentKadr == btn->_parentKadr)
			mButtonsGroup.push_back(button);
	for (CMenuTButton* button : mButtonsGroup)
		if (button->_enabled && button != btn)
		{
			button->_enabled = false;
			for (int i = 0; i < button->buttonsNum; i++)
				button->dropMenu[i]->Hide(true);
		}

	if (btn->_enabled)
	{
		btn->_enabled = false;
		for (int i = 0; i < btn->buttonsNum; i++)
			btn->dropMenu[i]->Hide(true);
	}
	else
	{
		btn->_enabled = true;
		for (int i = 0; i < btn->buttonsNum; i++)
			btn->dropMenu[i]->Hide(false);
	}
}