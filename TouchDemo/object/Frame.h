#pragma once
#include "object/DrawingObject.h"
#include "object/Kadr.h"

class CFrame : CDrawingObject
{
public:
	CFrame(UINT id, UINT activeButton, KADR_SIZE frameSize);
	~CFrame() {};

	void Draw(HDC hdc) {};
	void DrawBackground();
	virtual void ChangeSOIStatus();
	void ChangeSize(KADR_SIZE newSize);
	CFrame* ChangePos(UINT newPos);

private:

	void CreateFrame();

	UINT _id;
	UINT _activeButton;
	bool _isSOI;
	KADR_SIZE _frameSize;
};