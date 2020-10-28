#pragma once
#include "../Kadr.h"

class CKadrSYS : public CKadr
{
public:
	CKadrSYS(UINT id, KADR_SIZE kadrSize);
	~CKadrSYS();
	
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
};