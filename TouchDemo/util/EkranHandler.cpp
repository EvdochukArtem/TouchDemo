#include "StdAfx.h"
#include "EkranHandler.h"

CEkranHandler::CEkranHandler()
{
	curSOI = 1;
}

BOOL CEkranHandler::Create()
{
	kadrs[0][0] = new CKadrPIL(0, QUARTER);
	kadrs[0][1] = new CKadrCAM(1, QUARTER);
	kadrs[0][2] = new CKadrMAP(2, QUARTER);
	kadrs[0][3] = new CKadrSYS(3, QUARTER);
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		//kadrs[0][i] = new CKadr(i, QUARTER);
		kadrs[1][i] = nullptr;
		mechanicMenu[i] = new CMechanicMenu(i, kadrs[0][i]->GetKadrType());
		frames[i] = new CFrame(i, mechanicMenu[i]->GetActiveButtonPosition(), QUARTER);
	}
	kadrs[0][curSOI]->SetSOIStatus(true);
	mechanicMenu[curSOI]->SetSOIStatus(true);
	frames[curSOI]->SetSOIStatus(true);
	return TRUE;
}

void CEkranHandler::SetSOI(POINT pt)
{
	if (kadrs[0][curSOI]->GetBlockStatus() == false)
		kadrs[0][curSOI]->SetSOIStatus(false);
	else
		kadrs[0][curSOI - 1]->SetSOIStatus(false);

	if (frames[curSOI]->GetBlockStatus() == false)
		frames[curSOI]->SetSOIStatus(false);
	else
		frames[curSOI - 1]->SetSOIStatus(false);
	mechanicMenu[curSOI]->SetSOIStatus(false);

	curSOI = FindMechMenu(pt);

	if (kadrs[0][curSOI]->GetBlockStatus() == false)
		kadrs[0][curSOI]->SetSOIStatus(true);
	else
		kadrs[0][curSOI - 1]->SetSOIStatus(true);

	if (frames[curSOI]->GetBlockStatus() == false)
		frames[curSOI]->SetSOIStatus(true);
	else
		frames[curSOI - 1]->SetSOIStatus(true);
	mechanicMenu[curSOI]->SetSOIStatus(true);
}

void CEkranHandler::SetSOI(UINT newSOI)
{
	kadrs[0][curSOI]->SetSOIStatus(false);
	frames[curSOI]->SetSOIStatus(false);
	mechanicMenu[curSOI]->SetSOIStatus(false);
	
	curSOI = newSOI;
			
	kadrs[0][curSOI]->SetSOIStatus(true);
	frames[curSOI]->SetSOIStatus(true);
	mechanicMenu[curSOI]->SetSOIStatus(true);
}

void CEkranHandler::SwapMenus(UINT leftOne)
{
	CMechanicMenu* tmp = mechanicMenu[leftOne];
	mechanicMenu[leftOne] = mechanicMenu[leftOne + 1]->ChangePos(leftOne);
	mechanicMenu[leftOne + 1] = tmp->ChangePos(leftOne + 1);
	if (curSOI == leftOne)
		curSOI = leftOne + 1;
	else if (curSOI == leftOne + 1)
		curSOI = leftOne;
}

