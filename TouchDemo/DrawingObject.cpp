#include "DrawingObject.h"
#include "DrawEngine.h"

void CDrawingObject::RegisterDrawingObject()
{
	extern CDrawEngine drawEngine;
	drawEngine.AddDrawingObject(this);
};

void CDrawingObject::DeleteDrawingObject()
{
	extern CDrawEngine drawEngine;
	drawEngine.DeleteDrawingObject(this);
};