#include "StdAfx.h"
#include "DrawEngine.h"
#ifdef DEBUG
#include "Util.h"
#endif

CDrawEngine::CDrawEngine()
{
	backgroundHDC = nullptr;
	tmpHDC = nullptr;
	backgroundBITMAP = nullptr;
	tmpBITMAP = nullptr;
	drawingObjects = nullptr;
}

CDrawEngine::~CDrawEngine()
{
	CleanUp();
	delete drawingObjects;
	drawingObjects = nullptr;
}

BOOL CDrawEngine::Create()
{
	//Создаем все необходиные объекты GDI
	HDC tmp = GetDC(NULL);
	backgroundHDC = CreateCompatibleDC(tmp);
	if (backgroundHDC == nullptr)
		return FALSE;

	backgroundBITMAP = CreateCompatibleBitmap(tmp, X0_PX + WIDTHPX, Y0_PX + HEIGHTPX);
	if (backgroundBITMAP == nullptr)
		return FALSE;

	//Выбираем битмап в контекст фона
	SelectObject(backgroundHDC, backgroundBITMAP);
	SetGraphicsMode(backgroundHDC, GM_ADVANCED);

	drawingObjects = new PriorObjectList();

#ifdef DEBUG
		if (QueryPerformanceFrequency(&counter) == FALSE)
			MessageBox(NULL, _T("Таймер не прошел"), _T(""), MB_OK);
		ZeroMemory(&count, sizeof(count));
#endif
	DeleteDC(tmp);
	return TRUE;
}

BOOL CDrawEngine::CleanUp()
{
	if (backgroundHDC)
	{
		DeleteDC(backgroundHDC);
		backgroundHDC = nullptr;
	}
	if (backgroundBITMAP)
	{
		DeleteObject(backgroundBITMAP);
		backgroundBITMAP = nullptr;
	}
	if (tmpBITMAP)
	{
		DeleteObject(tmpBITMAP);
		tmpBITMAP = nullptr;
	}
	if (tmpHDC)
	{
		DeleteDC(tmpHDC);
		tmpHDC = nullptr;
	}
	
	drawingObjects->Clear();

	return TRUE;
}

void CDrawEngine::AddDrawingObject(CDrawingObject* obj)
{
	if (obj == nullptr)
		return;
	drawingObjects->Add(obj);
#ifdef DEBUG
	drawingObjects->asArray();
#endif
}

void CDrawEngine::DeleteDrawingObject(CDrawingObject* obj)
{
	if (obj == nullptr)
		return;
	drawingObjects->Remove(obj);
#ifdef DEBUG
	drawingObjects->asArray();
#endif
}

void CDrawEngine::UpdateBackground()
{
	drawingObjects->UpdateBackground();
}

void CDrawEngine::Draw(HDC& hdc)
{
	tmpHDC = CreateCompatibleDC(hdc);
	tmpBITMAP = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN));
	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	BitBlt(tmpHDC, 0, 0, GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN), backgroundHDC, 0, 0, SRCCOPY);
	
	drawingObjects->Draw(tmpHDC);
	
#ifdef DEBUG
	if (GESTURE_EMULATOR.pixelCheck)
	{
		HPEN oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.RedPen);
		int oldAlign = SetTextAlign(tmpHDC, TA_LEFT|TA_TOP);
		int i = 0;
		for (int a = X0_PX; a < X0_PX + WIDTHPX; a += TO_PIXEL(10))
		{
			if (a % TO_PIXEL(50) == 0)
			{
				HFONT oldFont = (HFONT)SelectObject(tmpHDC, DRAW_KIT.Arial10b);
				COLORREF oldColor = SetTextColor(tmpHDC, DRAW_KIT.GetRedColor());
				SetBkMode(tmpHDC, TRANSPARENT);
				TCHAR buf [10];
				_stprintf_s(buf, _T("%d"), a);
				i += TO_PIXEL(50);
				int c = TO_PIXEL(20);
				int cc = TO_PIXEL(5);
				TextOut(tmpHDC, a, Y0_PX - TO_PIXEL(20), buf, (int)_tcslen(buf));
				TextOut(tmpHDC, a, Y0_PX + HEIGHTPX + TO_PIXEL(5), buf, (int)_tcslen(buf));
				SelectObject(tmpHDC, oldFont);
				SetTextColor(tmpHDC, oldColor);
				SetBkMode(tmpHDC, OPAQUE);
			}
			MoveToEx(tmpHDC, a, Y0_PX, NULL);
			LineTo(tmpHDC, a, Y0_PX + HEIGHTPX);	
		}
		for (int a = Y0_PX; a < Y0_PX + HEIGHTPX; a += TO_PIXEL(10))
		{
			MoveToEx(tmpHDC, X0_PX, a, NULL);
			LineTo(tmpHDC, X0_PX + WIDTHPX, a);	
		}
		SelectObject(tmpHDC, oldPen);
		SetTextAlign(tmpHDC, oldAlign);
	}
	CountFrames(tmpHDC);
