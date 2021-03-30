#pragma once
#include "../AbstractKadr.h"

const int CAM_PAGES_MAX = 5;

class CPage;

class CKadrCAMButtons;

enum CAM_INPUT {
	CAM_INPUT_1,
	CAM_INPUT_2,
	CAM_INPUT_3,
	CAM_INPUT_4,
	CAM_INPUT_5,
};

class CKadrCAM : public CAbstractKadr
{
public:
	CKadrCAM(UINT id, KADR_SIZE kadrSize);
	~CKadrCAM();
	
	void Draw(HDC& hdc);
	void DrawBackground();
	
	void ChangeSize(KADR_SIZE newSize);
	CAbstractKadr* ChangePos(UINT newPos);
	void Move(const POINT firstTouchCoord, const POINT delta) {};
	void Zoom(const double dZoomFactor, const POINT zoomCenter) {};
	void DoRotate(const double dAngle, const POINT rotateCenter) {};
	void Reset() {};
	void LeftClickHandle(POINT pt);
	void ProcessKeyboard(UINT key) {};
	void ProcessCommand(KADR_COMMANDS cmd);
	void SetBlock(bool blockStatus);
	
	HRGN&			GetKadrRgn() { return priborRgn; };


private:

	CAM_INPUT selectedInput;

	HRGN priborRgn;
	
	void CreatePribors();
	void DeletePribors();
	void DisposePribors();
	
	CPage* pages[CAM_PAGES_MAX];

	CKadrCAMButtons*	buttons;
};
