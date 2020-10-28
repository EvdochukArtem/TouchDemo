#pragma once
#include "SimpleButton.h"

class CSimpleButtonHandler
{
public:
	CSimpleButtonHandler();
	~CSimpleButtonHandler();

	static void CALLBACK OnPZKPress(BUTTON_EVENT bEvent, CSimpleButton* btn);
	static void CALLBACK OnMFMPress(BUTTON_EVENT bEvent, CSimpleButton* btn);
	static void CALLBACK OnSimpleButtonPress(BUTTON_EVENT bEvent, CSimpleButton* btn);
};

