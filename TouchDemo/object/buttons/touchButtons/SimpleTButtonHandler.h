#pragma once
#include "SimpleTButton.h"

class CSimpleTButtonHandler
{
public:
	static void CALLBACK OnSimpleTButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn);
	static void CALLBACK OnChangePageTButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn);

	static void CALLBACK OnKBRDButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn);
	static void CALLBACK OnCAMButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn);
	static void CALLBACK OnRDRButtonPress(MOUSE_EVNT bEvent, CSimpleTButton* btn);

private:
	CSimpleTButtonHandler() {};
	~CSimpleTButtonHandler() {};
};

