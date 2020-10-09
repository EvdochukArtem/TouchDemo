#include "StdAfx.h"
#include "EkranHandler.h"

CEkranHandler::CEkranHandler()
{
	curSOI = 1;
}

BOOL CEkranHandler::Create()
{
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		displayCells[0][i] = new CKadr(i, QUATER);
		displayCells[1][i] = nullptr;
		mechanicMenu[i] = new CMechanicMenu(i);
		frames[i] = new CFrame(i, mechanicMenu[i]->GetActiveButtonPosition(), QUATER);
	}
	displayCells[0][curSOI]->ChangeSOIStatus();
	mechanicMenu[curSOI]->ChangeSOIStatus();
	frames[curSOI]->ChangeSOIStatus();
	//displayCells[0][0] = new CKadrPIL(0, QUATER);
	//displayCells[0][1] = new CKadrMASD(1, QUATER);
	//displayCells[0][2] = new CKadrTSD(2, QUATER);
	//displayCells[0][3] = new CKadrSYS(3, QUATER);
	return TRUE;
}

void CEkranHandler::SetSOI(POINT pt)
{
	if (displayCells[0][curSOI] != nullptr)
		displayCells[0][curSOI]->ChangeSOIStatus();
	else
		displayCells[0][curSOI - 1]->ChangeSOIStatus();
	if (frames[curSOI] != nullptr)
		frames[curSOI]->ChangeSOIStatus();
	else
		frames[curSOI - 1]->ChangeSOIStatus();
	mechanicMenu[curSOI]->ChangeSOIStatus();
	for (int i = 0; i < DISPLAY_COLS; i++)
		if (mechanicMenu[i]->PointIsMine(pt))
		{
			curSOI = i;
			break;
		}
	if (displayCells[0][curSOI] != nullptr)
		displayCells[0][curSOI]->ChangeSOIStatus();
	else
		displayCells[0][curSOI - 1]->ChangeSOIStatus();
	if (frames[curSOI] != nullptr)
		frames[curSOI]->ChangeSOIStatus();
	else
		frames[curSOI - 1]->ChangeSOIStatus();
	mechanicMenu[curSOI]->ChangeSOIStatus();
}

void CEkranHandler::SetSOI(UINT newSOI)
{
	if (displayCells[0][curSOI] != nullptr)
		displayCells[0][curSOI]->ChangeSOIStatus();
	if (frames[curSOI] != nullptr)
		frames[curSOI]->ChangeSOIStatus();
	mechanicMenu[curSOI]->ChangeSOIStatus();
	
	curSOI = newSOI;
			
	displayCells[0][curSOI]->ChangeSOIStatus();
	frames[curSOI]->ChangeSOIStatus();
	mechanicMenu[curSOI]->ChangeSOIStatus();
}

void CEkranHandler::SwipeMenus(UINT leftOne)
{
	CMechanicMenu* tmp = mechanicMenu[leftOne];
	mechanicMenu[leftOne] = mechanicMenu[leftOne + 1]->ChangePos(leftOne);
	mechanicMenu[leftOne + 1] = tmp->ChangePos(leftOne + 1);
	if (curSOI == leftOne)
		curSOI = leftOne + 1;
	else if (curSOI == leftOne + 1)
		curSOI = leftOne;
}

