#include "stdafx.h"
#include "SimpleTButtonHandler.h"
#include "util/Util.h"

void CALLBACK CSimpleTButtonHandler::OnSimpleTButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn)
{
	if (btn->_enabled)
		btn->_enabled = false;
	else
		btn->_enabled = true;

	//MessageBox(NULL, _T("Simple Tbutton pressed"), L"", MB_OK);
}

void CALLBACK CSimpleTButtonHandler::OnChangePageTButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn)
{
	//POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	//EKRAN_HANDLER.ProcessKadrCommand(CHANGE_PAGE, pt);
	MessageBox(NULL, _T("OnChangePageTButton pressed"), L"", MB_OK);
}

void CALLBACK CSimpleTButtonHandler::OnKBRDButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn)
{
	MessageBox(NULL, _T("Keyboard show"), L"", MB_OK);
	/*POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_SYST, pt);*/
}

void CALLBACK CSimpleTButtonHandler::OnCAMButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_CAM, pt);
}

void CALLBACK CSimpleTButtonHandler::OnRDRButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn)
{
	POINT pt = {btn->_x + btn->_cx / 2, btn->_y + btn->_cy / 2};
	EKRAN_HANDLER.ProcessMenuCommand(MENU_COMM_SWITCH_RDR, pt);
}