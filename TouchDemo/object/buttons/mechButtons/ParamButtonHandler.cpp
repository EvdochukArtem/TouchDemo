#include "stdafx.h"
#include "ParamButtonHandler.h"
#include "util/Util.h"
#include "../../MechanicMenu.h"
#include "RotaryButton.h"

void CALLBACK CParamButtonHandler::OnParamButtonPress(MOUSE_EVNT bEvent, CParamButton* btn)
{
	for (CParamButton* button : CParamButton::allParamButtons)
		if (button->enabled && button != btn)
		{
			button->enabled = !button->enabled;
			if (button->_x < WIDTHPX / 2)
				EKRAN_HANDLER.GetMechanicMenu(0)->GetLeftLoRotary()->DeAttachParamButton();
			else
				EKRAN_HANDLER.GetMechanicMenu(0)->GetRightLoRotary()->DeAttachParamButton();
			break;
		}

	btn->enabled = !btn->enabled;
	if (btn->enabled)
	{
		if (btn->_x < WIDTHPX / 2)
			EKRAN_HANDLER.GetMechanicMenu(0)->GetLeftLoRotary()->AttachParamButton(btn);
		else
			EKRAN_HANDLER.GetMechanicMenu(0)->GetRightLoRotary()->AttachParamButton(btn);
	}
	else
	{
		if (btn->_x < WIDTHPX / 2)
			EKRAN_HANDLER.GetMechanicMenu(0)->GetLeftLoRotary()->DeAttachParamButton();
		else
			EKRAN_HANDLER.GetMechanicMenu(0)->GetRightLoRotary()->DeAttachParamButton();
	}
}