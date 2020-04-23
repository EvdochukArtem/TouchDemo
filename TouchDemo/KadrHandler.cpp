#include "KadrHandler.h"
#include "Math.h"

#define KADR_BORDER 20
#define EKRAN_WIDTH (int)(GetSystemMetrics(SM_CXSCREEN) - 2 * KADR_BORDER)
#define EKRAN_HEIGHT (int)(GetSystemMetrics(SM_CYSCREEN) - 2 * KADR_BORDER)

CKadrHandler::CKadrHandler()
{
	UINT cx = KADR_BORDER;
	UINT cy = KADR_BORDER;
	UINT width = EKRAN_WIDTH;
	UINT height = EKRAN_HEIGHT;
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			displayCells[i][j] = NULL;
	displayCells[0][0] = new CKadr(0, FULL, cx, cy, width, height);
}

void CKadrHandler::DivideKadr(UINT kadrID, KADR_SIZE kadrSize)
{
	//UINT row = (kadrID > 3) ? 1 : 0;
	UINT col = (kadrID > 3) ? kadrID - 4 : kadrID;
	delete displayCells[0][col];
	switch (kadrSize)
	{
	case FULL:
	{
		UINT cx = KADR_BORDER;
		UINT cy = KADR_BORDER;
		int a = EKRAN_WIDTH;
		UINT width =  EKRAN_WIDTH/2;
		UINT height = EKRAN_HEIGHT;
		displayCells[0][0] = new CKadr(0, HALF, cx, cy, width, height);
		displayCells[0][2] = new CKadr(2, HALF, cx + width, cy, width, height);
	}
	break;
	case HALF:
	{
		UINT cx = KADR_BORDER + col * (EKRAN_WIDTH / 4);
		UINT cy = KADR_BORDER;
		UINT width = EKRAN_WIDTH / 4;
		UINT height = EKRAN_HEIGHT;
		displayCells[0][col] = new CKadr(col, QUATER, cx, cy, width, height);
		displayCells[0][col] = new CKadr(++col, QUATER, cx + width, cy, width, height);
	}
	break;
	case QUATER:
	{ 
		UINT cx = KADR_BORDER + (col) * (EKRAN_WIDTH / 4);
		UINT cy = KADR_BORDER;
		UINT width = EKRAN_WIDTH / 4;
		UINT height = EKRAN_HEIGHT / 2;
		displayCells[0][col] = new CKadr(col, EIGHTH, cx, cy, width, height);
		displayCells[1][col] = new CKadr(4 + col, EIGHTH, cx, cy + height, width, height);
	}
	break;
	default:
		MessageBox(NULL, L"Invalid kadrSize!", L"Error", MB_OK | MB_ICONERROR);
		break;
	}
}

void CKadrHandler::MergeKadr(UINT kadrID, KADR_SIZE kadrSize, MERGE_DIRECTION mergeDir)
{
	UINT row = (kadrID > 3) ? 1 : 0;
	UINT col = (kadrID > 3) ? kadrID - 4 : kadrID;
	delete displayCells[row][col];
	displayCells[row][col] = NULL;
	switch (kadrSize)
	{
	case FULL:
		return;
		break;
	case HALF:
	{
		UINT cx = KADR_BORDER;
		UINT cy = KADR_BORDER;
		UINT width = EKRAN_WIDTH;
		UINT height = EKRAN_HEIGHT;
		for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (displayCells[i][j] != NULL)
			{
				delete displayCells[i][j];
				displayCells[i][j] = NULL;
			}
		displayCells[0][0] = new CKadr(0, FULL, cx, cy, width, height);
	}
		break;
	case QUATER:
	{
		if (mergeDir == RIGHT)
		{
			//что бы мы расширяя четвертушку в сторону половинного
			//не забыли создать на его месте новую четвертушку
			if (col == 0 || col == 1 && displayCells[0][col + 2] == NULL)
			{
				UINT cx = KADR_BORDER + (col + 2) * (EKRAN_WIDTH / 4);
				UINT cy = KADR_BORDER;
				UINT width = EKRAN_WIDTH / 4;
				UINT height = EKRAN_HEIGHT;
				displayCells[0][col + 2] = new CKadr(col + 2, QUATER, cx, cy, width, height);
			}
			delete displayCells[0][col + 1];
			displayCells[0][col + 1] = NULL;
			if (displayCells[1][col + 1] != NULL)
			{
				delete displayCells[1][col + 1];
				displayCells[1][col + 1] = NULL;
			}
		}
		else
		{	//что бы мы расширяя четвертушку в сторону половинного
			//не забыли создать на его месте новую четвертушку
			if (col == 2 || col == 3 && displayCells[0][col - 2] == NULL)
			{
				UINT cx = KADR_BORDER + (col - 2) * (EKRAN_WIDTH / 4);
				UINT cy = KADR_BORDER;
				UINT width = EKRAN_WIDTH / 4;
				UINT height = EKRAN_HEIGHT;
				displayCells[0][col - 2] = new CKadr(col - 2, QUATER, cx, cy, width, height);
			}
			delete displayCells[0][--col];
			displayCells[0][col] = NULL;
			if (displayCells[1][col] != NULL)
			{
				delete displayCells[1][col];
				displayCells[1][col] = NULL;
			}
		}
		UINT cx;
		if (col == 3)
			cx = KADR_BORDER + (EKRAN_WIDTH / 2);
		else
			cx = KADR_BORDER + col * (EKRAN_WIDTH / 4);
		UINT cy = KADR_BORDER;
		UINT width = EKRAN_WIDTH / 2;
		UINT height = EKRAN_HEIGHT;
		displayCells[0][col] = new CKadr(col, HALF, cx, cy, width, height);
	}
		break;
	case EIGHTH:
	{
		delete displayCells[abs((int)row - 1)][col];
		displayCells[abs((int)row - 1)][col] = NULL;
		UINT cx = KADR_BORDER + (col) * (EKRAN_WIDTH / 4);
		UINT cy = KADR_BORDER;
		UINT width = EKRAN_WIDTH / 4;
		UINT height = EKRAN_HEIGHT;
		displayCells[0][col] = new CKadr(col, QUATER, cx, cy, width, height);
	}
		break;
	default:
		break;
	}
}