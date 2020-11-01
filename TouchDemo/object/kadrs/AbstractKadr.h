/*
*	Родительский класс для всех кадров используемых в приложении. Содержит интерактивный объект
*	для отработки жестов (в будущем необходимо заменить на меню выбора кадра) и методы взаимодействия
*	с ним. Дочерние классы должны переопределить объект, заменяя их на объекты символизирующие
*	индикацию приборов и другие объекты кадра.
*/

#pragma once
#include "../DrawingObject.h"

const int INNER_KADR_INDENT	= TO_PIXEL(10);

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
	MAX_KADR_TYPE, //он же кадр Blank
};
class CAbstractKadr : public CDrawingObject
{
public:
	CAbstractKadr(UINT id, KADR_SIZE kadrSize);
	virtual ~CAbstractKadr() {};
	virtual KADR_TYPE GetKadrType() { return _kadrType; };
	virtual KADR_SIZE GetKadrSize() { return _kadrSize; };
	virtual void SetSOIStatus(bool soiStatus);
	virtual bool GetBlockStatus() { return _blocked; };
	virtual void SetBlock(bool blockStatus) { _blocked = blockStatus; Hide(blockStatus); };
	
	virtual void ChangeSize(KADR_SIZE newSize) = 0;
	virtual CAbstractKadr* ChangePos(UINT newPos) = 0;
	virtual void Move(const POINT firstTouchCoord, const POINT delta) = 0;
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter) = 0;
	virtual void Rotate(const double dAngle, const POINT rotateCenter) = 0;
	virtual void Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord) final;
	virtual void Reset() = 0;
	virtual void LeftClickHandle(POINT pt) = 0;
	
protected:
	UINT _id;						//(0-7)
	bool _isSOI;
	bool _blocked;
	KADR_SIZE _kadrSize;
	KADR_TYPE _kadrType;
	double  _scalingFactor;
	double  _rotationAngle;

	virtual void PlaceKadr() final;
	virtual void Hide(bool hidden) { _hidden = hidden; };
};

