#pragma once
#include "RadioButton.h"

class CRadioButtonHandler
{
public:
	static void CALLBACK OnRadioButtonPress(MOUSE_EVNT bEvent, CRadioButton* btn);

private:
	CRadioButtonHandler() {};
	~CRadioButtonHandler() {};
};