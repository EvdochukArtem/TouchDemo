#pragma once
#include "StdAfx.h"
#include "DrawKit.h"

class CDrawingObject
{
public:

	virtual void RegisterDrawingObject(); 
	virtual void DeleteDrawingObject();
	virtual void Draw(HDC hdc) = 0;
	virtual void DrawBackground() = 0;
};