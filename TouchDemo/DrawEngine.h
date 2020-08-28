#pragma once

#include "StdAfx.h"
#include "DrawingObject.h"
#include <vector>

class CDrawEngine {

public:
	CDrawEngine();
	~CDrawEngine();
	BOOL Create();
	void AddDrawingObject(CDrawingObject* obj);
	void DeleteDrawingObject(CDrawingObject* obj);
	void Draw(HDC hdc);
	void UpdateBackground();
	HDC getBackgroundHDC() { return backgroundHDC; };

private:
	std::vector <CDrawingObject*> drawingObjects;
	HDC backgroundHDC;
	HDC tmpHDC;
	HBITMAP backgroundBITMAP;
	HBITMAP tmpBITMAP;
};