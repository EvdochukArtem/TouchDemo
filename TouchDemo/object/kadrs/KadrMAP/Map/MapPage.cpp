#include "stdafx.h"
#include "MapPage.h"
#include "../KadrMAP.h"
#include "ScaleCircle.h"

CMapPage::CMapPage(CKadrMAP* parent, PAGE_TYPE pType) : CPage(pType)
{
	kadrMAP = parent;

	scaleCircle = nullptr;
	CreatePribors();
}

CMapPage::~CMapPage()
{
	DeletePribors();
}

void CMapPage::CreatePribors()
{
	RECT tmp;
	GetRgnBox(kadrMAP->GetKadrRgn(), &tmp);
	int x = tmp.left;
	int y = tmp.top;
	int cx = tmp.right - tmp.left;
	int cy = tmp.bottom - tmp.top;

	scaleCircle	= new CScaleCircle(kadrMAP);
}

void CMapPage::DeletePribors()
{
	if (scaleCircle != nullptr)
	{
		delete scaleCircle;
		scaleCircle = nullptr;
	}
}

void CMapPage::DisposePribors()
{
	RECT tmp;
	GetRgnBox(kadrMAP->GetKadrRgn(), &tmp);
	int x = tmp.left;
	int y = tmp.top;
	int cx = tmp.right - tmp.left;
	int cy = tmp.bottom - tmp.top;

	if (scaleCircle != nullptr)
		scaleCircle->Place();
}

void CMapPage::Hide(bool blockStatus)
{
	_hidden = blockStatus;
	if (scaleCircle != nullptr)
		scaleCircle->Hide(blockStatus);
}