#include "stdafx.h"
#include "RadioButtonHandler.h"
#include "util/Util.h"

void CALLBACK CRadioButtonHandler::OnRadioButtonPress(MOUSE_EVNT bEvent, CRadioButton* btn)
{	
	std::vector<CRadioButton*> rButtonsGroup;
	for (CRadioButton* button : CRadioButton::allRadioButtons)
		if (_tcscmp(button->_groupName, btn->_groupName) == 0 && btn->_parentMenu == button->_parentMenu)
			rButtonsGroup.push_back(button);
	for (CRadioButton* button : rButtonsGroup)
		if (button->_enabled && button != btn)
		{
			button->_enabled = false;
			btn->_enabled = true;
		}
}