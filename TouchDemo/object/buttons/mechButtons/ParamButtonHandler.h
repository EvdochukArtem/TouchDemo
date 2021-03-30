#pragma once
#include "ParamButton.h"

class CParamButtonHandler
{
public:
	CParamButtonHandler() {};
	~CParamButtonHandler() {};
	
	static void CALLBACK OnParamButtonPress(MOUSE_EVNT bEvent, CParamButton* btn);
};