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
	drawingObjects->~LinkedPriorList();
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

	//Выбираем битмап в конткст фона
	::SelectObject(backgroundHDC, backgroundBITMAP);
	::SetGraphicsMode(backgroundHDC, GM_ADVANCED);

	drawingObjects = new LinkedPriorList();

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
}

void CDrawEngine::UpdateBackground()
{
	drawingObjects->UpdateBackground();
}

void CDrawEngine::Draw(HDC hdc)
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

CDrawingObject* CDrawEngine::getDrawingObject(POINT pt)
{
	return drawingObjects->getDrawingObject(pt);
}

CDrawEngine::LinkedPriorList::LinkedPriorList()
{
	head = nullptr;
}

void CDrawEngine::LinkedPriorList::Add(CDrawingObject* obj)
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
		while (cur->next != nullptr && cur->obj->getPrior() < obj->getPrior())
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur->obj->getPrior() < obj->getPrior())
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
void CDrawEngine::LinkedPriorList::asArray()
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

BOOL CDrawEngine::LinkedPriorList::Remove(CDrawingObject* obj)
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

void CDrawEngine::LinkedPriorList::Clear()
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

void CDrawEngine::LinkedPriorList::Draw(HDC hdc)
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

void CDrawEngine::LinkedPriorList::UpdateBackground()
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

CDrawingObject* CDrawEngine::LinkedPriorList::getDrawingObject(POINT pt)
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