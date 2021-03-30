#include "stdafx.h"
#include "SwitchButtonHandler.h"

void CALLBACK CSwitchButtonHandler::OnSwitchButtonPress(MOUSE_EVNT bEvent, CSwitchButton* btn)
{
	btn->enabled = !btn->enabled;
	MessageBox(NULL, _T("Switch button pressed"), L"", MB_OK);
}