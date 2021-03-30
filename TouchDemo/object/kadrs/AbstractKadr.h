/*
*	Родительский класс для всех кадров используемых в приложении. Дочерние 
*	классы должны переопределить методы взаимодействия с кадром и наполнить
*	кадр объектами-приборами, кнопками и тд. в соответствии с Логикой кадра.
*/

#pragma once
#include "../DrawingObject.h"

#define INNER_KADR_INDENT (TO_PIXEL(10))
#define TBUTTON_VERT_INDENT	(TO_PIXEL(14))
#define	TBUTTON_HOR_INDENT	(TO_PIXEL(16))
const int MAX_LSIDE_TBUTTONS = 8;					//Макс кол-во кнопок на левой стороне кадра
const int MAX_BSIDE_TBUTTONS = 4;					//Макс кол-во кнопок на нижней стороне кадра
const int MAX_RSIDE_TBUTTONS = MAX_LSIDE_TBUTTONS;	//Макс кол-во кнопок на правой стороне кадра
const int MAX_TBUTTONS = MAX_LSIDE_TBUTTONS + MAX_BSIDE_TBUTTONS + MAX_RSIDE_TBUTTONS; //Макс кол-во кнопок

enum KADR_SIZE
{
	KADR_SIZE_HALF,
	KADR_SIZE_QUARTER,
	KADR_SIZE_EIGHTH,
};

enum SWIPE_DIRECTION
{
	SWIPE_DIR_LEFT,
	SWIPE_DIR_RIGHT,
};

enum KADR_TYPE
{
	KADR_TYPE_PLD,
	KADR_TYPE_SYST,
	KADR_TYPE_CAM,
	KADR_TYPE_MAP,
	KADR_TYPE_RDR,
	KADR_TYPE_AUX,
	KADR_TYPE_KBRD, //Клавиатура
};

enum KADR_COMMANDS
{
	//Общие для всех кадров комманды
	KADR_COMM_ENABLE_SUBMENU,
	KADR_COMM_DISABLE_SUBMENU,
	//Команды кадра MAP:
	KADR_COMM_NAV,
	KADR_COMM_AIR,
	KADR_COMM_GROUND,
	KADR_COMM_MODE1,
	KADR_COMM_MODE2,
	KADR_COMM_SWITCH_COORD_SYS,
	//Команды кадра CAM:
	KADR_COMM_CAM1,
	KADR_COMM_CAM2,
	KADR_COMM_CAM3,
	KADR_COMM_CAM4,
	KADR_COMM_CAM5,
	//Команды кадра SYS:
	KADR_COMM_SYS1,
	KADR_COMM_SYS2,
	KADR_COMM_SYS3,
	KADR_COMM_SYS4,
	KADR_COMM_SYS5,
};

class CAbstractKadr : public CDrawingObject
{
public:
	CAbstractKadr(UINT id, KADR_SIZE kadrSize);
	virtual ~CAbstractKadr() {};
	virtual KADR_TYPE GetKadrType() { return _kadrType; };
	virtual KADR_SIZE GetKadrSize() { return _kadrSize; };
	virtual void SetSOIStatus(bool soiStatus);
	virtual bool GetSOIStatus() { return _isSOI; };
	virtual bool GetBlockStatus() { return _blocked; };
	virtual void SetBlock(bool blockStatus) { _blocked = blockStatus; Hide(blockStatus); };
	virtual bool SubMenuIsOn() { return _subMenu; };
	virtual void ChangeSize(KADR_SIZE newSize) = 0;
	virtual CAbstractKadr* ChangePos(UINT newPos) = 0;

	virtual void Move(const POINT firstTouchCoord, const POINT delta) = 0;
	virtual void Zoom(const double dZoomFactor, const POINT zoomCenter) = 0;
	virtual void DoRotate(const double dAngle, const POINT rotateCenter) = 0;
	virtual void Swipe(const POINT firstTouchCoord, const POINT secondTouchCoord) final;
	virtual void Reset() = 0;
	virtual void LeftClickHandle(POINT pt) = 0;
	virtual void ProcessKeyboard(UINT key) = 0;
	virtual void ProcessCommand(KADR_COMMANDS cmd) = 0;
	
protected:
	UINT _id;						//(0-7)
	bool _isSOI;
	bool _blocked;
	KADR_SIZE _kadrSize;
	KADR_TYPE _kadrType;
	double  _scalingFactor;
	double  _rotationAngle;
	bool	_subMenu;

	virtual void Place() final;
	virtual void Hide(bool hidden) { _hidden = hidden; };
};

