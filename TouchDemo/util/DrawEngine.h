/*
*	����� �������� �� ��������� �������� ���� DrawingObject �� ����� ������������. ������������ ������� �����������
*	� ����������� ���������� HDC ��� ��������� ��������� �������� (����������� �� ������������� ��. WM_UPDATE) � HDC
*	��� ��������� ���������� ��������� (����������� ��������� ��� � ���). ��� ������� ��� ��������� �������� �
*	��������� ������ � ����������� (������� �� �������� ����� �������������� ����������). � ������ ������� ������
*	����������� � ������ ��� �������� ��������� � ������ ���������.
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
	CDrawEngine();
	~CDrawEngine();
	BOOL Create();

	friend class CUtil;
	class PriorObjectList;
	
	PriorObjectList* drawingObjects;

	HDC backgroundHDC;
	HDC tmpHDC;
	HBITMAP backgroundBITMAP;
	HBITMAP tmpBITMAP;
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


	void Draw(HDC& hdc);	// ����������� ��������� ������ � ����������������. 
						// �������� PriorObjectList �������� ��� �������� ���������� ��� ������������ ������.
						// ���� ����� ��� ��������� �� ��������� PriorObjectList � �� ���� ������������� ObjectList,
						// ��� ������� ����� � ������� ��� ����� ObjectList. 
	void UpdateBackground();
	CDrawingObject* getObjectInPoint(POINT pt);
	std::vector<CDrawingObject*> getAllObjectsInPoint(POINT pt);
	std::vector<CDrawingObject*> foundObj;

#ifdef DEBUG
	std::vector<CDrawingObject*> arr;
	void asArray();
#endif
};