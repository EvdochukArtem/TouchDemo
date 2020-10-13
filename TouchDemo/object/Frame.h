/*
*	Класс представляющий рамку демонстрирующую состояние кадра (активный/СОИ).
*/
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
	
	virtual bool GetBlockStatus() { return _blocked; };
	virtual void SetBlock(bool blockStatus) { _blocked = blockStatus; };

private:

	void PlaceFrame();

	UINT _id;
	UINT _activeButton;
	bool _isSOI;
	bool _blocked;
	KADR_SIZE _frameSize;
};