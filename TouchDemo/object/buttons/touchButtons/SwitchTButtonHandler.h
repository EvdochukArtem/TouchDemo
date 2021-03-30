#pragma once
#include "SwitchTButton.h"

class CSwitchTButtonHandler
{
public:
	static void CALLBACK OnTestPress(MOUSE_EVNT bEvent, CSwitchTButton* btn);
	static void CALLBACK OnCoordSysButtonPress(MOUSE_EVNT bEvent, CSwitchTButton* btn);

private:
	CSwitchTButtonHandler() {};
	~CSwitchTButtonHandler() {};
};

