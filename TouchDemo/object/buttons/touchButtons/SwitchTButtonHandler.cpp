#include "stdafx.h"
#include "SwitchTButtonHandler.h"
#include "util/Util.h"

void CALLBACK CSwitchTButtonHandler::OnCoordSysButtonPress(MOUSE_EVNT bEvent, CSwitchTButton* btn)
{
	btn->firstStatusActive = !btn->firstStatusActive;
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_SWITCH_COORD_SYS, pt);
}

void CALLBACK CSwitchTButtonHandler::OnTestPress(MOUSE_EVNT bEvent, CSwitchTButton* btn)
{
	btn->firstStatusActive = !btn->firstStatusActive;
}