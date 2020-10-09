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
	
	CGestureEngine& getGestureEngine() { return gestureEngine; };
	CGestureEngineEmulator& getGestureEngineEmulator() { return gestureEngineEmulator; };
	CEkranHandler& getEkranHandler() { return EkranHandler; };
	CDrawKit& getDrawKit() { return drawKit; };
	CDrawEngine& getDrawEngine() { return drawEngine; };

private:
	static bool created;

	CUtil() {};
	~CUtil() {};
	CUtil(const CUtil&);
	CUtil& operator=(const CUtil&);

	CGestureEngine gestureEngine;
	CGestureEngineEmulator gestureEngineEmulator;
	CEkranHandler EkranHandler;
	CDrawEngine drawEngine;
	CDrawKit drawKit;
};

