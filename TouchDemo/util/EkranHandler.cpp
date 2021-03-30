#include "StdAfx.h"
#include "EkranHandler.h"
#include "object/Frame.h"
#include "object/InfoLine.h"
#include "object/TouchSymbol.h"
#include "object/MechanicMenu.h"
#include "object/kadrs/BlankKadr.h"
#include "object/kadrs/auxilary/BlankAuxKadr.h"
#include "object/kadrs/KadrSYS/KadrSYS.h"
#include "object/kadrs/KadrMAP/KadrMAP.h"
#include "object/kadrs/KadrPIL/KadrPIL.h"
#include "object/kadrs/KadrRDR/KadrRDR.h"
#include "object/kadrs/KadrCAM/KadrCAM.h"
#include <cassert>

CEkranHandler::CEkranHandler()
{
	curSOI = 1;
}

BOOL CEkranHandler::Create()
{
	kadrs[0] = new KadrsAssembly(0, KADR_SIZE_QUARTER, KADR_TYPE_CAM);
	kadrs[1] = new KadrsAssembly(1, KADR_SIZE_QUARTER, KADR_TYPE_MAP);
	kadrs[2] = new KadrsAssembly(2, KADR_SIZE_QUARTER, KADR_TYPE_RDR);
	kadrs[3] = new KadrsAssembly(3, KADR_SIZE_QUARTER, KADR_TYPE_SYST);
	infoLine = new CInfoLine();
	touchSymb = new CTouchSymbol();
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		mechanicMenu[i] = new MechMenuAssembly(i, kadrs[i]->GetActiveKadr()->GetKadrType());
		frames[i] = new CFrame(i, mechanicMenu[i]->GetActiveMenu()->GetActiveButtonPosition(), KADR_SIZE_QUARTER);
	}
	kadrs[curSOI]->GetActiveKadr()->SetSOIStatus(true);
	mechanicMenu[curSOI]->GetActiveMenu()->SetSOIStatus(true);
	frames[curSOI]->SetSOIStatus(true);
	return TRUE;
}

BOOL CEkranHandler::CleanUp()
{
	delete infoLine;
	delete touchSymb;
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		delete kadrs[i];
		delete mechanicMenu[i];
		delete frames[i];
	}
	return TRUE;
}

CAbstractKadr*	CEkranHandler::GetKadr(UINT row, UINT col)
{ 
	if (row == 0)
		return kadrs[col]->GetActiveKadr();
	else
		return kadrs[col]->GetAuxKadr();
}

CMechanicMenu*	CEkranHandler::GetMechanicMenu(UINT col)
{
	return mechanicMenu[col]->GetActiveMenu();
}

void CEkranHandler::SetSOI(POINT pt)
{
	if (kadrs[curSOI]->GetActiveKadr()->GetBlockStatus() == false)
		kadrs[curSOI]->GetActiveKadr()->SetSOIStatus(false);
	else
		kadrs[curSOI - 1]->GetActiveKadr()->SetSOIStatus(false);

	if (frames[curSOI]->GetBlockStatus() == false)
		frames[curSOI]->SetSOIStatus(false);
	else
		frames[curSOI - 1]->SetSOIStatus(false);
	mechanicMenu[curSOI]->GetActiveMenu()->SetSOIStatus(false);

	curSOI = FindMechMenu(pt);

	if (kadrs[curSOI]->GetActiveKadr()->GetBlockStatus() == false)
		kadrs[curSOI]->GetActiveKadr()->SetSOIStatus(true);
	else
		kadrs[curSOI - 1]->GetActiveKadr()->SetSOIStatus(true);

	if (frames[curSOI]->GetBlockStatus() == false)
		frames[curSOI]->SetSOIStatus(true);
	else
		frames[curSOI - 1]->SetSOIStatus(true);
	mechanicMenu[curSOI]->GetActiveMenu()->SetSOIStatus(true);
}

void CEkranHandler::SetSOI(UINT newSOI)
{
	kadrs[curSOI]->GetActiveKadr()->SetSOIStatus(false);
	frames[curSOI]->SetSOIStatus(false);
	mechanicMenu[curSOI]->GetActiveMenu()->SetSOIStatus(false);
	
	curSOI = newSOI;
	
	kadrs[curSOI]->GetActiveKadr()->SetSOIStatus(true);
	frames[curSOI]->SetSOIStatus(true);
	mechanicMenu[curSOI]->GetActiveMenu()->SetSOIStatus(true);
}

