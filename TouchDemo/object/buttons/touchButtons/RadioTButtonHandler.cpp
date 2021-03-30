#include "stdafx.h"
#include "RadioTButtonHandler.h"
#include "util/Util.h"

void CALLBACK CRadioTButtonHandler::OnRadioTButtonPress(MOUSE_EVNT bEvent, CRadioTButton* btn)
{	
	std::vector<CRadioTButton*> rButtonsGroup;
	for (CRadioTButton* button : CRadioTButton::allRadioTButtons)
		if (_tcscmp(button->_groupName, btn->_groupName) == 0 && btn->_parentKadr == button->_parentKadr)
			rButtonsGroup.push_back(button);
	for (CRadioTButton* button : rButtonsGroup)
		if (button->_enabled && button != btn)
		{
			button->_enabled = false;
			btn->_enabled = true;
		}
}