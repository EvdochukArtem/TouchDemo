/*
*	Родительский класс для всех кадров используемых в приложении. Содержит интерактивный объект
*	для отработки жестов (в будущем необходимо заменить на меню выбора кадра) и методы взаимодействия
*	с ним. Дочерние классы должны переопределить объект, заменяя их на объекты символизирующие
*	индикацию приборов и другие объекты кадра.
*/
#pragma once

#include "DrawingObject.h"
#include "buttons/MenuButtonHandler.h"

const int INTERACTIVE_OBJ_LENGTH	= 4;

enum KADR_SIZE
{
	HALF,
	QUARTER,
	EIGHTH,
};

enum SWIPE_DIRECTION
{
	LEFT,
	RIGHT,
};

enum KADR_TYPE
{
	EMPTY,
	PLD,
	SYST,
	CAM,
	MAP,
	RDR,
	MAX_KADR_TYPE,
};

class CKadr : public CDrawingObject
{
public:
	CKadr(UINT id, KADR_SIZE kadrSize);
	~CKadr();

	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();
	virtual void ChangeSize(KADR_SIZE newSize);
	virtual CKadr* ChangePos(UINT newPos);

	virtual void Move(const POINT firstTouchCoord, const POINT delta);
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter);
	virtual void Rotate(const double dAngle, const POINT rotateCenter);
	virtual void Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord);
	virtual void Reset();
	virtual KADR_TYPE GetKadrType() { return _kadrType; };
	virtual KADR_SIZE GetKadrSize() { return _kadrSize; };
	virtual void SetSOIStatus(bool soiStatus);
	virtual bool GetBlockStatus() { return _blocked; };
	virtual void SetBlock(bool blockStatus) { _blocked = blockStatus; Hide(blockStatus); };

	virtual void LeftClickHandle(POINT pt);

protected:
	UINT _id;						//(0-7)
	bool _isSOI;
	bool _blocked;
	KADR_SIZE _kadrSize;
	KADR_TYPE _kadrType;	
	double  _scalingFactor;
	double  _rotationAngle;

	void PlaceKadr();

private:
	UINT ID; //Удалить потом вместе с интерактивным объектом
	POINT interactiveObj[INTERACTIVE_OBJ_LENGTH];
	void InitInteractiveObj();
	void DrawInteractiveObj(HDC& hdc);
	void ResetInteractiveObject();

	void Hide(bool hidden);

	CMenuButton* btn [MAX_KADR_TYPE - 1];
	void BtnInit();

	POINT _ptCoords;
	bool  _paintClickZone;
	static CKadr* pKadr;
	static void TimerProc (HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
};