void CEkranHandler::SwapMenus(UINT leftOne)
{
	MechMenuAssembly* tmp = mechanicMenu[leftOne];
	mechanicMenu[leftOne] = mechanicMenu[leftOne + 1]->ChangePos(leftOne);
	mechanicMenu[leftOne + 1] = tmp->ChangePos(leftOne + 1);
	if (curSOI == leftOne)
		curSOI = leftOne + 1;
	else if (curSOI == leftOne + 1)
		curSOI = leftOne;
}

void CEkranHandler::SwapKadr(UINT leftOne)
{
	KadrsAssembly* tmp = nullptr;
	tmp = kadrs[leftOne];
	kadrs[leftOne] = kadrs[leftOne + 1]->ChangePos(leftOne);
	kadrs[leftOne + 1] = tmp->ChangePos(leftOne + 1);
	if (curSOI == leftOne)
		curSOI = leftOne + 1;
	else if (curSOI == leftOne + 1)
		curSOI = leftOne;
}

void CEkranHandler::SwapFrames(UINT leftOne)
{
	CFrame* tmp = frames[leftOne];
	frames[leftOne] = frames[leftOne + 1]->ChangePos(leftOne);
	frames[leftOne + 1] = tmp->ChangePos(leftOne + 1);
	if (curSOI == leftOne)
		curSOI = leftOne + 1;
	else if (curSOI == leftOne + 1)
		curSOI = leftOne;
}

void CEkranHandler::DivideKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir)
{
	UINT col = kadrID % 4;
	mechanicMenu[col]->GetActiveMenu()->DisableKadrTypeSelection();
	frames[col]->DisableKadrTypeSelection();
	if (swipeDir == SWIPE_DIR_LEFT && col > 0 && kadrSize != KADR_SIZE_QUARTER)
	{
		assert(col < 3);
		mechanicMenu[col + 1]->GetActiveMenu()->DisableKadrTypeSelection();
		frames[col + 1]->DisableKadrTypeSelection();
	}
	if (swipeDir == SWIPE_DIR_RIGHT && col < 3 && kadrSize != KADR_SIZE_QUARTER)
	{
		mechanicMenu[col + 1]->GetActiveMenu()->DisableKadrTypeSelection();
		frames[col + 1]->DisableKadrTypeSelection();
	}
	switch (kadrSize)
	{
	case KADR_SIZE_HALF:
	{
		if (swipeDir == SWIPE_DIR_RIGHT)
		{
			kadrs[col]->ChangeSize(KADR_SIZE_QUARTER);
			SwapKadr(col);
			frames[col]->ChangeSize(KADR_SIZE_QUARTER);
			SwapFrames(col);
			if (!mechanicMenu[col]->GetActiveMenu()->GetBlockStatus())
				SwapMenus(col);
			mechanicMenu[col]->GetActiveMenu()->SetBlock(false, swipeDir);
			frames[col]->SetBlock(false);
			kadrs[col]->GetActiveKadr()->SetBlock(false);
		} else {
			kadrs[col]->ChangeSize(KADR_SIZE_QUARTER);
			frames[col]->ChangeSize(KADR_SIZE_QUARTER);
			if (mechanicMenu[col]->GetActiveMenu()->GetBlockStatus())
				SwapMenus(col);
			assert(col < 3);
			mechanicMenu[col + 1]->GetActiveMenu()->SetBlock(false, swipeDir);
			frames[col + 1]->SetBlock(false);
			kadrs[col + 1]->GetActiveKadr()->SetBlock(false);
		}
	}
	break;
	case KADR_SIZE_QUARTER:
	{
		kadrs[col]->ChangeSize(KADR_SIZE_EIGHTH);
		frames[col]->ChangeSize(KADR_SIZE_EIGHTH);
		kadrs[col]->InvokeAuxKadr(col + 4);
	}
	break;
	default:
		MessageBox(NULL, L"Invalid kadrSize!", L"Error", MB_OK | MB_ICONERROR);
		break;
	}
}

