#pragma once
#include "StdAfx.h"
#include "DrawingObject.h"

class CMechanicMenu : CDrawingObject
{
public:
	CMechanicMenu(UINT id, UINT kadrBorders);
	~CMechanicMenu();
	
	void Draw(HDC hdc);
	void DrawBackground();

private:
	UINT _id;
	//Координата начала
	UINT _x;

	HGDIOBJ oldPen;
	HGDIOBJ oldBrush;

	UINT _height;
};