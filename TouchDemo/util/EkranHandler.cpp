#include "StdAfx.h"
#include "EkranHandler.h"

BOOL CEkranHandler::Create()
{
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		displayCells[0][i] = new CKadr(i, QUATER);
		displayCells[1][i] = NULL;
		mechanicMenu[i] = new CMechanicMenu(i);
	}
	curSOI = DISPLAY_COLS;
	return TRUE;
}

void CEkranHandler::SetSOI(UINT newSOI)
{
	if (curSOI < DISPLAY_COLS)
	{
		//Сброс текущего СОИ
	}
	curSOI = newSOI;
}

void CEkranHandler::DivideKadr(UINT kadrID, KADR_SIZE kadrSize)
{
	UINT col = kadrID % 4;
	delete displayCells[0][col];
	switch (kadrSize)
	{
	case FULL:
	{
		displayCells[0][0] = new CKadr(0, HALF);
		displayCells[0][2] = new CKadr(2, HALF);
	}
	break;
	case HALF:
	{
		displayCells[0][col] = new CKadr(col, QUATER);
		displayCells[0][col] = new CKadr(++col, QUATER);
	}
	break;
	case QUATER:
	{
		displayCells[0][col] = new CKadr(col, EIGHTH);
		displayCells[1][col] = new CKadr(4 + col, EIGHTH);
	}
	break;
	default:
		MessageBox(NULL, L"Invalid kadrSize!", L"Error", MB_OK | MB_ICONERROR);
		break;
	}
}

void CEkranHandler::MergeKadr(UINT kadrID, KADR_SIZE kadrSize, MERGE_DIRECTION mergeDir)
{
	UINT row = kadrID / 4;
	UINT col = kadrID % 4;
	delete displayCells[row][col];
	displayCells[row][col] = NULL;
	switch (kadrSize)
	{
	case FULL:
		return;
		break;
	case HALF:
	{
		for (int i = 0; i < DISPLAY_ROWS; i++)
			for (int j = 0; j < DISPLAY_COLS; j++)
				if (displayCells[i][j] != NULL)
				{
					delete displayCells[i][j];
					displayCells[i][j] = NULL;
				}
		displayCells[0][0] = new CKadr(0, FULL);
	}
	break;
	case QUATER:
	{
		if (mergeDir == RIGHT)
		{
			if (col == 3)
				displayCells[0][col] = new CKadr(3, QUATER);
			else
			{
				delete displayCells[0][col + 1];
				displayCells[0][col + 1] = NULL;
				delete displayCells[1][col + 1];
				displayCells[1][col + 1] = NULL;
				if (col < 2 && displayCells[0][col + 2] == NULL)
					displayCells[0][col + 2] = new CKadr(col + 2, QUATER);
				displayCells[0][col] = new CKadr(col, HALF);
			}
		}
		else
		{
			if (col == 0)
				displayCells[0][col] = new CKadr(0, QUATER);
			else
			{
				if (displayCells[0][col - 1] == NULL)
				{
					delete displayCells[0][col - 2];
					displayCells[0][col - 2] = NULL;
					displayCells[0][col - 2] = new CKadr(col - 2, QUATER);
				}
				else {
					delete displayCells[0][col - 1];
					displayCells[0][col - 1] = NULL;
					delete displayCells[1][col - 1];
					displayCells[1][col - 1] = NULL;
				}
				displayCells[0][col - 1] = new CKadr(col - 1, HALF);
			}
		}
	}
	break;
	case EIGHTH:
	{
		delete displayCells[abs((int)row - 1)][col];
		displayCells[abs((int)row - 1)][col] = NULL;
		displayCells[0][col] = new CKadr(col, QUATER);
	}
	break;
	default:
		break;
	}
}