void CEkranHandler::MergeKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir)
{
	UINT row = kadrID / 4;
	UINT col = kadrID % 4;
	mechanicMenu[col]->GetActiveMenu()->DisableKadrTypeSelection();
	if (swipeDir == SWIPE_DIR_LEFT && col > 0)
		mechanicMenu[col - 1]->GetActiveMenu()->DisableKadrTypeSelection();
	if (swipeDir == SWIPE_DIR_RIGHT && col < 3)
		mechanicMenu[col + 1]->GetActiveMenu()->DisableKadrTypeSelection();
	if (row == 0 && kadrSize != KADR_SIZE_EIGHTH)
	{
		frames[col]->DisableKadrTypeSelection();
		if (swipeDir == SWIPE_DIR_LEFT && col > 0)
			frames[col - 1]->DisableKadrTypeSelection();
		if (swipeDir == SWIPE_DIR_RIGHT && col < 3)
			frames[col + 1]->DisableKadrTypeSelection();
	}
	switch (kadrSize)
	{
	case KADR_SIZE_HALF:
		break;
	case KADR_SIZE_QUARTER:
	{
		if (swipeDir == SWIPE_DIR_RIGHT)
			RightMerge(swipeDir, col);
		else 
			LeftMerge(swipeDir, col);
	}
		break;
	case KADR_SIZE_EIGHTH:
	{
		kadrs[col]->ChangeSize(KADR_SIZE_QUARTER);
		frames[col]->ChangeSize(KADR_SIZE_QUARTER);
		kadrs[col]->RemoveAuxKadr();
	}
		break;
	default:
		break;
	}
}


void CEkranHandler::RightMerge(SWIPE_DIRECTION swipeDir, UINT col)
{
	if (col == 3)	//если кадр крайний правый, то выходим
		return;
	else
	{
		if (col < 2 && kadrs[col + 2]->GetActiveKadr()->GetBlockStatus())	//когда кадр, в который мы собираемся расшириться, 
		{													//является половинкой (KADR_SIZE_HALF) делаем его четвертинкой
			kadrs[col + 1]->ChangeSize(KADR_SIZE_QUARTER);
			SwapKadr(col + 1);
			frames[col + 1]->ChangeSize(KADR_SIZE_QUARTER);
			SwapFrames(col + 1);
			if (!mechanicMenu[col + 1]->GetActiveMenu()->GetBlockStatus())	
				SwapMenus(col + 1);
		} else {
			if (kadrs[col + 1]->GetAuxKadr() != nullptr)
				MergeKadr(col + 1, KADR_SIZE_EIGHTH, swipeDir);
			kadrs[col + 1]->GetActiveKadr()->SetBlock(true);	//блокировка соседнего кадра
			frames[col + 1]->SetBlock(true);
			mechanicMenu[col + 1]->GetActiveMenu()->SetBlock(true, swipeDir);
			if (col + 1 == curSOI)
				SetSOI(col);
		}
		kadrs[col]->ChangeSize(KADR_SIZE_HALF);
		frames[col]->ChangeSize(KADR_SIZE_HALF);
	}
}

void CEkranHandler::LeftMerge(SWIPE_DIRECTION swipeDir, UINT col)
{
	if (col == 0)
		return;
	else
	{
		if (kadrs[col - 1]->GetActiveKadr()->GetBlockStatus())		//когда кадр, в который мы собираемся расшириться, 
		{											//является половинкой (KADR_SIZE_HALF) делаем его четвертинкой
			kadrs[col - 2]->ChangeSize(KADR_SIZE_QUARTER);
			frames[col - 2]->ChangeSize(KADR_SIZE_QUARTER);
			if (mechanicMenu[col - 2]->GetActiveMenu()->GetBlockStatus())
				SwapMenus(col - 2);
		} else {
			if (curSOI == col - 1)
				SetSOI(col);
			if (kadrs[col - 1]->GetAuxKadr() != nullptr)
				MergeKadr(col - 1, KADR_SIZE_EIGHTH, swipeDir);
		}
		SwapKadr(col - 1);
		SwapFrames(col - 1);
		kadrs[col - 1]->ChangeSize(KADR_SIZE_HALF);
		frames[col - 1]->ChangeSize(KADR_SIZE_HALF);
		kadrs[col]->GetActiveKadr()->SetBlock(true);
		frames[col]->SetBlock(true);
		mechanicMenu[col - 1]->GetActiveMenu()->SetBlock(true, swipeDir);
	}
}

int CEkranHandler::FindFrame(POINT pt)
{
	for (int i = 0; i < DISPLAY_COLS; i++)
		if (frames[i]->PointIsMine(pt))
			return i;
	return -1;
}

