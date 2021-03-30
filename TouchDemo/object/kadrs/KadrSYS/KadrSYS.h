#pragma once
#include "../AbstractKadr.h"

class CEngineSys;

class CKadrSYS : public CAbstractKadr
{
public:
	CKadrSYS(UINT id, KADR_SIZE kadrSize);
	~CKadrSYS();
	
	void Draw(HDC& hdc);
	void DrawBackground();
	void ChangeSize(KADR_SIZE newSize);
	CAbstractKadr* ChangePos(UINT newPos);
	void SetBlock(bool blockStatus);
	
	void Move(const POINT firstTouchCoord, const POINT delta) {};
	void Zoom(const double dZoomFactor, const POINT zoomCenter) {};
	void DoRotate(const double dAngle, const POINT rotateCenter) {};
	void Reset() {};
	void LeftClickHandle(POINT pt) {};
	virtual void ProcessKeyboard(UINT key) {};
	virtual void ProcessCommand(KADR_COMMANDS cmd) {};

private:
	void DrawPlane();

	void CreatePribors();
	void DeletePribors();

	CEngineSys*		engineSysL;
	CEngineSys*		engineSysR;

	POINT kadrCenter;
	POINT shift;
};