void CEkranHandler::SwapKadr(UINT leftOne)
{
	CKadr* tmp = nullptr;
	tmp = kadrs[0][leftOne];
	kadrs[0][leftOne] = kadrs[0][leftOne + 1]->ChangePos(leftOne);
	kadrs[0][leftOne + 1] = tmp->ChangePos(leftOne + 1);
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
	mechanicMenu[col]->DisableKadrTypeSelection();
	frames[col]->DisableKadrTypeSelection();
	if (swipeDir == LEFT && col > 0 && kadrSize != QUARTER)
	{
		mechanicMenu[col - 1]->DisableKadrTypeSelection();
		frames[col - 1]->DisableKadrTypeSelection();
	}
	if (swipeDir == RIGHT && col < 3 && kadrSize != QUARTER)
	{
		mechanicMenu[col + 1]->DisableKadrTypeSelection();
		frames[col + 1]->DisableKadrTypeSelection();
	}
	switch (kadrSize)
	{
	case HALF:
	{
		if (swipeDir == RIGHT)
		{
			kadrs[0][col]->ChangeSize(QUARTER);
			SwapKadr(col);
			frames[col]->ChangeSize(QUARTER);
			SwapFrames(col);
			if (!mechanicMenu[col]->GetBlockStatus())
				SwapMenus(col);
			mechanicMenu[col]->SetBlock(false, swipeDir);
			frames[col]->SetBlock(false);
			kadrs[0][col]->SetBlock(false);
		} else {
			kadrs[0][col]->ChangeSize(QUARTER);
			frames[col]->ChangeSize(QUARTER);
			if (mechanicMenu[col]->GetBlockStatus())
				SwapMenus(col);
			mechanicMenu[col + 1]->SetBlock(false, swipeDir);
			frames[col + 1]->SetBlock(false);
			kadrs[0][col + 1]->SetBlock(false);
		}
	}
	break;
	case QUARTER:
	{
		kadrs[0][col]->ChangeSize(EIGHTH);
		frames[col]->ChangeSize(EIGHTH);
		kadrs[1][col] = new CKadr(4 + col, EIGHTH);
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
	mechanicMenu[col]->DisableKadrTypeSelection();
	if (swipeDir == LEFT && col > 0)
		mechanicMenu[col - 1]->DisableKadrTypeSelection();
	if (swipeDir == RIGHT && col < 3)
		mechanicMenu[col + 1]->DisableKadrTypeSelection();
	if (row == 0 && kadrSize != EIGHTH)
	{
		frames[col]->DisableKadrTypeSelection();
		if (swipeDir == LEFT && col > 0)
			frames[col - 1]->DisableKadrTypeSelection();
		if (swipeDir == RIGHT && col < 3)
			frames[col + 1]->DisableKadrTypeSelection();
	}
	switch (kadrSize)
	{
	case HALF:
		break;
	case QUARTER:
	{
		if (swipeDir == RIGHT)
			RightMerge(swipeDir, col);
		else 
			LeftMerge(swipeDir, col);
	}
		break;
	case EIGHTH:
	{
		kadrs[0][col]->ChangeSize(QUARTER);
		frames[col]->ChangeSize(QUARTER);
		delete kadrs[1][col];
		kadrs[1][col] = nullptr;
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
		if (col < 2 && kadrs[0][col + 2]->GetBlockStatus())	//когда кадр, в который мы собираемся расшириться, 
		{															//является половинкой (HALF) делаем его четвертинкой
			kadrs[0][col + 1]->ChangeSize(QUARTER);
			SwapKadr(col + 1);
			frames[col + 1]->ChangeSize(QUARTER);
			SwapFrames(col + 1);
			if (!mechanicMenu[col + 1]->GetBlockStatus())	
				SwapMenus(col + 1);
		} else {
			kadrs[0][col + 1]->SetBlock(true);	//блокировка соседнего кадра
			if (kadrs[1][col + 1] != nullptr)
				MergeKadr(col + 1, EIGHTH, swipeDir);
			frames[col + 1]->SetBlock(true);
			mechanicMenu[col + 1]->SetBlock(true, swipeDir);
			if (col + 1 == curSOI)
				SetSOI(col);
		}
		kadrs[0][col]->ChangeSize(HALF);
		frames[col]->ChangeSize(HALF);
	}
}

void CEkranHandler::LeftMerge(SWIPE_DIRECTION swipeDir, UINT col)
{
	if (col == 0)
		return;
	else
	{
		if (kadrs[0][col - 1]->GetBlockStatus())		//когда кадр, в который мы собираемся расшириться, 
		{													//является половинкой (HALF) делаем его четвертинкой
			kadrs[0][col - 2]->ChangeSize(QUARTER);
			frames[col - 2]->ChangeSize(QUARTER);
			if (mechanicMenu[col - 2]->GetBlockStatus())
				SwapMenus(col - 2);
		} else {
			if (curSOI == col - 1)
				SetSOI(col);
			if (kadrs[1][col - 1] != nullptr)
				MergeKadr(col - 1, EIGHTH, swipeDir);
		}
		kadrs[0][col]->ChangeSize(HALF);
		frames[col]->ChangeSize(HALF);
		SwapKadr(col - 1);
		SwapFrames(col - 1);
		kadrs[0][col]->SetBlock(true);
		frames[col]->SetBlock(true);
		mechanicMenu[col - 1]->SetBlock(true, swipeDir);
	}
}

UINT CEkranHandler::FindFrame(POINT pt)
{
	for (int i = 0; i < DISPLAY_COLS; i++)
		if (frames[i]->PointIsMine(pt))
			return i;
	return -1;
}

UINT CEkranHandler::FindMechMenu(POINT pt)
{
	for (int i = 0; i < DISPLAY_COLS; i++)
		if (mechanicMenu[i]->PointIsMine(pt))
			return i;
	return -1;
}

std::pair<UINT, UINT> CEkranHandler::FindKadr(POINT pt)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (kadrs[i][j] != nullptr && kadrs[i][j]->PointIsMine(pt))
				return std::make_pair(i, j);
	return std::make_pair(-1, -1);
}

void CEkranHandler::ProcessCommand(EKRAN_HANDLER_COMMANDS cmd, POINT pt)
{
	switch (cmd)
	{
	case ENABLE_KADR_TYPE_SELECTION:
		{
			int curCol = FindMechMenu(pt);
			mechanicMenu[curCol]->EnableKadrTypeSelection();
			frames[curCol]->EnableKadrTypeSelection();
		}
		break;
	case DISABLE_KADR_TYPE_SELECTION:
		{
			int curCol = FindMechMenu(pt);
			mechanicMenu[curCol]->DisableKadrTypeSelection();
			frames[curCol]->DisableKadrTypeSelection();
		}
		break;
	case SWITCH_PLD:
		SwitchKadr(PLD, pt);
		break;
	case SWITCH_SYST:
		SwitchKadr(SYST, pt);
		break;
	case SWITCH_CAM:
		SwitchKadr(CAM, pt);
		break;
	case SWITCH_MAP:
		SwitchKadr(MAP, pt);
		break;
	case SWITCH_RDR:
		SwitchKadr(RDR, pt);
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
		rowAndCol = FindKadr(pt); // значит команда пришла от нижней восьмушки и мех меню переключать не надо
	else
		if (kadrs[0][menuCol]->GetBlockStatus())
			rowAndCol.second = menuCol - 1;
		else
			rowAndCol.second = menuCol;

	size = kadrs[rowAndCol.first][rowAndCol.second]->GetKadrSize();

	if (rowAndCol.first == 0)
	{
		delete mechanicMenu[menuCol];
		delete kadrs[0][rowAndCol.second];
	}
	else
		delete kadrs[1][rowAndCol.second];
	
	switch (type)
	{
	case PLD:
		kadrs[rowAndCol.first][rowAndCol.second] = new CKadrPIL(4*rowAndCol.first + rowAndCol.second, size);
		break;
	case SYST:
		kadrs[rowAndCol.first][rowAndCol.second] = new CKadrSYS(4*rowAndCol.first + rowAndCol.second, size);
		break;
	case CAM:
		kadrs[rowAndCol.first][rowAndCol.second] = new CKadrCAM(4*rowAndCol.first + rowAndCol.second, size);
		break;
	case MAP:
		kadrs[rowAndCol.first][rowAndCol.second] = new CKadrMAP(4*rowAndCol.first + rowAndCol.second, size);
		break;
	case RDR:
		kadrs[rowAndCol.first][rowAndCol.second] = new CKadrRDR(4*rowAndCol.first + rowAndCol.second, size);
		break;
	default:
		break;
	}
	
	if (rowAndCol.first == 0)
	{
		mechanicMenu[menuCol] = new CMechanicMenu(menuCol, kadrs[0][rowAndCol.second]->GetKadrType());
		frames[rowAndCol.second]->DisableKadrTypeSelection();
	}
}