/*
*	Класс отвечает за отрисовку объектов типа DrawingObject на экран пользователя. Используется двойная буферизация
*	с применением отдельного HDC для статичных элементов объектов (обновляется по необходимости см. WM_UPDATE) и HDC
*	для отрисовки динамичных элементов (обновляется несколько раз в сек). Все объекты для отрисовки хранятся в
*	связанном списке с приоритетом (объекты на переднем плане отрисовываются последними). В режиме отладки список
*	дублируется в массив для удобства просмотра и поиска элементов.
*/
#pragma once
#include "object/DrawingObject.h"

class CDrawEngine
{
public:
	void AddDrawingObject(CDrawingObject* obj);
	void DeleteDrawingObject(CDrawingObject* obj);
	void ResetDrawingObject(CDrawingObject* obj) { DeleteDrawingObject(obj); AddDrawingObject(obj); };
	void Draw(HDC hdc);
	void UpdateBackground();
	HDC getBackgroundHDC() { return backgroundHDC; };
	CDrawingObject* getDrawingObject(POINT pt);

private:
	CDrawEngine();
	~CDrawEngine();
	BOOL Create();

	friend class CUtil;
	class LinkedPriorList;
	
	LinkedPriorList* drawingObjects;

	HDC backgroundHDC;
	HDC tmpHDC;
	HBITMAP backgroundBITMAP;
	HBITMAP tmpBITMAP;
};

class CDrawEngine::LinkedPriorList
{
	friend class CDrawEngine;

	LinkedPriorList();
	~LinkedPriorList() { Clear(); };

	void Add(CDrawingObject* obj);
	BOOL Remove(CDrawingObject* obj);
	BOOL isEmpty() { return head == nullptr; };
	void Clear();
	struct Node
	{
		CDrawingObject* obj;
		Node* next;
	};

	Node* head;


	void Draw(HDC hdc);
	void UpdateBackground();
	CDrawingObject* getDrawingObject(POINT pt);

#ifdef DEBUG
	std::vector<CDrawingObject*> arr;
	void asArray();
#endif
};