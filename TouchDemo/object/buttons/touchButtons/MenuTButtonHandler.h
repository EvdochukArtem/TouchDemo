#pragma once
#include "MenuTButton.h"

class CMenuTButtonHandler
{
public:
	static void CALLBACK OnMenuTButtonPress(MOUSE_EVNT bEvent, CMenuTButton* btn);
	
private:
	CMenuTButtonHandler() {};
	~CMenuTButtonHandler() {};
};

