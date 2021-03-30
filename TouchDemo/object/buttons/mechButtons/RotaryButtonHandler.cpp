#include "stdafx.h"
#include "RotaryButtonHandler.h"
#include "ParamButton.h"

void CALLBACK CRotaryButtonHandler::OnRotaryButtonScroll(MOUSE_EVNT bEvent, CRotaryButton* btn)
{
	switch (bEvent)
	{
	case M_EVNT_LB_DOWN:
		btn->paramBtn->ActivateNextValue();
		break;
	case M_EVNT_WHEEL_DOWN:
		btn->paramBtn->GetActiveValue().DecrimentValue();
		break;
	case M_EVNT_WHEEL_UP:
		btn->paramBtn->GetActiveValue().IncrimentValue();
		break;
	default:
		break;
	}
	btn->paramBtn->UpdateActivityTime();
}