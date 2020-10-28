#include "stdafx.h"
#include "MenuButtonHandler.h"
#include "util/Util.h"

void CALLBACK CMenuButtonHandler::OnMenuButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	btn->Activate();
}

void CALLBACK CMenuButtonHandler::OnSetButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(ENABLE_KADR_TYPE_SELECTION, pt);
}

void CALLBACK CMenuButtonHandler::OnEscButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(DISABLE_KADR_TYPE_SELECTION, pt);
}

void CALLBACK CMenuButtonHandler::OnPLDButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(SWITCH_PLD, pt);
}

void CALLBACK CMenuButtonHandler::OnSYSTButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(SWITCH_SYST, pt);
}

void CALLBACK CMenuButtonHandler::OnCAMButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(SWITCH_CAM, pt);
}

void CALLBACK CMenuButtonHandler::OnMAPButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(SWITCH_MAP, pt);
}

void CALLBACK CMenuButtonHandler::OnRDRButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessCommand(SWITCH_RDR, pt);
}