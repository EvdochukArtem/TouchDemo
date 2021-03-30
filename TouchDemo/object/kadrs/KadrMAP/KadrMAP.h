#pragma once
#include "../AbstractKadr.h"

const int MAP_PAGES_MAX = 2;
static short MapScale[] = { 10, 20, 50, 100, 200, 500, 1000, 2000, 4000 };

//Нулевой азимут на карте указывает на
enum COORD_SYS
{
	COORD_SYS_PLN,		// САМОЛЕТ
	COORD_SYS_NRTH,		// СЕВЕР
};

struct MAP_SETTINGS
{
	int			scaleIndex;		//текущий зум
	float		scale;			//м в пикселе
	int			declutterState;	//разгрузка кадра
};

class CPage;

class CKadrMAPButtons;

class CKadrMAP : public CAbstractKadr
{
public:
	CKadrMAP(UINT id, KADR_SIZE kadrSize);
	~CKadrMAP();

	virtual void Draw(HDC& hdc);
	virtual void DrawBackground();

	void ChangeSize(KADR_SIZE newSize);
	CAbstractKadr* ChangePos(UINT newPos);
	void Move(const POINT firstTouchCoord, const POINT delta);
	void Zoom(const double dZoomFactor, const POINT zoomCenter);
	void DoRotate(const double dAngle, const POINT rotateCenter) {};
	void Reset();
	void LeftClickHandle(POINT pt);
	void ProcessKeyboard(UINT key);
	void ProcessCommand(KADR_COMMANDS cmd);
	void SetBlock(bool blockStatus);

	//Принимает вектор в котором х - север y - восток, возвращает вектор, где х - восток у - север
	POINT		MapGeoToScreen(POINT position);
	//Принимает вектор где х - восток y - север, возвращает вектор в котором х - север y - восток
	POINT		MapScreenToGeo(POINT position);
	
	double			GetUnchangingNavAngle() {return navAngle;};
	HRGN&			GetKadrRgn() { return priborRgn; };
	MAP_SETTINGS&	GetSettings() { return settings; };
	COORD_SYS&		GetCoordSys() { return coordSys; };
	POINT&			GetMapCenterPoint() { return mapCenterPoint; };
	POINT&			GetPlanePoint() { return planePoint; };
	POINT&			GetMapMove() { return mapMove; };
	
	double			AngleZeroIfPLN();
	double			AnglePsiIfPLN();

	static void		DrawPlane(HDC &hdc, CKadrMAP* kadr, int x, int y, double Kurs, HPEN pen_Plan, HBRUSH brush_Pen);

private:

	void CreatePribors();
	void DeletePribors();
	void DisposePribors();
	void CalculateConstants();
	void PrevScale();
	void NextScale();

	HRGN priborRgn;
	
	MAP_SETTINGS	settings;
	POINT			mapCenterCoord;	//m
	POINT			mapCenterPoint;	//px
	POINT			planePoint;		//px
	POINT			mapMove;		//px

	COORD_SYS		coordSys;

	double	navAngle;
	float	oldScale;
	bool	dataBaseIsOn;
	
	class MyPlane;
	MyPlane*		myPlane;
	
	CPage* pages[MAP_PAGES_MAX];
	CKadrMAPButtons* buttons;

	friend class CCursor;
};

class CKadrMAP::MyPlane : public CDrawingObject
{
public:
	MyPlane(CKadrMAP* kadr);
	virtual ~MyPlane() { kadrMAP = nullptr; };

private:	
	void Draw(HDC& hdc);
	void DrawBackground() {};
	void Place() {};

	CKadrMAP* kadrMAP;
};