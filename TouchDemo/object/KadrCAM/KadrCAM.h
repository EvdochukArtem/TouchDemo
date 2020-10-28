#pragma once
#include "../Kadr.h"

class CKadrCAM : public CKadr
{
public:
	CKadrCAM(UINT id, KADR_SIZE kadrSize);
	~CKadrCAM();
	
	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
};