#endif
	BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN), tmpHDC, 0, 0, SRCCOPY);
	
	SelectObject(tmpHDC, hOld);

	DeleteDC(tmpHDC);
	DeleteObject(tmpBITMAP);
	DeleteObject(hOld);
}

CDrawingObject* CDrawEngine::getObjectInPoint(POINT pt)
{
	return drawingObjects->getObjectInPoint(pt);
}

std::vector<CDrawingObject*> CDrawEngine::getAllObjectsInPoint(POINT pt)
{
	return drawingObjects->getAllObjectsInPoint(pt);
}

#ifdef DEBUG
void CDrawEngine::CountFrames(HDC& hdc)
{
	//Считаем кадры в секунду
	QueryPerformanceCounter(&count1);
	if ((count1.QuadPart-count.QuadPart) < counter.QuadPart)
		fps++;
	else
	{
		f = fps;
		fps = 0;
		count = count1;
	}
	//Отрисовываем счетчик кадров в секунду
	TCHAR buf [32];
	HFONT oldFont = (HFONT)SelectObject(hdc, DRAW_KIT.Arial12);
	UINT oldTextAlign = SetTextAlign(hdc, TA_TOP|TA_LEFT);
	_stprintf_s(buf, _T("FPS = %d"), f);
	TextOut(hdc, TO_PIXEL(10), TO_PIXEL(10), buf, (int)_tcslen(buf));
	SelectObject(hdc, oldFont);
	SetTextAlign(hdc, oldTextAlign);
}
#endif


CDrawEngine::PriorObjectList::PriorObjectList()
{
	head = nullptr;
}

void CDrawEngine::PriorObjectList::Add(CDrawingObject* obj)
{
	if (obj == nullptr)
		return;
	Node* newNode = new Node;
	newNode->obj = obj;
	newNode->next = nullptr;
	if (isEmpty())
		head = newNode;
	else {
		Node* prev = nullptr;
		Node* cur = head;
		while (cur->next != nullptr && cur->obj->GetPrior() < obj->GetPrior())
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur->obj->GetPrior() < obj->GetPrior())
		{
			newNode->next = cur->next;
			cur->next = newNode;
		} else {
			if (prev == nullptr)
			{
				newNode->next = head;
				head = newNode;
			} else {
				prev->next = newNode;
				newNode->next = cur;
			}
		}
	}
}

#ifdef DEBUG
void CDrawEngine::PriorObjectList::asArray()
{
	arr.clear();
	Node* cur = head;
	while (cur != nullptr)
	{
		arr.push_back(cur->obj);
		cur = cur->next;
	}
}
#endif

BOOL CDrawEngine::PriorObjectList::Remove(CDrawingObject* obj)
{
	if (isEmpty())
		return false;
	Node* tmp = head;
	if (head->obj == obj)
	{
		head = head->next;
		delete tmp;
		return true;
	}
	Node* prev = head;
	while (tmp != nullptr) 
		if (tmp->obj == obj)
		{
			prev->next = tmp->next;
			delete tmp;
			return true;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
	return false;
}

void CDrawEngine::PriorObjectList::Clear()
{
	if (isEmpty())
		return;
	Node* tmp = head;
	while (tmp->next != nullptr)
	{
		head = tmp;
		tmp = tmp->next;
		delete head;
	}
	delete tmp;
	head = nullptr;
}

void CDrawEngine::PriorObjectList::Draw(HDC& hdc)
{
	if (isEmpty())
		return;
	Node* cur = head;
	while (cur != nullptr)
	{
		cur->obj->Draw(hdc);
		cur = cur->next;
	}
}

void CDrawEngine::PriorObjectList::UpdateBackground()
{
	if (isEmpty())
		return;
	Node* cur = head;
	while (cur != nullptr)
	{
		cur->obj->DrawBackground();
		cur = cur->next;
	}
}

CDrawingObject* CDrawEngine::PriorObjectList::getObjectInPoint(POINT pt)
{
	if (isEmpty())
		return nullptr;
	Node* cur = head;
	while (cur != nullptr)
	{
		if (cur->obj->PointIsMine(pt))
			return cur->obj;
		cur = cur->next;
	}
	return nullptr;
}

std::vector<CDrawingObject*> CDrawEngine::PriorObjectList::getAllObjectsInPoint(POINT pt)
{
	foundObj.clear();
	if (isEmpty())
		return foundObj;
	Node* cur = head;
	while (cur != nullptr)
	{
		if (cur->obj->PointIsMine(pt))
			foundObj.push_back(cur->obj);
		cur = cur->next;
	}
	return foundObj;
}