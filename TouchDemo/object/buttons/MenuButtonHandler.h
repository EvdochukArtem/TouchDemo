#pragma once
#include "MenuButton.h"

class CMenuButtonHandler
{
public:
	CMenuButtonHandler() {};
	~CMenuButtonHandler() {};
	
	static void CALLBACK OnMenuButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnSetButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnEscButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnPLDButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnSYSTButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnCAMButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnMAPButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
	static void CALLBACK OnRDRButtonPress(BUTTON_EVENT bEvent, CMenuButton* btn);
};

