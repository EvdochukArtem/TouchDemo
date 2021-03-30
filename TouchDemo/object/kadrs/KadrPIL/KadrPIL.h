#pragma once
#include "../AbstractKadr.h"

class CKadrPIL : public CAbstractKadr
{
public:
	CKadrPIL(UINT id, KADR_SIZE kadrSize);
	~CKadrPIL();
	
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CAbstractKadr* ChangePos(UINT newPos);
	void SetBlock(bool blockStatus);

	virtual void Move(const POINT firstTouchCoord, const POINT delta) {};
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter) {};
	virtual void DoRotate(const double dAngle, const POINT rotateCenter) {};
	virtual void Reset() {};
	virtual void LeftClickHandle(POINT pt) {};
	virtual void ProcessKeyboard(UINT key) {};
	virtual void ProcessCommand(KADR_COMMANDS cmd) {};
private:
	void CreatePribors();
	void DeletePribors();

	POINT priborCenter;
	POINT shift;
};