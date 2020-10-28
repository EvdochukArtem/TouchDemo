/*
*	Класс представляющий рамку демонстрирующую состояние кадра (активный/СОИ).
*/
#pragma once
#include "DrawingObject.h"
#include "Kadr.h"

class CFrame : public CDrawingObject
{
public:
	CFrame(UINT id, UINT activeButton, KADR_SIZE frameSize);
	~CFrame() {};

	void Draw(HDC& hdc) {};
	void DrawBackground();
	void DrawBorders(HDC& hdc);
	void ChangeSize(KADR_SIZE newSize);
	CFrame* ChangePos(UINT newPos);
	
	bool GetBlockStatus() { return _blocked; };
	void SetBlock(bool blockStatus) { _blocked = blockStatus; Hide(blockStatus); };
	void SetSOIStatus(bool soiStatus);
	void EnableKadrTypeSelection();
	void DisableKadrTypeSelection();

private:

	void PlaceFrame();

	UINT _id;
	UINT _activeButton;
	bool _isSOI;
	bool _blocked;
	bool kadrSelection;
	KADR_SIZE _frameSize;
};