int CEkranHandler::FindMechMenu(POINT pt)
{
	for (int i = 0; i < DISPLAY_COLS; i++)
		if (mechanicMenu[i]->GetActiveMenu()->PointIsMine(pt))
			return i;
	return -1;
}

std::pair<int, int> CEkranHandler::FindKadr(POINT pt)
{
	for (int j = 0; j < DISPLAY_COLS; j++)
		if (kadrs[j]->GetActiveKadr()->PointIsMine(pt))
			return std::make_pair(0, j);
		else if (kadrs[j]->GetAuxKadr() != nullptr && kadrs[j]->GetAuxKadr()->PointIsMine(pt))
			return std::make_pair(1, j);
	return std::make_pair(-1, -1);
}

void CEkranHandler::ProcessKadrCommand(KADR_COMMANDS cmd, POINT pt)
{
	std::pair<int, int> curKadr = FindKadr(pt);
	if (curKadr.first == -1 && curKadr.second == -1)
	{
		curKadr.first = 0;
		curKadr.second = FindMechMenu(pt);
	}
	if (curKadr.first == 1)
		kadrs[curKadr.second]->GetAuxKadr()->ProcessCommand(cmd);
	else
		kadrs[curKadr.second]->GetActiveKadr()->ProcessCommand(cmd);
}

void CEkranHandler::ProcessKeyboard(UINT key)
{
	kadrs[curSOI]->GetActiveKadr()->ProcessKeyboard(key);
}

void CEkranHandler::ProcessMenuCommand(MENU_COMMANDS cmd, POINT pt)
{
	switch (cmd)
	{
	case MENU_COMM_ENABLE_KADR_TYPE_SELECTION:
		{
			int curCol = FindMechMenu(pt);
			assert(curCol >= 0);
			mechanicMenu[curCol]->GetActiveMenu()->EnableKadrTypeSelection();
			if (frames[curCol]->GetBlockStatus())
			{
				assert(curCol > 0);
				frames[curCol - 1]->EnableKadrTypeSelection();
			}
			else
				frames[curCol]->EnableKadrTypeSelection();
		}
		break;
	case MENU_COMM_DISABLE_KADR_TYPE_SELECTION:
		{
			int curCol = FindMechMenu(pt);
			assert(curCol >= 0);
			mechanicMenu[curCol]->GetActiveMenu()->DisableKadrTypeSelection();
			if (frames[curCol]->GetBlockStatus())
			{
				assert(curCol > 0);
				frames[curCol - 1]->EnableKadrTypeSelection();
			}
			else
				frames[curCol]->DisableKadrTypeSelection();
		}
		break;
	case MENU_COMM_SWITCH_PLD:
		SwitchKadr(KADR_TYPE_PLD, pt);
		break;
	case MENU_COMM_SWITCH_SYST:
		SwitchKadr(KADR_TYPE_SYST, pt);
		break;
	case MENU_COMM_SWITCH_CAM:
		SwitchKadr(KADR_TYPE_CAM, pt);
		break;
	case MENU_COMM_SWITCH_MAP:
		SwitchKadr(KADR_TYPE_MAP, pt);
		break;
	case MENU_COMM_SWITCH_RDR:
		SwitchKadr(KADR_TYPE_RDR, pt);
		break;
	default:
		break;
	}
}

void CEkranHandler::SwitchKadr(KADR_TYPE type, POINT pt)
{
	KADR_SIZE size;
	std::pair<UINT, UINT> rowAndCol = std::make_pair(0 , 0);
	int menuCol = FindMechMenu(pt);
	
	if (menuCol == -1)
	{
		rowAndCol = FindKadr(pt); // значит команда пришла от нижней восьмушки и мех меню переключать не надо
		menuCol = rowAndCol.second;
	}
	else
		if (kadrs[menuCol]->GetActiveKadr()->GetBlockStatus())
			rowAndCol.second = menuCol - 1;
		else
			rowAndCol.second = menuCol;

	size = kadrs[rowAndCol.second]->GetActiveKadr()->GetKadrSize();
	
	if (rowAndCol.first == 1)
	{
		kadrs[rowAndCol.second]->RemoveAuxKadr();
		kadrs[rowAndCol.second]->InvokeAuxKadr(rowAndCol.second + 4, type);
	}
	if (rowAndCol.first == 0)
	{
		kadrs[rowAndCol.second]->SwitchKadr(type);
		mechanicMenu[rowAndCol.second]->SwitchMenu(type);
		frames[rowAndCol.second]->DisableKadrTypeSelection();
	}
}

