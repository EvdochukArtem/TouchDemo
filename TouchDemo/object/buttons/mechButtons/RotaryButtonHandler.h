#pragma once
#include "RotaryButton.h"

class CRotaryButtonHandler
{
public:
	CRotaryButtonHandler() {};
	~CRotaryButtonHandler() {};

	static void CALLBACK OnRotaryButtonScroll(MOUSE_EVNT bEvent, CRotaryButton* btn);
};