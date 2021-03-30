#pragma once
#include "SimpleButton.h"

class CSimpleButtonHandler
{
public:
	CSimpleButtonHandler() {};
	~CSimpleButtonHandler() {};

	static void CALLBACK OnPZKPress(MOUSE_EVNT bEvent, CSimpleButton* btn);
	static void CALLBACK OnMFMPress(MOUSE_EVNT bEvent, CSimpleButton* btn);
	static void CALLBACK OnSimpleButtonPress(MOUSE_EVNT bEvent, CSimpleButton* btn);
};

