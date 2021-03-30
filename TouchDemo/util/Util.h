/*
*	Класс инкапсулирующий в себе все утилитарные классы пакета.
*/
#pragma once
#include "GestureEngine.h"
#include "GestureEngineEmulator.h"
#include "EkranHandler.h"
#include "DrawEngine.h"
#include "DrawKit.h"

class CUtil
{
public:
	static CUtil& Instance();
	BOOL Create();
	BOOL CleanUp();

	CGestureEngine&			GetGestureEngine() { return gestureEngine; };
	CGestureEngineEmulator&	GetGestureEngineEmulator() { return gestureEngineEmulator; };
	CEkranHandler&			GetEkranHandler() { return ekranHandler; };
	CDrawKit&				GetDrawKit() { return drawKit; };
	CDrawEngine&			GetDrawEngine() { return drawEngine; };

private:
	CUtil() {};
	~CUtil() {};
	CUtil(const CUtil&);

	CUtil& operator=(const CUtil&);

	CGestureEngine			gestureEngine;
	CGestureEngineEmulator	gestureEngineEmulator;
	CEkranHandler			ekranHandler;
	CDrawEngine				drawEngine;
	CDrawKit				drawKit;
};