void CEkranHandler::DivideKadr(UINT kadrID, KADR_SIZE kadrSize, SWIPE_DIRECTION swipeDir)
{
	UINT col = kadrID % 4;
	switch (kadrSize)
	{
	case FULL:
	{
		/*delete displayCells[0][col];
		displayCells[0][0] = new CKadr(0, HALF);
		displayCells[0][2] = new CKadr(2, HALF);*/
	}
	break;
	case HALF:
	{
		if (swipeDir == RIGHT)
		{
			displayCells[0][col + 1] = displayCells[0][col]->ChangePos(col + 1);
			displayCells[0][col + 1]->ChangeSize(QUATER);
			displayCells[0][col] = new CKadr(col, QUATER);
			frames[col + 1] = frames[col]->ChangePos(col + 1);
			frames[col + 1]->ChangeSize(QUATER);
			frames[col] = new CFrame(col, mechanicMenu[col]->GetActiveButtonPosition(), QUATER);
			if (!mechanicMenu[col]->GetBlockStatus())
				SwipeMenus(col);
			mechanicMenu[col]->SetBlock(false);
		} else {
			displayCells[0][col]->ChangeSize(QUATER);
			displayCells[0][col + 1] = new CKadr(col + 1, QUATER);
			frames[col]->ChangeSize(QUATER);
			frames[col + 1] = new CFrame(col + 1, mechanicMenu[col + 1]->GetActiveButtonPosition(), QUATER);
			if (mechanicMenu[col]->GetBlockStatus())
				SwipeMenus(col);
			mechanicMenu[col + 1]->SetBlock(false);
		}
	}
	break;
	case QUATER:
	{
		displayCells[0][col]->ChangeSize(EIGHTH);
		frames[col]->ChangeSize(EIGHTH);
		displayCells[1][col] = new CKadr(4 + col, EIGHTH);
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
	switch (kadrSize)
	{
	case FULL:
		return;
		break;
	case HALF:
	/*{
		delete displayCells[row][col];
		displayCells[row][col] = nullptr;
		for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
		if (displayCells[i][j] != nullptr)
		{
			delete displayCells[i][j];
			displayCells[i][j] = nullptr;
			mechanicMenu[j]->SetBlock(true);
		}
		displayCells[0][0] = new CKadr(0, FULL);
		mechanicMenu[col]->SetBlock(false);
	}*/
		return;
		break;
	case QUATER:
	{
		if (swipeDir == RIGHT)
		{
			if (col == 3)
				return;
			else
			{
				if (col < 2 && displayCells[0][col + 2] == nullptr)
				{
					displayCells[0][col + 2] = displayCells[0][col + 1]->ChangePos(col + 2);
					displayCells[0][col + 1]->ChangeSize(QUATER);
					displayCells[0][col + 1] = nullptr;
					frames[col + 2] = frames[col + 1]->ChangePos(col + 2);
					frames[col + 2]->ChangeSize(QUATER);
					frames[col + 1] = nullptr;
					if (mechanicMenu[col + 2]->GetBlockStatus())
						SwipeMenus(col + 1);
					if (col + 1 == curSOI)
						SetSOI(col + 2);
				} else {
					delete displayCells[0][col + 1];
					displayCells[0][col + 1] = nullptr;
					delete displayCells[1][col + 1];
					displayCells[1][col + 1] = nullptr;
					delete frames[col + 1];
					frames[col + 1] = nullptr;
					mechanicMenu[col + 1]->SetBlock(true);
					if (col + 1 == curSOI)
						SetSOI(col);
				}
				displayCells[0][col]->ChangeSize(HALF);
				frames[col]->ChangeSize(HALF);
			}
		}
		else
		{
			if (col == 0)
				return;
			else
			{
				if (displayCells[0][col - 1] == nullptr)
				{
					displayCells[0][col - 2]->ChangeSize(QUATER);
					frames[col - 2]->ChangeSize(QUATER);
					if (mechanicMenu[col - 2]->GetBlockStatus())
						SwipeMenus(col - 2);
					if (curSOI == col - 1)
						SetSOI(col - 2);
				}
				else {
					delete displayCells[0][col - 1];
					displayCells[0][col - 1] = nullptr;
					delete displayCells[1][col - 1];
					displayCells[1][col - 1] = nullptr;
					delete frames[col - 1];
					frames[col - 1] = nullptr;
					mechanicMenu[col - 1]->SetBlock(true);
					if (curSOI == col - 1)
						SetSOI(col);
				}
				displayCells[0][col - 1] = displayCells[0][col]->ChangePos(col - 1);
				displayCells[0][col]->ChangeSize(HALF);
				frames[col - 1] = frames[col]->ChangePos(col - 1);
				frames[col]->ChangeSize(HALF);
				displayCells[0][col] = nullptr;
				frames[col] = nullptr;
			}
		}
	}
		break;
	case EIGHTH:
	{
		if (row == 1)
		{
			delete displayCells[0][col];
			displayCells[0][col] = nullptr;
		} else
			delete displayCells[1][col];
		displayCells[0][col] = displayCells[row][col]->ChangePos(col);
		displayCells[row][col]->ChangeSize(QUATER);
		frames[col]->ChangeSize(QUATER);
		displayCells[1][col] = nullptr;
	}
		break;
	default:
		break;
	}
}