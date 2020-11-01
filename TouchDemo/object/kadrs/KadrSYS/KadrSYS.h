#pragma once
#include "../AbstractKadr.h"
#include "EngineSys.h"

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
	void Rotate(const double dAngle, const POINT rotateCenter) {};
	void Reset() {};
	void LeftClickHandle(POINT pt) {};

private:

	/*class CBrakes;
	class Hydro;
	class Klin;
	class Oxygen;
	class Pnevmo;
	class PriborFuelSyst;
	class Seat;
	class Tanks;
	class Trim;*/

	void CreatePribors();
	void DeletePribors();

	CEngineSys* engineSysL;
	CEngineSys* engineSysR;
};