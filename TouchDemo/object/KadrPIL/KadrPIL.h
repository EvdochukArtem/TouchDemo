#pragma once
#include "../Kadr.h"

class CKadrPIL : public CKadr
{
public:
	CKadrPIL(UINT id, KADR_SIZE kadrSize);
	~CKadrPIL();
	
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
};