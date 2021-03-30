#pragma once
#include "SetTButton.h"

class CSetTButtonHandler
{
public:
	static void CALLBACK OnSetTButtonPress(MOUSE_EVNT bEvent, CSetTButton* btn);

private:
	CSetTButtonHandler() {};
	~CSetTButtonHandler() {};
};

