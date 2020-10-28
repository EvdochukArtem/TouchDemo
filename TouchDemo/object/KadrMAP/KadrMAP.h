#pragma once
#include "../Kadr.h"

class CKadrMAP : public CKadr
{
public:
	CKadrMAP(UINT id, KADR_SIZE kadrSize);
	~CKadrMAP();

	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
};