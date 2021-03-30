#include "stdafx.h"
#include "SetTButtonHandler.h"
#include "util/Util.h"

void CALLBACK CSetTButtonHandler::OnSetTButtonPress(MOUSE_EVNT bEvent, CSetTButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	if (btn->_enabled)
	{
		EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_DISABLE_SUBMENU, pt);
		btn->_enabled = false;
	}
	else
	{
		EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_ENABLE_SUBMENU, pt);
		btn->_enabled = true;
	}
}
