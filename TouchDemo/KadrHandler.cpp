#include "KadrHandler.h"

BOOL CKadrHandler::Create()
{
	for (int i = 0; i < DISPLAY_COLS; i++)
	{
		displayCells[0][i] = new CKadr(i, QUATER);
		displayCells[1][i] = NULL;
		mechanicMenu[i] = new CMechanicMenu(i, 25);
	}
	return TRUE;
}

void CKadrHandler::DivideKadr(UINT kadrID, KADR_SIZE kadrSize)
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
	//ClearLines();
}

void CKadrHandler::MergeKadr(UINT kadrID, KADR_SIZE kadrSize, MERGE_DIRECTION mergeDir)
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
		/*UINT cx;
		if (mergeDir == RIGHT)
		{
			delete displayCells[0][col + 1];
			displayCells[0][col + 1] = NULL;
				if (displayCells[1][col + 1] != NULL)
				{
					delete displayCells[1][col + 1];
					displayCells[1][col + 1] = NULL;
				}
			//что бы мы расширяя четвертушку в сторону половинного
			//не забыли создать на его месте новую четвертушку
			if ((col == 0 || col == 1) && displayCells[0][col + 2] == NULL)
			{
				cx = KADR_BORDER_X + (col + 2) * (KADR_WORK_AREA_WIDTH / 4);
				UINT cy = KADR_BORDER_Y;
				UINT width = KADR_WORK_AREA_WIDTH / 4;
				UINT height = KADR_WORK_AREA_HEIGHT;
				displayCells[0][col + 2] = new CKadr(col + 2, QUATER, cx, cy, width, height);
			}
			if (col == 3)
				cx = KADR_BORDER_X + (KADR_WORK_AREA_WIDTH / 2);
			else
				cx = KADR_BORDER_X + col * (KADR_WORK_AREA_WIDTH / 4);
		}
		else
		{	//что бы мы расширяя четвертушку в сторону половинного
			//не забыли создать на его месте новую четвертушку
			if ((col == 2 || col == 3) && displayCells[0][col - 1] == NULL)
			{
				delete displayCells[0][col - 2];
				displayCells[0][col - 2] = NULL;
				cx = KADR_BORDER_X + (col - 2) * (KADR_WORK_AREA_WIDTH / 4);
				UINT cy = KADR_BORDER_Y;
				UINT width = KADR_WORK_AREA_WIDTH / 4;
				UINT height = KADR_WORK_AREA_HEIGHT;
				displayCells[0][col - 2] = new CKadr(col - 2, QUATER, cx, cy, width, height);
			}
			else
			{
				delete displayCells[0][col - 1];
				displayCells[0][col] = NULL;
				if (displayCells[1][col - 1] != NULL)
				{
					delete displayCells[1][col - 1];
					displayCells[1][col - 1] = NULL;
				}
			}
			col--;
			if (col == 2)
				cx = KADR_BORDER_X + (KADR_WORK_AREA_WIDTH / 2);
			else
				cx = KADR_BORDER_X + col * (KADR_WORK_AREA_WIDTH / 4);
		}
		UINT cy = KADR_BORDER_Y;
		UINT width = KADR_WORK_AREA_WIDTH / 2;
		UINT height = KADR_WORK_AREA_HEIGHT;
		displayCells[0][col] = new CKadr(col, HALF, cx, cy, width, height);*/
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
	//ClearLines();
}

/*void CKadrHandler::StartLine(const POINT firstTouchCoord, const bool singleTouch)
{
	startLine = firstTouchCoord;
	multiLine = singleTouch;
}

void CKadrHandler::FinishLine(const POINT lastTouchCoord)
{
	endLine = lastTouchCoord;
}

void CKadrHandler::DrawLine(HDC hdc)
{
	if (!multiLine)
		return;
	MoveToEx(hdc, startLine.x, startLine.y, NULL);
	LineTo(hdc, endLine.x, endLine.y);
	MoveToEx(hdc, startLine.x, startLine.y + 5, NULL);
	LineTo(hdc, endLine.x, endLine.y + 5);
}

void CKadrHandler::ClearLines()
{
	startLine.x = NULL;
	startLine.y = NULL;
	endLine.x = NULL;
	endLine.y = NULL;
	multiLine = false;
}

void CKadrHandler::DrawBackground()
{
	HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, WhiteBrush);
	
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
		{
			if (getDisplayCell(i, j) != NULL)
				getDisplayCell(i, j)->Paint(hdc);
			mechanicMenu[j]->DrawBackground(hdc);
		}

	SelectObject(hdc, oldBrush);
	DeleteObject(WhiteBrush);
}

void CKadrHandler::Draw(HDC hdc)
{
	for (int i = 0; i < DISPLAY_ROWS; i++)
		for (int j = 0; j < DISPLAY_COLS; j++)
			if (getDisplayCell(i, j) != NULL)
				getDisplayCell(i, j)->Draw(hdc);
}*/