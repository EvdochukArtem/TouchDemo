#pragma once
#include "RadioTButton.h"

class CRadioTButtonHandler
{
public:
	static void CALLBACK OnRadioTButtonPress(MOUSE_EVNT bEvent, CRadioTButton* btn);

private:
	CRadioTButtonHandler() {};
	~CRadioTButtonHandler() {};
};

