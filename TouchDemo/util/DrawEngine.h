#pragma once
#include "object/DrawingObject.h"

class CDrawEngine
{
public:
	void AddDrawingObject(CDrawingObject* obj);
	void DeleteDrawingObject(CDrawingObject* obj);
	void Draw(HDC hdc);
	void UpdateBackground();
	HDC getBackgroundHDC() { return backgroundHDC; };
	CDrawingObject* getDrawingObject(POINT pt);

private:
	CDrawEngine();
	~CDrawEngine();
	BOOL Create();

	friend class CUtil;

	std::vector <CDrawingObject*> drawingObjects;
	HDC backgroundHDC;
	HDC tmpHDC;
	HBITMAP backgroundBITMAP;
	HBITMAP tmpBITMAP;
};