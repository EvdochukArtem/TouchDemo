#pragma once
#include "TabButton.h"

class CTabButtonHandler
{
public:
	CTabButtonHandler() {};
	~CTabButtonHandler() {};
	
	static void CALLBACK OnTabButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnSetButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnEscButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnPLDButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnSYSTButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnCAMButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnMAPButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnRDRButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);

	//Кнопки кадра CAM
	static void CALLBACK OnCAM1ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnCAM2ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnCAM3ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnCAM4ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnCAM5ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	//Кнопки кадра MAP
	static void CALLBACK OnNAVButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnAIRButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnGROUNDButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnMODE1ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnMODE2ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	//Кнопки кадра SYS
	static void CALLBACK OnSYS1ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnSYS2ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnSYS3ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnSYS4uttonPress(MOUSE_EVNT bEvent, CTabButton* btn);
	static void CALLBACK OnSYS5ButtonPress(MOUSE_EVNT bEvent, CTabButton* btn);

};

