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
	void Draw(HDC& hdc);
	void UpdateBackground();
	HDC& getBackgroundHDC() { return backgroundHDC; };
	CDrawingObject* getObjectInPoint(POINT pt);
	std::vector<CDrawingObject*> getAllObjectsInPoint(POINT pt);

private:
	friend class CUtil;
	class PriorObjectList;
	PriorObjectList* drawingObjects;

	CDrawEngine();
	~CDrawEngine();
	BOOL Create();
	BOOL CleanUp();

	HDC backgroundHDC;
	HDC tmpHDC;
	HBITMAP backgroundBITMAP;
	HBITMAP tmpBITMAP;

#ifdef DEBUG
	short	f, fps;
	LARGE_INTEGER	counter, count, count1;
	void CountFrames(HDC& hdc);
#endif

};

class CDrawEngine::PriorObjectList
{
	friend class CDrawEngine;

	PriorObjectList();
	~PriorObjectList() { Clear(); };

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


	void Draw(HDC& hdc);	// Смешиваются структура данных и функциональность. 
						// Название PriorObjectList выглядит как название контейнера для произвольных данных.
						// Есть смысл или разделить на контейнер PriorObjectList и от него отнаследовать ObjectList,
						// или махнуть рукой и назвать сам класс ObjectList. 
	void UpdateBackground();
	CDrawingObject* getObjectInPoint(POINT pt);
	std::vector<CDrawingObject*> getAllObjectsInPoint(POINT pt);
	std::vector<CDrawingObject*> foundObj;

#ifdef DEBUG
	std::vector<CDrawingObject*> arr;
	void asArray();
#endif
};