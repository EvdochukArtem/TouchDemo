#include "stdafx.h"
#include "TabButtonHandler.h"
#include "util/Util.h"

void CALLBACK CTabButtonHandler::OnTabButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	btn->Activate();
}

void CALLBACK CTabButtonHandler::OnSetButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_ENABLE_KADR_TYPE_SELECTION, pt);
}

void CALLBACK CTabButtonHandler::OnEscButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_DISABLE_KADR_TYPE_SELECTION, pt);
}

void CALLBACK CTabButtonHandler::OnPLDButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_PLD, pt);
}

void CALLBACK CTabButtonHandler::OnSYSTButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_SYST, pt);
}

void CALLBACK CTabButtonHandler::OnCAMButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_CAM, pt);
}

void CALLBACK CTabButtonHandler::OnMAPButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_MAP, pt);
}

void CALLBACK CTabButtonHandler::OnRDRButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_RDR, pt);
}

/////////////////////////////////////////////////////////////////////////////////////////

void CALLBACK CTabButtonHandler::OnCAM1ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_CAM1, pt);
}

void CALLBACK CTabButtonHandler::OnCAM2ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_CAM2, pt);
}

void CALLBACK CTabButtonHandler::OnCAM3ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_CAM3, pt);
}

void CALLBACK CTabButtonHandler::OnCAM4ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_CAM4, pt);
}

void CALLBACK CTabButtonHandler::OnCAM5ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_CAM5, pt);
}
void CALLBACK CTabButtonHandler::OnNAVButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_NAV, pt);
}

void CALLBACK CTabButtonHandler::OnAIRButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_AIR, pt);
}

void CALLBACK CTabButtonHandler::OnGROUNDButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_GROUND, pt);
}

void CALLBACK CTabButtonHandler::OnMODE1ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_MODE1, pt);
}

void CALLBACK CTabButtonHandler::OnMODE2ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_MODE2, pt);
}

void CALLBACK CTabButtonHandler::OnSYS1ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_SYS1, pt);
}

void CALLBACK CTabButtonHandler::OnSYS2ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_SYS2, pt);
}

void CALLBACK CTabButtonHandler::OnSYS3ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_SYS3, pt);
}

void CALLBACK CTabButtonHandler::OnSYS4uttonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_SYS4, pt);
}

void CALLBACK CTabButtonHandler::OnSYS5ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessKadrCommand(KADR_COMM_SYS5, pt);
}
