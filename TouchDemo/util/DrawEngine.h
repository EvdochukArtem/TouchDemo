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