#include "DrawEngine.h"

CDrawEngine::CDrawEngine()
{
	backgroundHDC = NULL;
	tmpHDC = NULL;
	backgroundBITMAP = NULL;
	tmpBITMAP = NULL;
}

CDrawEngine::~CDrawEngine()
{
	if (backgroundHDC)
	{
		::DeleteObject(backgroundBITMAP);
		backgroundBITMAP = NULL;
	}
	if (backgroundBITMAP)
	{
		::DeleteDC(backgroundHDC);
		backgroundHDC = NULL;
	}
	if (tmpBITMAP)
	{
		::DeleteObject(tmpBITMAP);
		tmpBITMAP = NULL;
	}
	if (tmpHDC)
	{
		::DeleteDC(tmpHDC);
		tmpHDC = NULL;
	}
}

BOOL CDrawEngine::Create()
{
	//Создаем все необходиные объекты GDI
	backgroundHDC = ::CreateCompatibleDC(::GetDC(NULL));
	if (backgroundHDC == NULL)
		return FALSE;

	backgroundBITMAP = ::CreateCompatibleBitmap(::GetDC(NULL), WIDTHPX, HEIGHTPX);
	if (backgroundBITMAP == NULL)
		return FALSE;

	//Выбираем битмап в конткст фона
	::SelectObject(backgroundHDC, backgroundBITMAP);
	::SetGraphicsMode(backgroundHDC, GM_ADVANCED);

	return TRUE;
}

void CDrawEngine::AddDrawingObject(CDrawingObject* obj)
{
	if (obj == NULL)
		return;
	drawingObjects.push_back(obj);
}

void CDrawEngine::DeleteDrawingObject(CDrawingObject* obj)
{
	if (obj == NULL)
		return;
	std::vector<CDrawingObject*>::iterator it = std::find(drawingObjects.begin(), drawingObjects.end(), obj);
	//std::vector<CDrawingObject*>::difference_type index = std::distance(drawingObjects.begin(), it);
	drawingObjects.erase(it);
}

void CDrawEngine::UpdateBackground()
{
	for (CDrawingObject* obj : drawingObjects)
		obj->DrawBackground();
}

void CDrawEngine::Draw(HDC hdc)
{
	tmpHDC = CreateCompatibleDC(hdc);
	tmpBITMAP = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	BitBlt(tmpHDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), backgroundHDC, 0, 0, SRCCOPY);

	for (CDrawingObject* obj : drawingObjects)
		obj->Draw(tmpHDC);
	
	BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), tmpHDC, 0, 0, SRCCOPY);
	
	SelectObject(tmpHDC, hOld);

	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
	DeleteObject(hOld);
}