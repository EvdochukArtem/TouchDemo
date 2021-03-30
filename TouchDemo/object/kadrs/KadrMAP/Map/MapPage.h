#pragma once
#include "../../Page.h"

class CScaleCircle;

class CMapPage : public CPage
{
private:
	friend class CKadrMAP;

	CMapPage(CKadrMAP* parent, PAGE_TYPE pType);
	~CMapPage();
	
	void CreatePribors();
	void DeletePribors();
	void DisposePribors();

	void LeftClickHandle(POINT pt) {};
	void Hide(bool blockStatus);

	CScaleCircle*	scaleCircle;

	CKadrMAP* kadrMAP;
};

