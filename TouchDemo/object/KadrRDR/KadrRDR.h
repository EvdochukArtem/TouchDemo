#pragma once
#include "../Kadr.h"

class CKadrRDR : public CKadr
{
public:
	CKadrRDR(UINT id, KADR_SIZE kadrSize);
	~CKadrRDR();
	
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
};