CEkranHandler::KadrsAssembly::KadrsAssembly(UINT id, KADR_SIZE kadrSize, KADR_TYPE type)
{
	kadrs[KADR_TYPE_PLD] = new CKadrPIL(id, kadrSize);
	kadrs[KADR_TYPE_SYST] = new CKadrSYS(id, kadrSize);
	kadrs[KADR_TYPE_CAM] = new CKadrCAM(id, kadrSize);
	kadrs[KADR_TYPE_MAP] = new CKadrMAP(id, kadrSize);
	kadrs[KADR_TYPE_RDR] = new CKadrRDR(id, kadrSize);
	curActive = type;
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		if (i != curActive)
			kadrs[i]->SetBlock(true);
	auxKadr = nullptr;
}

CEkranHandler::KadrsAssembly::~KadrsAssembly()
{
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		if (kadrs[i] != nullptr)
			delete kadrs[i];
	if (auxKadr != nullptr)
		delete auxKadr;
}

void CEkranHandler::KadrsAssembly::InvokeAuxKadr(UINT auxId)
{
	assert(auxKadr == nullptr);
	auxKadr = new CBlankAuxKadr(auxId, KADR_SIZE_EIGHTH);
}

void CEkranHandler::KadrsAssembly::InvokeAuxKadr(UINT auxId, KADR_TYPE type)
{
	assert(auxKadr == nullptr);
	switch (type)
	{
	case KADR_TYPE_CAM:
		auxKadr = new CKadrCAM(auxId, KADR_SIZE_EIGHTH);
		break;
	case KADR_TYPE_RDR:
		auxKadr = new CKadrRDR(auxId, KADR_SIZE_EIGHTH);
		break;
	default:
		break;
	}
}

void CEkranHandler::KadrsAssembly::RemoveAuxKadr()
{
	assert(auxKadr != nullptr);
	delete auxKadr;
	auxKadr = nullptr;
}

void CEkranHandler::KadrsAssembly::SwitchKadr(KADR_TYPE type)
{
	bool SOI = kadrs[curActive]->GetSOIStatus();
	kadrs[curActive]->SetBlock(true);
	kadrs[curActive]->SetSOIStatus(false);
	curActive = type;
	kadrs[curActive]->SetBlock(false);
	kadrs[curActive]->SetSOIStatus(SOI);
}

void CEkranHandler::KadrsAssembly::ChangeSize(KADR_SIZE newSize)
{
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		kadrs[i]->ChangeSize(newSize);
}

CEkranHandler::KadrsAssembly* CEkranHandler::KadrsAssembly::ChangePos(UINT newPos)
{
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		kadrs[i]->ChangePos(newPos);
	return this;
}

CEkranHandler::MechMenuAssembly::MechMenuAssembly(UINT id, KADR_TYPE type)
{
	menus[KADR_TYPE_PLD] = new CMechanicMenu(id, KADR_TYPE_PLD);
	menus[KADR_TYPE_SYST] = new CMechanicMenu(id, KADR_TYPE_SYST);
	menus[KADR_TYPE_CAM] = new CMechanicMenu(id, KADR_TYPE_CAM);
	menus[KADR_TYPE_MAP] = new CMechanicMenu(id, KADR_TYPE_MAP);
	menus[KADR_TYPE_RDR] = new CMechanicMenu(id, KADR_TYPE_RDR);
	curActive = type;
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		if (i != curActive)
			menus[i]->Hide(true);
}
CEkranHandler::MechMenuAssembly::~MechMenuAssembly()
{
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		if (menus[i] != nullptr)
			delete menus[i];
}

CEkranHandler::MechMenuAssembly* CEkranHandler::MechMenuAssembly::ChangePos(UINT newPos)
{
	for (int i = 0; i < KADRS_MAX_NUM; i++)
		menus[i]->ChangePos(newPos);
	return this;
}

void CEkranHandler::MechMenuAssembly::SwitchMenu(KADR_TYPE type)
{
	bool SOI = menus[curActive]->GetSOIStatus();
	menus[curActive]->Hide(true);
	menus[curActive]->SetSOIStatus(false);
	curActive = type;
	menus[curActive]->Hide(false);
	menus[curActive]->SetSOIStatus(SOI);
}