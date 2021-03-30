#pragma once
#include "SwitchButton.h"

class CSwitchButtonHandler
{
public:
	CSwitchButtonHandler() {};
	~CSwitchButtonHandler() {};

	static void CALLBACK OnSwitchButtonPress(MOUSE_EVNT bEvent, CSwitchButton* btn);
};