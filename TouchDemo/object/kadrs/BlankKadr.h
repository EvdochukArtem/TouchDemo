/*
*	������������ ����� ��� ���� ������ ������������ � ����������. �������� ������������� ������
*	��� ��������� ������ (� ������� ���������� �������� �� ���� ������ �����) � ������ ��������������
*	� ���. �������� ������ ������ �������������� ������, ������� �� �� ������� ���������������
*	��������� �������� � ������ ������� �����.
*/
#pragma once

#include "AbstractKadr.h"
#include "../buttons/MenuButtonHandler.h"

const int INTERACTIVE_OBJ_LENGTH	= 4;


class CBlankKadr : public CAbstractKadr
{
public:
	CBlankKadr(UINT id, KADR_SIZE kadrSize);
	~CBlankKadr();

	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CAbstractKadr* ChangePos(UINT newPos);

	virtual void Move(const POINT firstTouchCoord, const POINT delta);
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter);
	virtual void Rotate(const double dAngle, const POINT rotateCenter);
	//virtual void Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord);
	virtual void Reset();

	virtual void LeftClickHandle(POINT pt);

private:

	UINT ID; //������� ����� ������ � ������������� ��������
	POINT interactiveObj[INTERACTIVE_OBJ_LENGTH];
	void InitInteractiveObj();
	void DrawInteractiveObj(HDC& hdc);
	void ResetInteractiveObject();

	void Hide(bool hidden);

	CMenuButton* btn [MAX_KADR_TYPE - 1];
	void BtnInit();

	POINT _ptCoords;
	bool  _paintClickZone;
	static CBlankKadr* pKadr;
	static void TimerProc (HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
};