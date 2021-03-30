#include "stdafx.h"
#include "KadrCAM.h"
#include "util/Util.h"

#include "../Page.h"

#include "KadrCAMButtons.h"


CKadrCAM::CKadrCAM(UINT id, KADR_SIZE kadrSize) : CAbstractKadr(id, kadrSize)
{
	_kadrType		= KADR_TYPE_CAM;

	priborRgn = CreateRectRgn(_x + TO_PIXEL(4), _y + TO_PIXEL(4), _x + _cx - TO_PIXEL(4), _y + _cy - TO_PIXEL(4));
	
	buttons = nullptr;
	for (int i = 0; i < CAM_PAGES_MAX; i++)
		pages[i] = nullptr;

	CreatePribors();
}

CKadrCAM::~CKadrCAM()
{
	DeletePribors();
	if (priborRgn != nullptr)
	{
		DeleteObject(priborRgn);
		priborRgn = nullptr;
	}
}

void CKadrCAM::CreatePribors()
{
	buttons	= new CKadrCAMButtons(this);
	for (int i = 1; i < CAM_PAGES_MAX; i++)
		if (pages[i] != nullptr)
			pages[i]->Hide(true);
}

void CKadrCAM::DeletePribors()
{
	if (buttons != nullptr)
	{
		delete buttons;
		buttons = nullptr;
	}	
	for (int i = 0; i < CAM_PAGES_MAX; i++)
		if (pages[i] != nullptr)
		{
			delete pages[i];
			pages[i] = nullptr;
		}
}

void CKadrCAM::DisposePribors()
{
	if (priborRgn != nullptr)
	{
		DeleteObject(priborRgn);
		priborRgn = nullptr;
	}
	priborRgn = CreateRectRgn(_x + TO_PIXEL(4), _y + TO_PIXEL(4), _x + _cx - TO_PIXEL(4), _y + _cy - TO_PIXEL(4));

	if (buttons != nullptr)
		buttons->Place();
	if (_blocked)
		SetBlock(true);
}

void CKadrCAM::SetBlock(bool blockStatus)
{
	_blocked = blockStatus;
	Hide(blockStatus);
	
	switch (selectedInput)
	{
	case CAM_INPUT_1:
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_CAM1)
				page->Hide(blockStatus);
		break;
	case CAM_INPUT_2:
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_CAM2)
				page->Hide(blockStatus);
		break;
	case CAM_INPUT_3:
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_CAM3)
				page->Hide(blockStatus);
		break;
	case CAM_INPUT_4:
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_CAM4)
				page->Hide(blockStatus);
		break;
	case CAM_INPUT_5:
		for (CPage* page : pages)
			if (page != nullptr && page->GetPageType() == PAGE_CAM5)
				page->Hide(blockStatus);
		break;
	default:
		break;
	}
	if (buttons != nullptr)
		buttons->Hide(blockStatus);
}

void CKadrCAM::Draw(HDC& hdc)
{
	if (_blocked)
		return;
	//TextOut(hdc, _x+_cx/2, _y+_cy/2, L"CAM KADR", 10);
}

void CKadrCAM::DrawBackground()
{
	if (_blocked)
		return;
	//Ôîí
	oldPen = (HPEN)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackPen);
	oldBrush = (HBRUSH)SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.BlackBrush);
	Rectangle(DRAW_ENGINE.getBackgroundHDC(), _x, _y, _x + _cx, _y + _cy);
	if (_id / 4 == 1 && _kadrSize == KADR_SIZE_EIGHTH)
	{
		SelectObject(DRAW_ENGINE.getBackgroundHDC(), DRAW_KIT.GreyPen2);
		DrawBorders(DRAW_ENGINE.getBackgroundHDC());
	}
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldBrush);
	SelectObject(DRAW_ENGINE.getBackgroundHDC(), oldPen);
}

void CKadrCAM::ChangeSize(KADR_SIZE newSize)
{
	_kadrSize = newSize;
	Place();
	DisposePribors();
	for (CPage* page : pages)
		if (page != nullptr)
		{
			page->DisposePribors();
			if (_blocked)
				page->Hide(true);
		}
}

CAbstractKadr* CKadrCAM::ChangePos(UINT newPos)
{
	_id = newPos;
	Place();
	DisposePribors();
	for (CPage* page : pages)
		if (page != nullptr)
		{
			page->DisposePribors();
			if (_blocked)
				page->Hide(true);
		}
	return this;
}

void CKadrCAM::ProcessCommand(KADR_COMMANDS cmd)
{
	switch (cmd)
	{
	case KADR_COMM_ENABLE_SUBMENU:
		_subMenu = true;
		buttons->EnableSubmenu();
		break;
	case KADR_COMM_DISABLE_SUBMENU:
		_subMenu = false;
		buttons->DisableSubmenu();
		break;
	case KADR_COMM_CAM1:
		selectedInput	= CAM_INPUT_1;
		for (int i = 0; i < CAM_PAGES_MAX; i++)
			if (pages[i]->GetPageType() == PAGE_CAM1)
				pages[i]->Hide(false);
			else
				if (!pages[i]->IsHidden())
					pages[i]->Hide(true);
		break;
	case KADR_COMM_CAM2:
		selectedInput	= CAM_INPUT_2;
		for (int i = 0; i < CAM_PAGES_MAX; i++)
			if (pages[i]->GetPageType() == PAGE_CAM2)
				pages[i]->Hide(false);
			else
				if (!pages[i]->IsHidden())
					pages[i]->Hide(true);
		break;
	case KADR_COMM_CAM3:
		selectedInput	= CAM_INPUT_3;
		for (int i = 0; i < CAM_PAGES_MAX; i++)
			if (pages[i]->GetPageType() == PAGE_CAM3)
				pages[i]->Hide(false);
			else
				if (!pages[i]->IsHidden())
					pages[i]->Hide(true);
		break;
	case KADR_COMM_CAM4:
		selectedInput	= CAM_INPUT_5;
		for (int i = 0; i < CAM_PAGES_MAX; i++)
			if (pages[i]->GetPageType() == PAGE_CAM5)
				pages[i]->Hide(false);
			else
				if (!pages[i]->IsHidden())
					pages[i]->Hide(true);
		break;
	case KADR_COMM_CAM5:
		selectedInput	= CAM_INPUT_4;
		for (int i = 0; i < CAM_PAGES_MAX; i++)
			if (pages[i]->GetPageType() == PAGE_CAM4)
				pages[i]->Hide(false);
			else
				if (!pages[i]->IsHidden())
					pages[i]->Hide(true);
		break;
	default:
		break;
	}
}

void CKadrCAM::LeftClickHandle(POINT pt)
{
	if (buttons->HandleTouch(pt))
		return;
}