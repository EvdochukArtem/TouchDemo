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
	if (backgroundHDC)
	{
		::DeleteObject(backgroundBITMAP);
		backgroundBITMAP = nullptr;
	}
	if (backgroundBITMAP)
	{
		::DeleteDC(backgroundHDC);
		backgroundHDC = nullptr;
	}
	if (tmpBITMAP)
	{
		::DeleteObject(tmpBITMAP);
		tmpBITMAP = nullptr;
	}
	if (tmpHDC)
	{
		::DeleteDC(tmpHDC);
		tmpHDC = nullptr;
	}
	drawingObjects->~PriorObjectList();
}

BOOL CDrawEngine::Create()
{
	//Создаем все необходиные объекты GDI
	backgroundHDC = ::CreateCompatibleDC(::GetDC(NULL));
	if (backgroundHDC == nullptr)
		return FALSE;

	backgroundBITMAP = ::CreateCompatibleBitmap(::GetDC(NULL), WIDTHPX, HEIGHTPX);
	if (backgroundBITMAP == nullptr)
		return FALSE;

	//Выбираем битмап в контекст фона
	::SelectObject(backgroundHDC, backgroundBITMAP);
	::SetGraphicsMode(backgroundHDC, GM_ADVANCED);

	drawingObjects = new PriorObjectList();

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
	tmpBITMAP = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	HANDLE hOld = SelectObject(tmpHDC, tmpBITMAP);
	BitBlt(tmpHDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), backgroundHDC, 0, 0, SRCCOPY);
	
	drawingObjects->Draw(tmpHDC);
	
#ifdef DEBUG
	if (GESTURE_EMULATOR.pixelCheck)
	{
		HPEN oldPen = (HPEN)SelectObject(tmpHDC, DRAW_KIT.RedPen);
		for (int a = 0; a < WIDTHPX; a += TO_PIXEL(10))
		{
			MoveToEx(tmpHDC, a, 0, NULL);
			LineTo(tmpHDC, a, HEIGHTPX);	
		}
		for (int a = 0; a < HEIGHTPX; a += TO_PIXEL(10))
		{
			MoveToEx(tmpHDC, 0, a, NULL);
			LineTo(tmpHDC, WIDTHPX, a);	
		}
		SelectObject(tmpHDC, oldPen);

	}
#endif

	BitBlt(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), tmpHDC, 0, 0, SRCCOPY);
	
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